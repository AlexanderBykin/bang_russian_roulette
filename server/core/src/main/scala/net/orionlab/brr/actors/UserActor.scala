/*
    Bang Russian Roulette (server) - This is real online and multiplayer game published at Google Play.
    Copyright (C) 2016  Alexander Shniperson
    Email: alex.shniperson@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

package net.orionlab.brr.actors

object UserActor {

  import org.apache.commons.codec.binary.Hex
  import akka.actor.{PoisonPill, Props, ActorRef, ActorLogging, Actor}
  import org.joda.time.LocalDateTime
  import net.orionlab.brr.actors.RoomPlayerActor._
  import net.orionlab.brr.actors.SocketClientActor._
  import net.orionlab.brr.actors.RoomActor._
  import net.orionlab.brr.actors.RoomManager._
  import net.orionlab.brr.actors.UserManager._
  import ProtoMessages.MessageRequestWatchAdBase.MessageRequestWatchAd.eAdType
  import net.orionlab.brr.utils.{SocketMessage, CoreTransaction}
  import ProtoMessages._
  import ProtoMessages.ProtoMessageTypeBase.eProtoMessageType
  import ProtoMessages.MessageRequestBuyShopItemBase.MessageRequestBuyShopItem.{eItemType, eBuyType, eMarketType}
  import ProtoMessages.MessageResponseBuyShopItemBase.MessageResponseBuyShopItem.eBuyErrorType
  import ProtoMessages.MessageResponseCheckApiBase.MessageResponseCheckApi.eCheckApiStatus
  import net.orionlab.brr.domain._
  import ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType
  import com.google.protobuf.ByteString
  import ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType
  import ProtoMessages.MessageResponseAuthBase.MessageResponseAuth
  import ProtoMessages.MessageResponseTimeToResultsBase.MessageResponseTimeToResults.eRoomResultType
  import ProtoMessages.MessageRequestRoomListBase.MessageRequestRoomList.eBetType
  import ProtoMessages.MessageRequestRoomPlayerListBase
  import java.util.{List => JList}
  import scala.util._
  import org.apache.commons.codec.digest.DigestUtils
  import net.orionlab.brr.utils.CoreUtils._

  def props(clientActor: ActorRef, actorId: Long, ipAddress: String) = {
    Props(classOf[UserActor], clientActor, actorId, ipAddress)
  }

  case class RoomPlayerInit2Player(roomId: Long)

  case class RoomPlayerInit2Room(roomId: Long)

  case object NeedAuth2Player

  case class NoMoney2Player(amount: Long, need: Long)

  case class AuthUser2Room(playerId: Long, playerName: String)

  case class GetShopItems(identity: String, itemType: eShopItemType, lang: String)

  case class RoomPlayerInfo(var playerId: Long, playerName: String, position: Int, avatar: Array[Byte], shootDirection: PlayerShootDirectionType)

  //case class RoomPlayerInfo(id: Long, name: String, wins: Int, loses: Int, position: Int, avatar: Array[Byte], shootDirection: PlayerShootDirectionType)

  case class SetPlayerTypeAndPosition2Player(roomId: Long, playerInfo: RoomPlayerInfo)

  case class SetPlayerTypeAndPosition2Room(roomId: Long, playerType: PlayerType, position: Int)

  case object UserDisconnected

  case class SetPistolBullets2Room(roomId: Long, bullets: Array[Boolean])

  //case class SetPistolBullets2Player(roomId: Long, bullets: Array[Boolean])

  case class UsePlayerItem2Room(roomId: Long, itemName: String, sourcePlayerId: Long, destPlayerId: Long)

  case class UsePlayerItem2Player(roomId: Long, itemName: String, sourcePlayerId: Long, destPlayerId: Long)

  case class PlayerBet2Room(roomId: Long, sourcePlayerId: Long, destPlayerId: Long, betType: PlayerBetWinType, amount: Long)

  case class PlayerBet2Player(roomId: Long, sourcePlayerId: Long, destPlayerId: Long, betType: PlayerBetWinType, amount: Long)

  case class PlayerBang2Room(roomId: Long)

  case class PlayerBang2Player(roomId: Long, result: RoomRoundPlayerResult)

  case class PlayerExit2Room(roomId: Long, playerId: Long)

  case class PlayerExit2Player(roomId: Long, playerId: Long, pos: Int)

  case class RotateDrum2Room(roomId: Long, playerId: Long)

  case class RotateDrum2Player(roomId: Long, playerId: Long)

  case class RoomPlayerDuelists2Room(roomId: Long)

  case class RoomPlayerDuelists2Player(roomId: Long, duelists: List[RoomRoundPlayerDuelist])

  case class SetRoomPlayerDuelist2Room(roomId: Long, position: Int)

  case class SetRoomPlayerDuelist2Player(roomId: Long, playerDuelistInfo: RoomRoundPlayerDuelist)

  case class BuyShopItem2Player(identity: String, shopItemName: String, receipt: Array[Byte], buyType: eBuyType, itemType: eItemType)

  class UserActor(clientActor: ActorRef, actorId: Long, ipAddress: String) extends Actor with ActorLogging with CoreTransaction with SocketMessage {

    import collection.JavaConversions._
    import concurrent.duration.Duration
    import java.util.concurrent.TimeUnit
    import ProtoMessages.AuthTypeBase.eAuthType
    import net.orionlab.brr.actors.NotificationManager.EmailNotification
    import net.orionlab.brr.actors.PaymentRequestManager.{PaymentRequestResult, CheckPaymentRequest}

    val sessionId: Long = createUserSession()
    val supportedLocalizations = Array("en", "ru")
    val defaultLocalization = supportedLocalizations.head
    val checkApiVersionTimeout = Duration.create(
      context.system.settings.config.getDuration("gameProperties.checkClientVersionTimeOut", TimeUnit.MILLISECONDS),
      TimeUnit.MILLISECONDS)
    val validApiVersion = context.system.settings.config.getString("gameProperties.validClientVersion")
    var playerId = Option.empty[Long]
    var playerName = Option.empty[String]
    var roomInfoListAmount = Int.MaxValue
    var roomInfos = List.empty[RoomInfo]

    case object CheckApiTimeout

    val checkApiScheduler = context.system.scheduler.scheduleOnce(checkApiVersionTimeout, self, CheckApiTimeout)(context.dispatcher)

    override def getClientActor(): ActorRef = clientActor

    def receive = {
      case msgReceive: IncomingMessage ⇒
        Try {
          msgReceive.message.getMessageType match {
            case eProtoMessageType.cmtCheckAPIVersion =>
              checkApiScheduler.cancel()
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
                msgCheckApi(false)
                disconnectUser()
              } else {
                val msg = MessageRequestCheckApiBase.MessageRequestCheckApi.parseFrom(msgReceive.message.getMessageBody)
                val isValidApiVersion = msg.getVersion == validApiVersion
                msgCheckApi(isValidApiVersion)
                if (isValidApiVersion) context.become(ready2Work)
                else disconnectUser()
              }
            case any => log.warning(s"Unhandled messageType <$any> from <${sender()}>")
          }
        } match {
          case Success(x) ⇒
          case Failure(x) ⇒
            log.error(x, "")
            msgCheckApi(false)
            disconnectUser()
        }

      case CheckApiTimeout => disconnectUser()

      case any => log.warning(s"Unhandled message <$any> from <${sender()}>")
    }

    def ready2Work: Receive = {
      case msg: PlayerBet2Room =>
        if (playerId.isEmpty)
          msgRoomPlayerNeedAuth()
        else if (msg.amount > 0)
          context.children.foreach(_ ! msg.copy(sourcePlayerId = playerId.get))

      case msg: PaymentRequestResult =>
        // TODO: move inTransaction outside of method
        msg.result match {
          case PaymentRequestStatus.SUCCESS =>
            sendBuyResponse(msg.itemName, doInThreadTransaction({
              doBuyShopItem(msg.itemName, msg.itemType, false)
            }).get.get)
          case PaymentRequestStatus.FAILED =>
            sendBuyResponse(msg.itemName, eBuyErrorType.betReceiptError)
          case _ =>
        }

      case msgReceive: IncomingMessage ⇒
        Try {
          msgReceive.message.getMessageType match {
            case eProtoMessageType.cmtGetPlayerProfile =>
              if (playerId.getOrElse(0L) <= 0) {
                msgRoomPlayerNeedAuth()
              } else {
                doInThreadTransaction({
                  getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.Player WHERE" +
                    s" id = ${playerId.get}")
                    .list().asInstanceOf[java.util.List[Player]].headOption match {
                    case None ⇒ log.error(s"Cant find player(${playerId.get}) when process cmtGetPlayerProfile.")
                    case Some(player) ⇒
                      val msgResponse = MessageResponsePlayerProfileBase.MessageResponsePlayerProfile.newBuilder()
                      msgResponse.setPlayerName(playerName.getOrElse(""))
                      msgResponse.setPlayerEmail(Option(player.getEmail).getOrElse(""))
                      msgResponse.setPlayerMoney(player.getMoney)
                      msgResponse.setPlayerWins(player.getWins)
                      msgResponse.setPlayerLoses(player.getLoses)
                      msgResponse.setPlayerRating(0)
                      msgResponse.setPlayerAvatar(ByteString.EMPTY)
                      sendSocketMessage(eProtoMessageType.cmtGetPlayerProfile, msgResponse)
                  }
                }, ro = true)
              }

            case eProtoMessageType.cmtRoomPlayerInit =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomPlayerInitBase.MessageRequestRoomPlayerInit.parseFrom(msgReceive.message.getMessageBody)
                val roomPlayerActor = getOrCreateRoomPlayerActor(msg.getRoomId)
                context.parent ! SetRoomPlayer(msg.getRoomId, RoomPlayer(roomPlayerActor, sessionId, playerId, playerName, PlayerType.WATCHER, 0))
              }

            case eProtoMessageType.cmtAuth =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestAuthBase.MessageRequestAuth.parseFrom(msgReceive.message.getMessageBody)
                val msgResponse = MessageResponseAuthBase.MessageResponseAuth.newBuilder()
                authUser(msg) match {
                  case Left(l) => msgResponse.setErrorType(l)
                  case Right(r) =>
                    playerId = Some(r._1)
                    playerName = Some(r._2)
                    context.children.foreach(_ ! AuthUser2Room(playerId.get, playerName.get))
                    msgResponse.setErrorType(MessageResponseAuth.eAuthErrorType.aetNone)
                    msgResponse.setPlayerId(playerId.get)
                }
                log.info(s">>> Auth errorType(${msgResponse.getErrorType}) playerId(${msgResponse.getPlayerId})")
                sendSocketMessage(eProtoMessageType.cmtAuth, msgResponse)
              }

            case eProtoMessageType.cmtRegister =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRegistrationBase.MessageRequestRegistration.parseFrom(msgReceive.message.getMessageBody)
                val msgResponse = MessageResponseAuthBase.MessageResponseAuth.newBuilder()
                registerUser(msg) match {
                  case Left(l) => msgResponse.setErrorType(l)
                  case Right(r) =>
                    msgResponse.setErrorType(MessageResponseAuth.eAuthErrorType.aetNone)
                    msgResponse.setPlayerId(r)
                }
                sendSocketMessage(eProtoMessageType.cmtAuth, msgResponse)
              }

            case eProtoMessageType.cmtForgotPassword =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestForgotPasswordBase.MessageRequestForgotPassword.parseFrom(msgReceive.message.getMessageBody)
                val msgResponse = MessageResponseAuthBase.MessageResponseAuth.newBuilder()
                msgResponse.setErrorType(forgotPassword(msg))
                sendSocketMessage(eProtoMessageType.cmtAuth, msgResponse)
              }

            case eProtoMessageType.cmtGetRoomPlayersDuelist =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomPlayerDuelistBase.MessageRequestRoomPlayerDuelist.parseFrom(msgReceive.message.getMessageBody)
                context.children.foreach(_ ! RoomPlayerDuelists2Room(msg.getRoomId))
              }

            case eProtoMessageType.cmtSetPlayerDuelist =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestSetPlayerDuelistBase.MessageRequestSetPlayerDuelist.parseFrom(msgReceive.message.getMessageBody)
                context.children.foreach(_ ! SetRoomPlayerDuelist2Room(msg.getRoomId, msg.getPosition))
              }

            case eProtoMessageType.cmtGetShopItems =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestShopItemListBase.MessageRequestShopItemList.parseFrom(msgReceive.message.getMessageBody)

                var lang = "[A-Za-z]".r.findAllIn(msg.getLang).mkString.substring(0, 2)

                if (lang.length < 2 || !supportedLocalizations.contains(lang)) {
                  lang = defaultLocalization
                }

                val items = shopItemsByTypeAndLang(msg.getShopItemType, lang)

                //              log.info(s"GetShopItems type=${msg.getShopItemType} lang=$lang items=$items")

                val msgResponse = MessageResponseShopItemListBase.MessageResponseShopItemList.newBuilder()
                items.foreach(r => {
                  msgResponse.addShopItemList(r)
                })

                sendSocketMessage(eProtoMessageType.cmtGetShopItems, msgResponse)
              }

            case eProtoMessageType.cmtBuyShopItem =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestBuyShopItemBase.MessageRequestBuyShopItem.parseFrom(msgReceive.message.getMessageBody)
                val itemName = "[a-zA-Z0-9\\_?]".r.findAllIn(msg.getShopItemName).mkString

                if (playerId.isEmpty) {
                  msgRoomPlayerNeedAuth()
                } else {
                  msg.getBuyType match {
                    case eBuyType.btRealMoney =>
                      val receipt = msg.getReceipt.toStringUtf8.replace("\r", "").replace("\n", "").replace("\t", "").trim.getBytes("utf-8")
                      val marketType = msg.getMarketType match {
                        case eMarketType.atApple => MarketType.APPLE
                        case _ => MarketType.GOOGLE
                      }
                      val paymentRequestId = doInThreadTransaction({
                        val player = getPlayerDao.load(playerId.get)
                        // log.info(s"received receipt='${msg.getReceipt.toStringUtf8}' after='${new String(receipt, "utf-8")}'")
                        // заносим чек полученный игроком от Сервера Аппле в свою таблицу на всякий пожарный
                        val res = getPlayerPaymentRequestDao.create(PlayerPaymentRequest.Factory.newInstance(msg.getShopItemName, receipt, marketType, PaymentRequestStatus.NEW, LocalDateTime.now, player))
                        res.getId
                      }).get.get
                      context.parent ! CheckPaymentRequest(Option(paymentRequestId), msg.getItemType)

                    case eBuyType.btInGameCash =>
                      // TODO: move inTransaction outside
                      sendBuyResponse(itemName, doInThreadTransaction({
                        doBuyShopItem(itemName, msg.getItemType, true)
                      }).get.get)
                  }
                }
              }

            case eProtoMessageType.cmtGetMoney =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                if (playerId.isEmpty) {
                  msgRoomPlayerNeedAuth()
                } else {
                  val msgResponse = MessageResponseMoneyBase.MessageResponseMoney.newBuilder()
                  msgResponse.setMoney(getPlayerDao.load(playerId.get).getMoney.longValue())
                  sendSocketMessage(eProtoMessageType.cmtGetMoney, msgResponse)
                }
              }

            case eProtoMessageType.cmtGetRoomList =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomListBase.MessageRequestRoomList.parseFrom(msgReceive.message.getMessageBody)

                val roomType = msg.getBetType match {
                  case eBetType.btTINY => RoomType.TINY
                  case eBetType.btSMALL => RoomType.SMALL
                  case eBetType.btMEDIUM => RoomType.MEDIUM
                  case eBetType.btBIG => RoomType.BIG
                }

                context.parent ! GenerateRoomByType(roomType)
                context.parent ! GetRoomListByType(roomType)
              }

            case eProtoMessageType.cmtBang =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestBangBase.MessageRequestBang.parseFrom(msgReceive.message.getMessageBody)
                context.children.foreach(_ ! PlayerBang2Room(msg.getRoomId))
              }

            case eProtoMessageType.cmtGetRoomInfo =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomInfoBase.MessageRequestRoomInfo.parseFrom(msgReceive.message.getMessageBody)
                context.children.foreach(_ ! RoomInfo2Room(msg.getRoomId))
              }

            case eProtoMessageType.cmtGetRoomPlayers =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomPlayerListBase.MessageRequestRoomPlayerList.parseFrom(msgReceive.message.getMessageBody)
                context.children.foreach(_ ! GetRoomPlayers(msg.getRoomId))
              }

            case eProtoMessageType.cmtUsePlayerInventoryItem =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestUsePlayerInventoryItemBase.MessageRequestUsePlayerInventoryItem.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.isEmpty)
                  msgRoomPlayerNeedAuth()
                else {
                  val itemName = "[a-zA-Z0-9\\_?]".r.findAllIn(msg.getShopItemName).mkString
                  if (itemName.nonEmpty && msg.getDestPlayerId > 0) {
                    context.children.foreach(_ ! UsePlayerItem2Room(msg.getRoomId, msg.getShopItemName, playerId.get, msg.getDestPlayerId))
                  }
                }
              }

            case eProtoMessageType.cmtRotateDrum =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRotateDrumBase.MessageRequestRotateDrum.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.isEmpty)
                  msgRoomPlayerNeedAuth()
                else {
                  context.children.foreach(_ ! RotateDrum2Room(msg.getRoomId, playerId.get))
                }
              }

            case eProtoMessageType.cmtSetPistolBullets =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestSetPlayerBulletsBase.MessageRequestSetPlayerBullets.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.isEmpty)
                  msgRoomPlayerNeedAuth()
                else
                  context.children.foreach(_ ! SetPistolBullets2Room(msg.getRoomId, Array(msg.getB1, msg.getB2, msg.getB3, msg.getB4, msg.getB5, msg.getB6, msg.getB7, msg.getB8, msg.getB9, msg.getB10, msg.getB11, msg.getB12)))
              }

            case eProtoMessageType.cmtSetPlayerTypeAndPosition =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.isEmpty)
                  msgRoomPlayerNeedAuth()
                else
                  context.children.foreach(_ ! SetPlayerTypeAndPosition2Room(msg.getRoomId, msg.getPlayerType, msg.getPosition))
              }

            case eProtoMessageType.cmtRoomExit =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestRoomPlayerExitBase.MessageRequestRoomPlayerExit.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.isDefined)
                  context.children.foreach(_ ! PlayerExit2Room(msg.getRoomId, playerId.get))
              }

            case eProtoMessageType.cmtPlayerBet =>

            case eProtoMessageType.cmtUpdateAvatar =>

            case eProtoMessageType.cmtUpdateSettings =>

            case eProtoMessageType.cmtGetPlayerInfo ⇒
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestPlayerInfoBase.MessageRequestPlayerInfo.parseFrom(msgReceive.message.getMessageBody)
                if (msg.getPlayerId > 0) {
                  doInThreadTransaction({
                    getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.Player WHERE" +
                      s" id = ${msg.getPlayerId}")
                      .list().asInstanceOf[java.util.List[Player]].headOption match {
                      case None ⇒ log.error(s"Cant find player(${msg.getPlayerId}) when process cmtGetPlayerInfo.")
                      case Some(player) ⇒
                        val msgResponse = MessageResponsePlayerInfoBase.MessageResponsePlayerInfo.newBuilder()
                        msgResponse.setPlayerId(player.getId)
                        msgResponse.setPlayerName(player.getDisplayName)
                        msgResponse.setPlayerWins(player.getWins)
                        msgResponse.setPlayerLoses(player.getLoses)
                        msgResponse.setRatingPosition(0)
                        msgResponse.setPlayerAvatar(ByteString.EMPTY)
                        sendSocketMessage(eProtoMessageType.cmtGetPlayerInfo, msgResponse)
                    }
                  }, ro = true)
                }
              }

            case eProtoMessageType.cmtWatchAd =>
              if (msgReceive.message.getMessageBody.isEmpty) {
                log.error(s"${self.path} received empty MessageBody for MessageType='${msgReceive.message.getMessageType.name()}'")
              } else {
                val msg = MessageRequestWatchAdBase.MessageRequestWatchAd.parseFrom(msgReceive.message.getMessageBody)
                if (playerId.getOrElse(0L) > 0) {
                  doInThreadTransaction({
                    getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.Player WHERE" +
                      s" id = ${playerId.get}")
                      .list().asInstanceOf[java.util.List[Player]].headOption match {
                      case None ⇒ log.error(s"Cant find player(${playerId.get}) when process cmtWatchAd.")
                      case Some(player) ⇒
                        val shopItemName = msg.getAdType match {
                          case eAdType.atVungle => "brr_videoad_vungle"
                          case eAdType.atAdColony => "brr_videoad_adcolony"
                        }
                        Option(getShopItemDao.searchUniqueName(shopItemName)).foreach(shopItem => {
                          player.setMoney(player.getMoney + shopItem.getCost)
                          val msgResponse = MessageResponseWatchAdBase.MessageResponseWatchAd.newBuilder()
                          msgResponse.setRewardAmount(shopItem.getCost)
                          sendSocketMessage(eProtoMessageType.cmtWatchAd, msgResponse)
                        })
                    }
                  })
                } else {
                  msgRoomPlayerNeedAuth()
                }
              }

            case _ =>
          }
        } match {
          case Success(x) ⇒
          case Failure(x) ⇒ log.error(x, "")
        }

      case UserDisconnected ⇒ disconnectUser()

      case msg: RoomNotFound ⇒
        log.error(s"Room(${msg.roomId}) not found, stopping RoomPlayerActor(${sender()})")
        context.stop(sender())

      case msg: RoomPlayerInit2Player =>
        val msgResponse = MessageResponseRoomPlayerInitBase.MessageResponseRoomPlayerInit.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        sendSocketMessage(eProtoMessageType.cmtRoomPlayerInit, msgResponse)

      case RoomIsFinish ⇒ context.stop(sender())

      case msg: RoomPlayerDuelists2Player =>
        val msgResponse = MessageResponseRoomPlayerDuelistBase.MessageResponseRoomPlayerDuelist.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msg.duelists.foreach(r => {
          val playerDuelist = MessageResponseRoundPlayerDuelistBase.MessageResponseRoundPlayerDuelist.newBuilder()
          playerDuelist.setPlayerId(r.playerId)
          playerDuelist.setPlayerPosition(r.position)
          playerDuelist.setPlayerIsDuelist(r.isDuelist)
          playerDuelist.setWinAmount(r.winAmount.toInt)
          msgResponse.addPlayerList(playerDuelist)
        })
        sendSocketMessage(eProtoMessageType.cmtGetRoomPlayersDuelist, msgResponse)

      case msg: SetRoomPlayerDuelist2Player =>
        val msgResponse = MessageResponseSetPlayerDuelistBase.MessageResponseSetPlayerDuelist.newBuilder()
        val playerDuelist = MessageResponseRoundPlayerDuelistBase.MessageResponseRoundPlayerDuelist.newBuilder()
        playerDuelist.setPlayerId(msg.playerDuelistInfo.playerId)
        playerDuelist.setPlayerPosition(msg.playerDuelistInfo.position)
        playerDuelist.setPlayerIsDuelist(msg.playerDuelistInfo.isDuelist)
        playerDuelist.setWinAmount(msg.playerDuelistInfo.winAmount.toInt)
        msgResponse.setPlayerInfo(playerDuelist)
        msgResponse.setRoomId(msg.roomId)
        sendSocketMessage(eProtoMessageType.cmtSetPlayerDuelist, msgResponse)

      case msg: Ready2DuelistResult2Player =>
        val msgResponse = MessageResponseTimeToResultsBase.MessageResponseTimeToResults.newBuilder()
        msgResponse.setResultType(eRoomResultType.rrtPlayerDuelist)
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setTime(msg.time)
        msg.duelists.foreach(r ⇒ {
          val duelist = MessageResponseRoundPlayerDuelistBase.MessageResponseRoundPlayerDuelist.newBuilder()
          duelist.setPlayerId(r.playerId)
          duelist.setPlayerPosition(r.position)
          duelist.setPlayerIsDuelist(r.isDuelist)
          duelist.setWinAmount(r.winAmount.toInt)
          msgResponse.addDuelistResults(duelist)
        })
        sendSocketMessage(eProtoMessageType.cmtRoomResults, msgResponse)

      case msg: Ready2Start2Player =>
        val msgResponse = MessageResponseTimeToStartBase.MessageResponseTimeToStart.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setTime(msg.time)
        msgResponse.setCurrentRound(msg.round)
        msgResponse.setShootDirection(msg.shootDirection)
        msgResponse.setIsChooseDuelist(msg.isChooseDuelist)
        msgResponse.setIsDuel(msg.isDuel)
        sendSocketMessage(eProtoMessageType.cmtTimeToStart, msgResponse)

      case msg: Ready2PutBullets2Player =>
        val msgResponse = MessageResponseTimeToPutBulletsBase.MessageResponseTimeToPutBullets.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setTime(msg.time)
        msgResponse.setPossibleBullets(msg.possibleBullets)
        sendSocketMessage(eProtoMessageType.cmtTimeToPutBullets, msgResponse)

      case msg: Ready2RotateDrum2Player =>
        val msgResponse = MessageResponseTimeToRotateDrumBase.MessageResponseTimeToRotateDrum.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setTime(msg.time)
        sendSocketMessage(eProtoMessageType.cmtTimeToRotateDrum, msgResponse)

      case msg: Ready2Shoot2Player =>
        val msgResponse = MessageResponseTimeToShootBase.MessageResponseTimeToShoot.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setTime(msg.time)
        sendSocketMessage(eProtoMessageType.cmtTimeToShoot, msgResponse)

      case msg: Ready2RoundResult2Player =>
        val msgResponse = MessageResponseTimeToResultsBase.MessageResponseTimeToResults.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setResultType(eRoomResultType.rrtPlayerBang)
        msg.roundResult.foreach(r => {
          val playerResult = MessageResponseRoundPlayerBangBase.MessageResponseRoundPlayerBang.newBuilder()
          playerResult.setPlayerId(r.playerId)
          playerResult.setPlayerPosition(r.playerPosition)
          playerResult.setKilledPlayerId(r.killedPlayerId)
          playerResult.setKilledPlayerPosition(r.killedPlayerPosition)
          playerResult.setWinAmount(r.winAmount.toInt)
          msgResponse.addGameResults(playerResult)
        })
        msgResponse.setTime(msg.time)
        sendSocketMessage(eProtoMessageType.cmtRoomResults, msgResponse)

      case msg: PlayerBang2Player =>
        val msgResponse = MessageResponseRoomPlayerBangBase.MessageResponseRoomPlayerBang.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        val playerResult = MessageResponseRoundPlayerBangBase.MessageResponseRoundPlayerBang.newBuilder()
        playerResult.setPlayerId(msg.result.playerId)
        playerResult.setPlayerPosition(msg.result.playerPosition)
        playerResult.setKilledPlayerId(msg.result.killedPlayerId)
        playerResult.setKilledPlayerPosition(msg.result.killedPlayerPosition)
        playerResult.setWinAmount(msg.result.winAmount.toInt)
        msgResponse.setResult(playerResult)
        sendSocketMessage(eProtoMessageType.cmtBang, msgResponse)

      case msg: Ready2End2Player =>
        val msgResponse = MessageResponseTimeToEndBase.MessageResponseTimeToEnd.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msg.gameWinner.foreach(x ⇒ {
          val playerResult = MessageResponseRoundPlayerBangBase.MessageResponseRoundPlayerBang.newBuilder()
          playerResult.setPlayerId(x.playerId)
          playerResult.setPlayerPosition(x.playerPosition)
          playerResult.setKilledPlayerId(x.killedPlayerId)
          playerResult.setKilledPlayerPosition(x.killedPlayerPosition)
          playerResult.setWinAmount(x.winAmount.toInt)
          msgResponse.setGameWinner(playerResult)
        })
        sendSocketMessage(eProtoMessageType.cmtTimeToEnd, msgResponse)

      case msg: PlayerBet2Player => msgPlayerBet(msg.roomId, msg.sourcePlayerId, msg.destPlayerId, msg.betType, msg.amount)

      case msg: UsePlayerItem2Player =>
        val msgResponse = MessageResponseUsePlayerInventoryItemBase.MessageResponseUsePlayerInventoryItem.newBuilder
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setPlayerId(msg.sourcePlayerId)
        msgResponse.setDestPlayerId(msg.destPlayerId)
        msgResponse.setShopItemName(msg.itemName)
        sendSocketMessage(eProtoMessageType.cmtUsePlayerInventoryItem, msgResponse)

      case msg: RotateDrum2Player =>
        val msgResponse = MessageResponseRotateDrumBase.MessageResponseRotateDrum.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setPlayerId(msg.playerId)
        sendSocketMessage(eProtoMessageType.cmtRotateDrum, msgResponse)

      case msg: SetPlayerTypeAndPosition2Player =>
        val msgResponse = MessageResponseSetPlayerTypeAndPositionBase.MessageResponseSetPlayerTypeAndPosition.newBuilder()
        val playerInfo = MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo.newBuilder()
        playerInfo.setPlayerId(msg.playerInfo.playerId)
        playerInfo.setPlayerName(msg.playerInfo.playerName)
        playerInfo.setPlayerAvatar(ByteString.EMPTY)
        playerInfo.setPlayerPosition(msg.playerInfo.position)
        playerInfo.setShootDirection(msg.playerInfo.shootDirection)
        msgResponse.setPlayer(playerInfo)
        msgResponse.setRoomId(msg.roomId)
        sendSocketMessage(eProtoMessageType.cmtSetPlayerTypeAndPosition, msgResponse)

      case NeedAuth2Player =>
        if (playerId.isEmpty && playerName.isEmpty)
          msgRoomPlayerNeedAuth()
        else
          context.children.foreach(_ ! AuthUser2Room(playerId.get, playerName.get))

      case msg: GetRoomListByType => context.parent ! msg

      case msg: RoomListAmountByType =>
        roomInfos = List.empty[RoomInfo]
        roomInfoListAmount = msg.amount

      case msg: RoomInfo2Player =>
        val msgResponse = makeRoomInfo(msg.roomInfo)
        sendSocketMessage(eProtoMessageType.cmtGetRoomInfo, msgResponse)

      case msg: RoomInfo =>
        roomInfos ::= msg

        if (roomInfos.size == roomInfoListAmount) {
          val msgResponse = MessageResponseRoomListBase.MessageResponseRoomList.newBuilder()
          roomInfos.foreach(r => {
            msgResponse.addRoomList(makeRoomInfo(r))
          })

          roomInfoListAmount = Int.MaxValue
          roomInfos = List.empty[RoomInfo]

          sendSocketMessage(eProtoMessageType.cmtGetRoomList, msgResponse)
        }

      case msg: PlayerExit2Player =>
        val msgResponse = MessageResponseRoomPlayerExitBase.MessageResponseRoomPlayerExit.newBuilder()
        msgResponse.setRoomId(msg.roomId)
        msgResponse.setPlayerId(msg.playerId)
        msgResponse.setPosition(msg.pos)
        sendSocketMessage(eProtoMessageType.cmtSetPlayerTypeAndPosition, msgResponse)

      case msg: RoomPlayerInfos =>
        val msgResponse = MessageResponseRoomPlayerListBase.MessageResponseRoomPlayerList.newBuilder
        msgResponse.setRoomId(msg.roomId)
        msg.infos.foreach(r => {
          val item = MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo.newBuilder
          item.setPlayerId(r.playerId)
          item.setPlayerName(r.playerName)
          item.setPlayerPosition(r.position)
          item.setPlayerAvatar(ByteString.EMPTY)
          item.setShootDirection(r.shootDirection)
          msgResponse.addPlayerList(item.build())
        })
        sendSocketMessage(eProtoMessageType.cmtGetRoomPlayers, msgResponse)

      case msg: NoMoney2Player ⇒
        val msgResponse = MessageResponseNoMoneyBase.MessageResponseNoMoney.newBuilder()
        msgResponse.setAmount(msg.amount)
        msgResponse.setNeed(msg.need)
        sendSocketMessage(eProtoMessageType.cmtNoMoney, msgResponse)

      case any => log.warning(s">>> Unhandled event <$any>")
    }

    def disconnectUser(): Unit = {
      if (playerId.isDefined) {
        context.children.foreach(_ ! ClientDisconnected2Room(actorId, playerId.get))
      }
      import concurrent.duration._
      import scala.concurrent.ExecutionContext.Implicits.global
      context.system.scheduler.scheduleOnce(1.second, clientActor, PoisonPill)
      context.parent ! UserDisconnected
    }

    def msgCheckApi(isSuccess: Boolean) {
      val msg = MessageResponseCheckApiBase.MessageResponseCheckApi.newBuilder()
      msg.setStatus(if (isSuccess) eCheckApiStatus.casSUCCESS else eCheckApiStatus.casFAILED)
      sendSocketMessage(eProtoMessageType.cmtCheckAPIVersion, msg)
    }

    def sendBuyResponse(itemName: String, buyResult: eBuyErrorType) {
      val msgResponse = MessageResponseBuyShopItemBase.MessageResponseBuyShopItem.newBuilder()
      msgResponse.setShopItemName(itemName)
      msgResponse.setBuyErrorType(buyResult)
      sendSocketMessage(eProtoMessageType.cmtBuyShopItem, msgResponse)
    }

    private def shopItemsByTypeAndLang(itemType: eShopItemType, lang: String): List[MessageResponseShopItemBase.MessageResponseShopItem] = {
      doInThreadTransaction({
        itemType match {
          case eShopItemType.sitITEMS =>
            getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.ShopItem WHERE" +
              s" itemType IN ('${ShopItemType.BULLET}', '${ShopItemType.HELMET}', '${ShopItemType.PISTOL}', '${ShopItemType.SHOOTDIRECTION}')" +
              s" AND isVisible = true" +
              s" AND isArchived = false").
              list().asInstanceOf[JList[ShopItem]].map(r => {
              val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
              item.setAmount(0)
              item.setCost(r.getCost)
              item.setImageName(r.getImageName)
              item.setName(r.getName)
              item.setDescription(getShopItemLocalization(r.getLocales.toList, lang))
              item.setUsageType(r.getUsageType)
              item.build()
            }).toList

          case eShopItemType.sitCOLLECTIONITEMS =>
            getShopItemCollectionDao.loadAll().flatMap(r => {
              if (r.getItems.count(i => i.getItem.getItemType == ShopItemType.MONEY) == 0) {
                val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
                item.setAmount(0)
                item.setCost(r.getCost)
                item.setImageName(r.getImageName)
                item.setName(r.getName)
                item.setDescription(getShopItemLocalization(r.getLocales.toList, lang))
                item.setUsageType(MessageResponseShopItemBase.MessageResponseShopItem.eUsageType.utBoth)
                Some(item.build())
              } else None
            }).toList

          case eShopItemType.sitCOLLECTIONMONEY =>
            getShopItemCollectionDao.loadAll().toList.sortWith(_.getOrderNum > _.getOrderNum).flatMap(r => {
              if (r.getItems.count(i => i.getItem.getItemType == ShopItemType.MONEY) > 0) {
                val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
                item.setAmount(0)
                item.setCost(r.getCost)
                item.setImageName(r.getImageName)
                item.setName(r.getName)
                item.setDescription(getShopItemLocalization(r.getLocales.toList, lang))
                item.setUsageType(MessageResponseShopItemBase.MessageResponseShopItem.eUsageType.utBoth)
                Some(item.build())
              } else None
            }).reverse

          case eShopItemType.sitINVENTORY =>
            if (playerId.getOrElse(0L) > 0) {
              getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.PlayerShopItem WHERE" +
                s" player.id = ${playerId.get}" +
                s" AND shopItem.itemType not in ('${ShopItemType.MONEY}', '${ShopItemType.VIDEOAD}')" +
                s" AND isArchived = false" +
                s" AND shopItem.isVisible = true" +
                s" AND shopItem.isArchived = false")
                .list().asInstanceOf[JList[PlayerShopItem]]
                .map(r => (r.getShopItem.getName, r.getShopItem.getImageName, getShopItemLocalization(r.getShopItem.getLocales.toList, lang), r.getShopItem.getUsageType))
                .groupBy(r => r).mapValues(_.size).map(r => {
                val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
                item.setAmount(r._2)
                item.setCost(0)
                item.setImageName(r._1._2)
                item.setName(r._1._1)
                item.setDescription(r._1._3)
                item.setUsageType(r._1._4)
                item.build()
              }).toList
            } else List.empty[MessageResponseShopItemBase.MessageResponseShopItem]

          case eShopItemType.sitINVENTORYWITHSHOP =>
            if (playerId.getOrElse(0L) > 0) {
              val query = getSessionFactoryDao.getCurrentSession.createSQLQuery("SELECT si.name, si.image_name, count(psi.id), si.usage_type" +
                " FROM shop_item si" +
                " LEFT JOIN player_shop_item psi ON psi.shop_item_fk = si.id" +
                s" WHERE coalesce(psi.player_fk, :pId) = :pId" +
                " AND coalesce(psi.is_archived, false) = false" +
                s" AND si.item_type not in ('${ShopItemType.MONEY}', '${ShopItemType.VIDEOAD}')" +
                s" AND si.is_visible = true" +
                s" AND si.is_archived = false" +
                " GROUP BY si.name, si.image_name, si.usage_type")
              query.setParameter("pId", playerId.get)
              query.list().asInstanceOf[JList[Array[Object]]].map(r => {
                val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
                item.setAmount(r(2).asInstanceOf[java.math.BigInteger].intValue())
                item.setCost(0)
                item.setImageName(r(1).asInstanceOf[String])
                item.setName(r(0).asInstanceOf[String])
                item.setDescription("")
                item.setUsageType(ShopItemUsageType.fromString(r(3).asInstanceOf[String]))
                item.build()
              }).toList
            } else List.empty[MessageResponseShopItemBase.MessageResponseShopItem]

          case eShopItemType.sitVIDEOAD =>
            getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.ShopItem WHERE" +
              s" itemType = '${ShopItemType.VIDEOAD}'" +
              s" AND isVisible = true" +
              s" AND isArchived = false")
              .list().asInstanceOf[JList[ShopItem]].map(r => {
              val item = MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
              item.setAmount(0)
              item.setCost(r.getCost)
              item.setImageName(r.getImageName)
              item.setName(r.getName)
              item.setDescription(getShopItemLocalization(r.getLocales.toList, lang))
              item.setUsageType(r.getUsageType)
              item.build()
            }).toList
        }
      }, ro = true).get.toOption
        .getOrElse(List.empty[MessageResponseShopItemBase.MessageResponseShopItem])
    }

    private def getShopItemLocalization(locales: List[ShopItemLocale], lang: String): String = {
      locales.find(r => r.getLocale.toLowerCase.equals(lang.toLowerCase)) match {
        case None => ""
        case Some(sil: ShopItemLocale) => sil.getDescription
      }
    }

    private def makeRoomInfo(ri: RoomInfo) = {
      val roomInfoBuilder = MessageResponseRoomInfoBase.MessageResponseRoomInfo.newBuilder()
      roomInfoBuilder.setRoomId(ri.roomId)
      roomInfoBuilder.setBet(ri.bet)
      roomInfoBuilder.setMaxRounds(ri.maxRounds)
      roomInfoBuilder.setCurrentRound(ri.currentRound)
      roomInfoBuilder.setShootDirection(ri.shootDirection)
      roomInfoBuilder.setMaxPlayers(ri.maxPlayers)
      roomInfoBuilder.setAmountPlayers(ri.currentPlayersAmount)
      roomInfoBuilder.setInvestorbank(ri.investorBank)
      roomInfoBuilder.setPlayerbank(ri.playerBank)
      roomInfoBuilder.setIsGameStarted(ri.isGameStarted)
      roomInfoBuilder
    }

    private def msgRoomPlayerNeedAuth() {
      sendSocketMessage(eProtoMessageType.cmtNeedAuth, None)
    }

    private def msgPlayerBet(roomId: Long, sourcePlayerId: Long, destPlayerId: Long, betType: PlayerBetWinType, amount: Long) {
      val msgResponse = MessageResponsePlayerBetBase.MessageResponsePlayerBet.newBuilder()
      msgResponse.setRoomId(roomId)
      msgResponse.setSourcePlayerId(sourcePlayerId)
      msgResponse.setDestPlayerId(destPlayerId)
      msgResponse.setAmount(amount)
      msgResponse.setWinType(betType)
      sendSocketMessage(eProtoMessageType.cmtPlayerBet, msgResponse)
    }

    private def doBuyShopItem(shopItemName: String, itemType: eItemType, isGameCash: Boolean): eBuyErrorType = {
      var result = eBuyErrorType.betNone

      val player = getPlayerDao.load(playerId.get)
      var itemsToAdd = List.empty[ShopItem]
      val balanceAmount: Option[Long] = itemType match {
        case eItemType.itItem =>
          Option(getShopItemDao.searchUniqueName(shopItemName)) match {
            case None =>
              result = eBuyErrorType.betInternalError
              None

            case Some(shopItem) =>
              itemsToAdd = List(shopItem)
              Some(if (isGameCash) player.getMoney - shopItem.getCost else player.getMoney)
          }

        case eItemType.itItemCollection =>
          Option(getShopItemCollectionDao.searchUniqueName(shopItemName)) match {
            case None =>
              result = eBuyErrorType.betInternalError
              None

            case Some(shopItemCollection) =>
              shopItemCollection.getItems.foreach(r => {
                for (i <- 1 to r.getAmount) {
                  itemsToAdd ::= r.getItem
                }
              })
              val moneyBuy = itemsToAdd.count(_.getItemType == ShopItemType.MONEY)
              Some(if (isGameCash) player.getMoney - shopItemCollection.getCost
              else player.getMoney + moneyBuy)
          }
      }

      if (balanceAmount.getOrElse(0L) >= 0L) {
        if (itemsToAdd.nonEmpty && result == eBuyErrorType.betNone) {
          player.setMoney(balanceAmount.get)
          itemsToAdd.filterNot(_.getItemType == ShopItemType.MONEY).foreach(r => {
            getPlayerShopItemDao.create(PlayerShopItem.Factory.newInstance(LocalDateTime.now(), r, player))
          })
        }
      }
      else {
        result = eBuyErrorType.betMoneyLessThenNeed
      }

      result
    }

    def authUser(msg: MessageRequestAuthBase.MessageRequestAuth): Either[MessageResponseAuth.eAuthErrorType, (Long, String)] = {
      val namePattern = "\\w*\\.*\\-*@?".r
      val (authType, authLoginO, needVerify) = msg.getAuthType match {
        case eAuthType.atAppleGameCenter => (AuthType.APPLEGAMECENTER, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), false)
        case eAuthType.atGooglePlay => (AuthType.GOOGLEPLAY, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), false)
        case _ => (AuthType.EMAIL, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), true)
      }
      val passwordO = Option(msg.getPassword).flatMap(x => if (x.trim.isEmpty) None else Some("\\w*".r.findAllIn(x.trim).take(32).mkString("")))
      val verifyCodeO = Option(msg.getVerifyCode).flatMap(x => if (x.trim.isEmpty) None else Some("\\d*".r.findAllIn(x.trim).take(6).mkString("")))
      authLoginO match {
        case Some(authLogin) =>
          if (passwordO.isEmpty || (needVerify && verifyCodeO.isEmpty)) {
            Left(MessageResponseAuth.eAuthErrorType.aetNotAllRequiredFields)
          } else {
            doInThreadTransaction[Either[MessageResponseAuth.eAuthErrorType, (Long, String)]]({
              getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
                s" authType = :authType" +
                s" AND (marketUID = :login OR email = :login)")
                .setParameter("authType", authType.value())
                .setParameter("login", authLogin)
                .list().asInstanceOf[JList[AbstractUser]].headOption match {
                case None => Left(MessageResponseAuth.eAuthErrorType.aetBadUID)
                case Some(x) =>
                  if (x.getIsBlocked)
                    Left(MessageResponseAuth.eAuthErrorType.aetBlocked)
                  else {
                    (passwordO, verifyCodeO) match {
                      case (None, None) => Left(MessageResponseAuth.eAuthErrorType.aetNoPassOrVerify)
                      case (Some(pass), None) =>
                        val md5 = DigestUtils.getMd5Digest
                        md5.reset()
                        if (x.getIsVerify && x.getPassword == Hex.encodeHex(md5.digest(pass.getBytes)).mkString) {
                          getUserSessionDao.load(sessionId).setUser(x)
                          Right(x.getId.longValue(), x.getDisplayName)
                        } else {
                          if (!x.getIsVerify)
                            Left(MessageResponseAuth.eAuthErrorType.aetNeedVerify)
                          else
                            Left(MessageResponseAuth.eAuthErrorType.aetNoPassOrVerify)
                        }
                      case (None, Some(verifyCode)) =>
                        if (x.getVerifyCode == verifyCode) {
                          x.setIsVerify(true)
                          getUserSessionDao.load(sessionId).setUser(x)
                          Right(x.getId.longValue(), x.getDisplayName)
                        } else {
                          Left(MessageResponseAuth.eAuthErrorType.aetNoPassOrVerify)
                        }
                      case (_, _) => Left(MessageResponseAuth.eAuthErrorType.aetBadUID)
                    }
                  }
              }
            }).get.get
          }
        case None => Left(MessageResponseAuth.eAuthErrorType.aetBadUID)
      }
    }

    def registerUser(msg: MessageRequestRegistrationBase.MessageRequestRegistration): Either[MessageResponseAuth.eAuthErrorType, Long] = {
      val namePattern = "\\w*\\.*\\-*@?".r
      val (authType, authLoginO, needVerify) = msg.getAuthType match {
        case eAuthType.atAppleGameCenter => (AuthType.APPLEGAMECENTER, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), false)
        case eAuthType.atGooglePlay => (AuthType.GOOGLEPLAY, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), false)
        case _ => (AuthType.EMAIL, Option(msg.getLogin).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase)), true)
      }
      val passwordO = Option(msg.getPassword).flatMap(x => if (x.trim.isEmpty) None else Some("\\w*".r.findAllIn(x.trim).take(32).mkString("")))
      val displayNameO = Option(msg.getDisplayName).flatMap(x => if (x.trim.isEmpty) None else Some("\\w*".r.findAllIn(x.trim).take(15).mkString("")))
      (authLoginO, passwordO, displayNameO) match {
        case (Some(authLogin), Some(password), Some(displayName)) =>
          doInThreadTransaction[Either[MessageResponseAuth.eAuthErrorType, Long]]({
            val checkNotUsedLogin = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
              " marketUID = :login" +
              " OR email = :login")
              .setParameter("login", authLogin)
              .list().isEmpty
            if (checkNotUsedLogin) {
              val verifyCode = Stream.continually(scala.util.Random.nextInt(100)).take(3).mkString("")
              val md5 = DigestUtils.getMd5Digest
              md5.reset()
              val encryptedPassword = Hex.encodeHex(md5.digest(password.getBytes)).mkString
              val newUser = getPlayerDao.create(Player.Factory.newInstance(UserRoleType.USER, authType, encryptedPassword, displayName, verifyCode, LocalDateTime.now(), LocalDateTime.now()))
              playerAddDefaultItems(newUser.getId.longValue())
              if (needVerify) {
                newUser.setEmail(authLogin)
                context.parent ! EmailNotification(newUser.getEmail, "Email verification", s"Email verification code: $verifyCode")
                Left(MessageResponseAuth.eAuthErrorType.aetNeedVerify)
              } else {
                newUser.setMarketUID(authLogin)
                newUser.setIsVerify(true)
                Right(newUser.getId)
              }
            } else {
              Left(MessageResponseAuth.eAuthErrorType.aetBadUID)
            }
          }).get.get
        case (_, _, _) => Left(MessageResponseAuth.eAuthErrorType.aetNotAllRequiredFields)
      }
    }

    def forgotPassword(msg: MessageRequestForgotPasswordBase.MessageRequestForgotPassword): MessageResponseAuth.eAuthErrorType = {
      val namePattern = "\\w*\\.*\\-*@?".r
      val authLoginO = Option(msg.getEmail).flatMap(x => if (x.trim.isEmpty) None else Some(namePattern.findAllIn(x.trim).take(60).mkString("").toLowerCase))
      authLoginO match {
        case Some(authLogin) =>
          val replyTo = context.parent
          doInThreadTransaction({
            getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
              " email = :login")
              .setParameter("login", authLogin)
              .list().asInstanceOf[JList[AbstractUser]].headOption match {
              case None => MessageResponseAuth.eAuthErrorType.aetBadUID
              case Some(player) =>
                val newPassword = scala.util.Random.alphanumeric.take(10).mkString
                val md5 = DigestUtils.getMd5Digest
                md5.reset()
                val hash1 = md5.digest(newPassword.getBytes)
                val hash1Str = Hex.encodeHex(hash1).mkString
                val hash2 = md5.digest(hash1Str.getBytes)
                val encryptedPassword = Hex.encodeHex(hash2).mkString
                //log.info(s">>> Hash1($hash1Str) Hash2($encryptedPassword)")
                player.setPassword(encryptedPassword)
                replyTo ! EmailNotification(player.getEmail, "Password changed", s"Your new password: $newPassword")
                MessageResponseAuth.eAuthErrorType.aetPasswordChanged
            }
          }).get.get
        case _ => MessageResponseAuth.eAuthErrorType.aetNotAllRequiredFields
      }
    }

    def playerAddDefaultItems(userId: Long) {
      val player = getPlayerDao.load(userId)
      player.setMoney(player.getMoney + 5000)
      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.ShopItem WHERE" +
        s" itemType <> '${ShopItemType.MONEY}'" +
        s" AND isVisible = true" +
        s" AND isArchived = false")
        .list().asInstanceOf[JList[ShopItem]].foreach(r => {
        r.getName match {
          case "brr_armored_bullet" | "brr_broken_bullet" =>
            for (i <- 1 to 12)
              getPlayerShopItemDao.create(PlayerShopItem.Factory.newInstance(LocalDateTime.now(), null, false, r, player))
          case "brr_helmet" =>
            for (i <- 1 to 2)
              getPlayerShopItemDao.create(PlayerShopItem.Factory.newInstance(LocalDateTime.now(), null, false, r, player))
          case "brr_change_shoot_direction" =>
            for (i <- 1 to 5)
              getPlayerShopItemDao.create(PlayerShopItem.Factory.newInstance(LocalDateTime.now(), null, false, r, player))
          case _ =>
        }
      })
    }

    def getOrCreateRoomPlayerActor(roomId: Long): ActorRef = {
      val actorName = s"RoomPlayerActor:$roomId:$sessionId"
      context.child(actorName).fold(context.actorOf(RoomPlayerActor.props(roomId), actorName))(x => x)
    }

    override def postStop() {
      super.postStop()
      log.info(s">>> Stopping $self")
    }

    def createUserSession() = {
      doInThreadTransaction({
        getUserSessionDao.create(UserSession.Factory.newInstance(ipAddress, LocalDateTime.now())).getId
      }).get.get
    }
  }

}