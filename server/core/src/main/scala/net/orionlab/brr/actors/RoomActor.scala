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

object RoomActor {

  import net.orionlab.brr.actors.RoomManager.RoomPlanned2Stop
  import net.orionlab.brr.actors.UserActor._
  import net.orionlab.brr.actors.BotManager.CreateRoomBots
  import net.orionlab.brr.actors.RoomPlayerActor.{PlayerInfoAmount, RoomInit}
  import net.orionlab.brr.actors.UserManager.ClientDisconnected2Room
  import java.util.{Date ⇒ JDate}
  import akka.actor._
  import concurrent.duration._
  import net.orionlab.brr.domain._
  import net.orionlab.brr.utils.CoreTransaction
  import org.joda.time.{LocalDateTime, Period}
  import ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType
  import collection.JavaConversions._
  import java.util.{List => JList}
  import java.lang.{Long => JLong}
  import scala.annotation.tailrec
  import scala.util._
  import net.orionlab.brr.utils.CoreUtils._

  sealed trait RoomState

  sealed trait RoomData

  def props(roomId: Long,
            roomType: RoomType,
            bet: Int,
            maxRounds: Int,
            currentCound: Int,
            maxPlayers: Int,
            timeout2Start: Int,
            timeout2RotateDrum: Int,
            timeout2Shoot: Int,
            timeout2Result: Int,
            timeout2End: Int) = {
    Props(classOf[RoomActor],
      roomId,
      roomType,
      bet,
      maxRounds,
      currentCound: Int,
      maxPlayers,
      timeout2Start,
      timeout2RotateDrum,
      timeout2Shoot,
      timeout2Result,
      timeout2End)
  }

  def generateNextRound(room: Room, nextRound: Int)(implicit roomRoundDao: RoomRoundDao): RoomRound = {
    val shootDirection = if (math.round(math.random) % 2 == 0) RoundShootDirectionType.RIGHT else RoundShootDirectionType.LEFT

    val roundType =
      if (nextRound == 4) RoomRoundType.CHOOSE_DUELIST
      else if (nextRound > 4) RoomRoundType.DUEL
      else RoomRoundType.ROUND

    room.setCurrentRound(nextRound)
    val newRoomRound = roomRoundDao.create(RoomRound.Factory.newInstance(roundType, shootDirection, LocalDateTime.now(), room))
    newRoomRound.setRound(nextRound)

    newRoomRound
  }

  case class GetRoomListByType(roomType: RoomType)

  case class GetRoomPlayers(roomId: Long)

  case class SetRoomPlayer(roomId: Long, player: RoomPlayer)

  case class RoomPlayer(playerActor: ActorRef, sessionId: Long, var playerId: Option[Long], var playerName: Option[String], var playerType: PlayerType, var position: Int, var shootDirection: Option[PlayerShootDirectionType] = None)

  case class RoomInfo2Room(roomId: Long)

  case class RoomInfo2Player(roomInfo: RoomInfo)

  case class RoomRoundPlayerResult(playerId: Long, playerPosition: Int, killedPlayerId: Long, killedPlayerPosition: Int, killReason: KillReasonType, hasBullet: Boolean, var winAmount: Long)

  case class RoomRoundPlayerDuelist(playerId: Long, position: Int, isDuelist: Boolean, winAmount: Long)

  case class RoomInfo(roomId: Long, bet: Int, maxRounds: Int, currentRound: Int, maxPlayers: Int, currentPlayersAmount: Int, playerBank: Long, investorBank: Long, shootDirection: RoundShootDirectionType, isGameStarted: Boolean)

  case class RoomListAmountByType(roomType: RoomType, amount: Int)

  case class Ready2Start2Player(roomId: Long, time: Int, round: Int, shootDirection: RoundShootDirectionType, isChooseDuelist: Boolean, isDuel: Boolean)

  case class Ready2PutBullets2Player(roomId: Long, time: Int, possibleBullets: Int)

  case class Ready2RotateDrum2Player(roomId: Long, time: Int)

  case class Ready2Shoot2Player(roomId: Long, time: Int)

  case class Ready2RoundResult2Player(roomId: Long, time: Int, roundResult: Iterable[RoomRoundPlayerResult])

  case class Ready2DuelistResult2Player(roomId: Long, time: Int, duelists: Iterable[RoomRoundPlayerDuelist])

  case class Ready2End2Player(roomId: Long, gameWinner: Option[RoomRoundPlayerResult])

  case object RoomIsFinish

  class RoomActor(roomId: Long,
                  roomType: RoomType,
                  bet: Int,
                  maxRounds: Int,
                  var currentRound: Int,
                  maxPlayers: Int,
                  timeout2Start: Int,
                  timeout2RotateDrum: Int,
                  timeout2Shoot: Int,
                  timeout2Result: Int,
                  timeout2End: Int) extends Actor with ActorLogging with FSM[RoomState, RoomData] with CoreTransaction {

    import context.dispatcher

    private val supportedLocalizationList = List("en", "ru")
    private val defaultLocalization = supportedLocalizationList.head
    private val minPlayerInRoomToPlay = 2
    private var players = List.empty[RoomPlayer]
    private var possibleBullets = currentRound
    private var isGameStarted = false
    private var killerId = 0L
    private var gameWinner = Option.empty[RoomRoundPlayerResult]

    @scala.throws[Exception](classOf[Exception])
    override def preStart(): Unit = {
      super.preStart()
      doInThreadTransaction({
        getSessionFactoryDao.getCurrentSession.createQuery("SELECT id FROM net.orionlab.brr.domain.AbstractUser WHERE" +
          s" role = '${UserRoleType.KILLER}'")
          .setMaxResults(1)
          .list().asInstanceOf[JList[JLong]].headOption
      }, ro = true).get.toOption.foreach(_.foreach(killerId = _))
    }

    startWith(RSWaiting4Player, RDNoData)

    when(RSWaiting4Player) {
      case Event(RoomPlanned2Stop, _) =>
        doInThreadTransaction({
          val room = getRoomDao.load(roomId)
          getCurrentRound(room).foreach(rr => {
            rr.setIsFinish(true)
          })
          roomFinish(room)
        })
        stay()

      case Event(msg: SetRoomPlayer, _) =>
        val parent = context.parent
        val replyTo = sender()
        doInThreadTransaction({
          getCurrentRound(getRoomDao.load(roomId)) match {
            case None =>
              log.error(s">>> Room($roomId) cant find current round State($stateName).")
              false
            case Some(rr) =>
              setRoundDates(rr)
              newPlayerConnected(rr, msg, parent, replyTo)
              true
          }
        }).get match {
          case Success(s) =>
            if (s) goto(RSReady2Start) using RDChangeStateNoData
            else stay()
          case Failure(f) =>
            stay()
        }
    }

    when(RSReady2Start) {
      case Event(msg: ScheduledStateChange, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
        } else {
         doInThreadTransaction({
            getCurrentRound(getRoomDao.load(roomId)) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) =>
                log.info(s"$stateName($msg) round(${rr.getStageStartEnd}) current(${new JDate})")
                players.foreach(sendPlayerCurrentRoundState(rr, _))
            }
          }, ro = true).get
        }
        stay()

      case Event(msg: SetPistolBullets2Room, _) =>
        if (!Array(6, 12).contains(msg.bullets.length))
          log.error(s"Player(${sender()}) send bullets(${msg.bullets.length}) != (6 or 12)")
        else {
          players.find(r => r.playerActor == sender() && r.playerType == PlayerType.PLAYER) match {
            case None => log.error(s"Cant find Player(${sender()}) at Room($roomId)")
            case Some(player) =>
              player.playerId match {
                case None => log.error(s"RoomPlayer($player) found but playerId is empty.")
                case Some(playerId) =>
                  doInThreadTransaction({
                    getCurrentRound(getRoomDao.load(roomId)) match {
                      case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                      case Some(rr) =>
                        log.info(s"$msg ${msg.bullets.mkString(",")}")
                        getPlayerBullets(rr, playerId, PistolType.PISTOL1) match {
                          case Left(x) =>
                            val bullets = (Array(msg.bullets(0), msg.bullets(1), msg.bullets(2), msg.bullets(3), msg.bullets(4), msg.bullets(5)), Array(false, false, false, false, false, false), Array(false, false, false, false, false, false))
                            setPlayerBullets(rr, playerId, PistolType.PISTOL1, shuffleBullets(bullets))
                          case Right(x) => log.error(s">>> Room($roomId) Round(${rr.getId}) Player(${player.playerId.getOrElse(0L)}) already insert bullets.")
                        }
                    }
                  }).get
              }
          }
        }
        stay()

      case Event(msg: UsePlayerItem2Room, _) =>
        val sourceIsPlayer = players.exists(r => r.playerActor == sender() && r.playerId.getOrElse(0L) == msg.sourcePlayerId && r.playerType == PlayerType.PLAYER)
        val destIsPlayer = players.exists(r => r.playerId.getOrElse(0L) == msg.destPlayerId && r.playerType == PlayerType.PLAYER)

        if (sourceIsPlayer && destIsPlayer) {
          doInThreadTransaction({
            val room = getRoomDao.load(roomId)
            getCurrentRound(room) match {
              case None =>
                log.error(s">>> Room($roomId) cant find current round State($stateName).")
                None
              case Some(rr) =>
                getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.PlayerShopItem WHERE" +
                  s" shopItem.name = '${msg.itemName}'" +
                  s" AND isArchived = false")
                  .list().asInstanceOf[JList[PlayerShopItem]].headOption match {
                  case None =>
                  case Some(playerItem) =>
                    val sourcePlayer = getPlayerDao.load(msg.sourcePlayerId)
                    val destPlayer = getPlayerDao.load(msg.destPlayerId)
                    playerItem.setIsArchived(true)
                    getRoundPlayerUsedItemDao.create(RoundPlayerUsedItem.Factory.newInstance(LocalDateTime.now(), playerItem.getShopItem, sourcePlayer, destPlayer, rr))

                    players.foreach(_.playerActor ! UsePlayerItem2Player(roomId, msg.itemName, msg.sourcePlayerId, msg.destPlayerId))

                    val multiplier = roomType match {
                      case RoomType.TINY => 1
                      case RoomType.SMALL => 2
                      case RoomType.BIG => 3
                      case RoomType.MEDIUM => 4
                    }

                    val amount = (playerItem.getShopItem.getCost * multiplier).toLong

                    val betWinType = if (msg.destPlayerId == msg.sourcePlayerId) PlayerBetWinType.pbwtWin else PlayerBetWinType.pbwtLose
                    getRoundPlayerBetDao.create(RoundPlayerBet.Factory.newInstance(amount, betWinType, true, LocalDateTime.now(), null, false, sourcePlayer, destPlayer, rr))
                    room.setPlayerBank(room.getPlayerBank + amount)
                    val playerBetMsg = PlayerBet2Player(roomId, msg.sourcePlayerId, msg.destPlayerId, betWinType, amount)
                    players.foreach(_.playerActor ! playerBetMsg)

                    playerItem.getShopItem.getItemType match {
                      case ShopItemType.BULLET ⇒
                        val rndBullet = Random.nextInt(6)
                        val destPlayerBullets = getPlayerBullets(rr, msg.destPlayerId, PistolType.PISTOL1) match {
                          case Left(x) => x
                          case Right(x) => x
                        }

                        if (playerItem.getShopItem.getName.toLowerCase.contains("broken")) {
                          destPlayerBullets._2(rndBullet) = true
                        }

                        if (playerItem.getShopItem.getName.toLowerCase.contains("armored")) {
                          destPlayerBullets._3(rndBullet) = true
                        }

                        setPlayerBullets(rr, msg.destPlayerId, PistolType.PISTOL1, destPlayerBullets)

                      case _ ⇒
                    }
                }
            }
          }).get
        }
        stay()

      case Event(msg: ScheduledStateTimeOut, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateTimeOut(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          if (players.count(r => r.playerType == PlayerType.PLAYER) < minPlayerInRoomToPlay) {
            goto(RSReady2End) using RDChangeStateNoData
          }
          else {
            if (!isGameStarted) {
              doInThreadTransaction[Boolean]({
                getCurrentRound(getRoomDao.load(roomId)) match {
                  case None =>
                    log.error(s">>> Room($roomId) cant find current round State($stateName).")
                    false
                  case Some(rr) => log.info(s"$stateName($msg) round(${rr.getStageStartEnd}) current(${new JDate})")
                    val room = getRoomDao.load(roomId)
                    room.setIsGameStarted(true)
                    true
                }
              }).get().toOption.foreach(isGameStarted = _)
            }
            goto(RSReady2RotateDrum) using RDChangeStateNoData
          }
        }
    }

    when(RSReady2RotateDrum) {
      case Event(msg: ScheduledStateChange, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          doInThreadTransaction({
            getCurrentRound(getRoomDao.load(roomId)) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) =>
                log.info(s"$stateName($msg) round(${rr.getStageRotateDrumEnd}) current(${new JDate})")
                players.foreach(sendPlayerCurrentRoundState(rr, _))
            }
          }, ro = true).get
        }
        stay()
      case Event(msg: RotateDrum2Room, _) =>
        doInThreadTransaction({
          getCurrentRound(getRoomDao.load(roomId)) match {
            case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
            case Some(rr) =>
              players.find(r => r.playerActor == sender() && r.playerType == PlayerType.PLAYER) match {
                case None => log.error(s"Cant find Player(${sender()}) at Room($roomId)")
                case Some(player) =>
                  player.playerId match {
                    case None => log.error(s"RoomPlayer($player) found but playerId is empty.")
                    case Some(playerId) =>
                      val bullets = getPlayerBullets(rr, playerId, PistolType.PISTOL1) match {
                        case Left(x) => x
                        case Right(x) => x
                      }
                      setPlayerBullets(rr, playerId, PistolType.PISTOL1, shuffleBullets(bullets))
                  }
              }
          }
        }).get
        players.foreach(_.playerActor ! RotateDrum2Player(roomId, msg.playerId))
        stay()
      case Event(msg: PlayerBang2Room, _) =>
        players.find(r => r.playerActor == sender() && r.playerType == PlayerType.PLAYER) match {
          case None => log.error(s"Cant find Player(${sender()}) at Room($roomId)")
          case Some(player) =>
            player.playerId match {
              case None => log.error(s"Player($player) found but playerId is empty.")
              case Some(shootPlayerId) =>
                doInThreadTransaction({
                  getCurrentRound(getRoomDao.load(roomId)) match {
                    case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                    case Some(rr) =>
                      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerShoot WHERE" +
                        s" round.id = ${rr.getId}" +
                        s" AND player.id = ${player.playerId.get}")
                        .list().asInstanceOf[JList[RoundPlayerShoot]].headOption match {
                        case None =>
                          val playerShoot = getRoundPlayerShootDao.create(RoundPlayerShoot.Factory.newInstance(LocalDateTime.now(), getPlayerDao.load(player.playerId.get), rr))
                          getPlayersBulletsAndItems(rr).find(_.playerId == shootPlayerId).foreach(x => {
                            playerShoot.setHasBullet(x.hasBullet)
                            playerShoot.setHasArmoredBullet(x.hasArmoredBullet)
                            playerShoot.setHasBrokenBullet(x.hasBrokenBullet)
                            playerShoot.setHasHelmet(x.usedItems.contains(ShopItemType.HELMET.value()))
                          })

                          val playerBangResult = RoomRoundPlayerResult(killerId, 0, shootPlayerId, player.position, KillReasonType.KILLED_BY_KILLER_EARLY_SHOOT, false, 0)
                          processKilledPlayers(rr, List(playerBangResult))
                          players.foreach(_.playerActor ! PlayerBang2Player(roomId, playerBangResult))
                        case Some(_) => log.info(s"Player($player) is already shoot.")
                      }
                  }
                }).get
            }
        }
        stay()
      case Event(msg: ScheduledStateTimeOut, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateTimeOut(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          doInThreadTransaction({
            getCurrentRound(getRoomDao.load(roomId)) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) => log.info(s"$stateName($msg) round(${rr.getStageRotateDrumEnd}) current(${new JDate})")
            }
          }, ro = true).get
          goto(RSReady2Shoot) using RDChangeStateNoData
        }
    }

    when(RSReady2Shoot) {
      case Event(msg: ScheduledStateChange, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          doInThreadTransaction({
            getCurrentRound(getRoomDao.load(roomId)) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) =>
                log.info(s"$stateName($msg) round(${rr.getStageShootEnd}) current(${new JDate})")
                players.foreach(sendPlayerCurrentRoundState(rr, _))
            }
          }, ro = true).get
        }
        stay()
      case Event(msg: PlayerBang2Room, _) =>
        players.find(r => r.playerActor == sender() && r.playerType == PlayerType.PLAYER) match {
          case None => log.error(s"Cant find Player(${sender()}) at Room($roomId)")
          case Some(player) =>
            player.playerId match {
              case None => log.error(s"Player($player) found but playerId is empty.")
              case Some(shootPlayerId) =>
                doInThreadTransaction({
                  getCurrentRound(getRoomDao.load(roomId)) match {
                    case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                    case Some(rr) =>
                      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerShoot WHERE" +
                        s" round.id = ${rr.getId}" +
                        s" AND player.id = $shootPlayerId")
                        .list().asInstanceOf[JList[RoundPlayerShoot]].headOption match {
                        case None =>
                          val playerShoot = getRoundPlayerShootDao.create(RoundPlayerShoot.Factory.newInstance(LocalDateTime.now(), getPlayerDao.load(shootPlayerId), rr))
                          val playerBulletsItems = getPlayersBulletsAndItems(rr)
                          playerBulletsItems.find(_.playerId == shootPlayerId).foreach(x => {
                            playerShoot.setHasBullet(x.hasBullet)
                            playerShoot.setHasArmoredBullet(x.hasArmoredBullet)
                            playerShoot.setHasBrokenBullet(x.hasBrokenBullet)
                            playerShoot.setHasHelmet(x.usedItems.contains(ShopItemType.HELMET.value()))
                          })

                          val result = getPlayerBangResult(playerShoot, playerBulletsItems)
                          log.info(s"\n>>> PlayerBangResult($shootPlayerId) $result")
                          processKilledPlayers(rr, List(result))
                          players.foreach(_.playerActor ! PlayerBang2Player(roomId, result))

                        case Some(_) => log.info(s"Player($player) is already shoot.")
                      }
                  }
                }).get
            }
        }
        stay()
      case Event(msg: ScheduledStateTimeOut, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateTimeOut(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          doInThreadTransaction({
            val room = getRoomDao.load(roomId)
            getCurrentRound(room) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) => log.info(s"$stateName($msg) round(${rr.getStageResultEnd}) current(${new JDate})")
            }
          }, ro = true).get
          goto(RSReady2Result) using RDChangeStateNoData
        }
    }

    when(RSReady2ChooseDuelist) {
      case Event(msg: ScheduledStateChange, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
        } else {
          doInThreadTransaction({
            val room = getRoomDao.load(roomId)
            getCurrentRound(room) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) =>
                log.info(s"$stateName($msg) round(${rr.getStageStartEnd}) current(${new JDate})")
                val playersAsPlayer = players.filter(r => r.playerType == PlayerType.PLAYER)
                val posAsDuelist = generateDuelistPos(playersAsPlayer, List.empty)
                val winMoneyAvgPerPlayer = if (room.getPlayerBank > 0 && posAsDuelist.nonEmpty) room.getPlayerBank / posAsDuelist.size else 0L

                playersAsPlayer.foreach(r => {
                  val playerDuelist = RoundPlayerDuelist.Factory.newInstance(LocalDateTime.now(), rr)
                  val isDuelist = posAsDuelist.contains(r.position)
                  playerDuelist.setPos(playersAsPlayer.indexOf(r) + 1)
                  playerDuelist.setIsDuelist(isDuelist)
                  playerDuelist.setWinAmount(if (!isDuelist) winMoneyAvgPerPlayer else 0L)
                  getRoundPlayerDuelistDao.create(playerDuelist)
                })

                players.foreach(sendPlayerCurrentRoundState(rr, _))
            }
          }).get
        }
        stay()
      case Event(msg: RoomPlayerDuelists2Room, _) =>
        val replyTo = sender()
        doInThreadTransaction({
          getCurrentRound(getRoomDao.load(roomId)) match {
            case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
            case Some(rr) =>
              val duelists = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerDuelist WHERE" +
                s" round.id = ${rr.getId}")
                .list().asInstanceOf[JList[RoundPlayerDuelist]].map(r => {
                Option(r.getPlayer) match {
                  case None => RoomRoundPlayerDuelist(0, r.getPos, r.getIsDuelist, 0L)
                  case Some(dp) => RoomRoundPlayerDuelist(dp.getId, r.getPos, r.getIsDuelist, r.getWinAmount)
                }
              }).toList
              replyTo ! RoomPlayerDuelists2Player(roomId, duelists)
          }
        }, ro = true)
        stay()
      case Event(msg: SetRoomPlayerDuelist2Room, _) =>
        if (msg.position > 6) {
          log.error(s"\n>>> Requested impossible duelist position($msg)")
        } else {
          players.find(r => r.playerActor == sender() && r.playerType == PlayerType.PLAYER) match {
            case None => log.warning(s"Cant find Player(${sender()}) at Room($roomId) or it was marked as not duelist.")
            case Some(player) =>
              if (player.playerId.isEmpty)
                log.error(s"RoomPlayer($player) found but playerId is empty (need auth?) state($stateName).")
              else {
                doInThreadTransaction({
                  val room = getRoomDao.load(roomId)
                  getCurrentRound(room) match {
                    case None =>
                      log.error(s">>> Room($roomId) cant find current round State($stateName).")
                      None
                    case Some(rr) =>
                      val duelists = getSessionFactoryDao.getCurrentSession.createQuery(s"FROM net.orionlab.brr.domain.RoundPlayerDuelist WHERE" +
                        s" round.id = ${rr.getId}")
                        .list().asInstanceOf[JList[RoundPlayerDuelist]]

                      duelists.find(x => Option(x.getPlayer).isDefined && x.getPlayer.getId == player.playerId.get) match {
                        case None =>
                          duelists.find(x => x.getPos == msg.position && Option(x.getPlayer).isEmpty) match {
                            case None =>
                              val duel = duelists.map(xx => (xx.getId, Option(xx.getPlayer).map(_.getId), xx.getIsDuelist))
                              log.info(s"Player(${player.playerId.get}) requested busy position(${msg.position}) duelists($duel).")
                              None
                            case Some(duelist) =>
                              if (!duelist.getIsDuelist) {
                                player.playerType = PlayerType.WATCHER
                                if (duelist.getWinAmount > 0) {
                                  room.setPlayerBank(room.getPlayerBank - duelist.getWinAmount)
                                  val playerDB = getPlayerDao.load(player.playerId.get)
                                  playerDB.setMoney(playerDB.getMoney + duelist.getWinAmount)
                                }
                              }
                              duelist.setPlayer(getPlayerDao.load(player.playerId.get))
                              Some(SetRoomPlayerDuelist2Player(roomId, RoomRoundPlayerDuelist(player.playerId.get, duelist.getPos, duelist.getIsDuelist, duelist.getWinAmount)))
                          }
                        case Some(_) => log.info(s"Player(${player.playerId.get}) is already choose position.")
                          None
                      }
                  }
                }).get.toOption.foreach(_.foreach(res => players.foreach(_.playerActor ! res)))
              }
          }
        }
        stay()
      case Event(msg: ScheduledStateTimeOut, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateTimeOut(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          doInThreadTransaction({
            val room = getRoomDao.load(roomId)
            getCurrentRound(room) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) => log.info(s"$stateName($msg) round(${rr.getStageStartEnd}) current(${new JDate})")
            }
          }).get
          goto(RSReady2Result) using RDChangeStateNoData
        }
    }

    when(RSReady2Result) {
      case Event(msg: ScheduledStateChange, RDChangeStateNoData) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          if (currentRound == 4) {
            doInThreadTransaction({
              val room = getRoomDao.load(roomId)
              getCurrentRound(room) match {
                case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                case Some(rr) =>
                  log.info(s"$stateName($msg) round(${rr.getStageResultEnd}) current(${new JDate})")
                  val playerDuelists = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerDuelist WHERE" +
                    s" round.id = ${rr.getId}" +
                    " and isArchived = false")
                    .list().asInstanceOf[JList[RoundPlayerDuelist]]

                  var usedPlayers = playerDuelists.flatMap(x ⇒ Option(x.getPlayer).map(_.getId)).toList
                  val duelists = playerDuelists.flatMap(duelist ⇒ {
                    Option(duelist.getPlayer) match {
                      case None =>
                        livePlayers().find(p ⇒ !usedPlayers.contains(p.playerId.get)).map(player ⇒ {
                          val playerDB = getPlayerDao.load(player.playerId.get)
                          duelist.setPlayer(playerDB)
                          usedPlayers ::= duelist.getPlayer.getId
                          if (!duelist.getIsDuelist) {
                            player.playerType = PlayerType.WATCHER
                            if (duelist.getWinAmount > 0) {
                              room.setPlayerBank(room.getPlayerBank - duelist.getWinAmount)
                              playerDB.setMoney(playerDB.getMoney + duelist.getWinAmount)
                            }
                            getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
                              s" round.id = ${rr.getId}" +
                              s" AND session.id = ${player.sessionId}")
                              .list().asInstanceOf[JList[RoundPlayer]].headOption.foreach(roundPlayer ⇒ {
                              roundPlayer.setPlayerType(player.playerType)
                              roundPlayer.setDateEdit(LocalDateTime.now())
                            })
                            getRoundPlayerResultDao.create(RoundPlayerResult.Factory.newInstance(KillReasonType.FREE_AS_NOT_DUELIST, player.position, 0, duelist.getWinAmount, LocalDateTime.now(), null, false, rr, playerDB, null))
                          }
                          RoomRoundPlayerDuelist(duelist.getPlayer.getId, duelist.getPos, duelist.getIsDuelist, duelist.getWinAmount)
                        })

                      case Some(dp) =>
                        Some(RoomRoundPlayerDuelist(duelist.getPlayer.getId, duelist.getPos, duelist.getIsDuelist, duelist.getWinAmount))
                    }
                  })

                  log.info(s"\n>>> DuelistResult($duelists)")

                  players.foreach(sendPlayerCurrentRoundState(rr, _, None, Some(duelists)))
              }
            }).get
          } else {
            doInThreadTransaction({
              val room = getRoomDao.load(roomId)
              getCurrentRound(room) match {
                case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                case Some(rr) =>
                  log.info(s"$stateName($msg) round(${rr.getStageShootEnd}) current(${new JDate})")
                  players.foreach(sendPlayerCurrentRoundState(rr, _))
                  var roundResult: List[RoomRoundPlayerResult] = {
                    val roundPlayerResult = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerResult WHERE" +
                      s" round.id = ${rr.getId}")
                      .list().asInstanceOf[JList[RoundPlayerResult]]
                      .map(x => (x.getPlayer.getId, Option(x.getKilledPlayer).fold(0L)(r => r.getId)))
                    livePlayers().flatMap(r => {
                      if (roundPlayerResult.exists(x => x._1 == r.playerId.get || x._2 == r.playerId.get))
                        None
                      else
                        Some(RoomRoundPlayerResult(killerId, 0, r.playerId.get, r.position, KillReasonType.KILLED_BY_KILLER_NOSHOOT, true, 0L))
                    })
                  }
                  processKilledPlayers(rr, roundResult)

                  val tmpLivePlayers = livePlayers()

                  log.info(s"\nRoundResult shootDirection(${rr.getShootDirection.value()})" +
                    s"\nresult($roundResult)")

                  if (currentRound == 7 && tmpLivePlayers.length >= minPlayerInRoomToPlay) {
                    val playerWillBeWinner = tmpLivePlayers(Random.nextInt(tmpLivePlayers.length))

                    tmpLivePlayers.find(x => x.playerId.get == playerWillBeWinner.playerId.get).foreach(x => {
                      val player = getPlayerDao.load(x.playerId.get)
                      val newPlayerResult = getRoundPlayerResultDao.create(RoundPlayerResult.Factory.newInstance(KillReasonType.FREE_AS_WINNER, 0, 0, room.getPlayerBank, LocalDateTime.now(), null, false, rr, player, null))
                      room.setPlayerBank(0L)
                      player.setWins(player.getWins + 1)
                      player.setMoney(player.getMoney + newPlayerResult.getWinAmount)
                      gameWinner = Some(RoomRoundPlayerResult(player.getId, 0, 0, 0, KillReasonType.FREE_AS_WINNER, false, newPlayerResult.getWinAmount))
                    })

                    roundResult ++= tmpLivePlayers.filter(_.playerId.get != playerWillBeWinner.playerId.get).map(x => {
                      RoomRoundPlayerResult(killerId, 0, x.playerId.get, x.position, KillReasonType.KILLED_BY_KILLER_GAMEOVER, true, 0L)
                    })

                    processKilledPlayers(rr, roundResult)
                  } else if (currentRound != 4 && tmpLivePlayers.length < minPlayerInRoomToPlay) {
                    tmpLivePlayers.headOption.foreach(x => {
                      val player = getPlayerDao.load(x.playerId.get)
                      val newPlayerResult = getRoundPlayerResultDao.create(RoundPlayerResult.Factory.newInstance(KillReasonType.FREE_AS_WINNER, 0, 0, room.getPlayerBank, LocalDateTime.now(), null, false, rr, player, null))
                      room.setPlayerBank(0L)
                      player.setWins(player.getWins + 1)
                      player.setMoney(player.getMoney + newPlayerResult.getWinAmount)
                      gameWinner = Some(RoomRoundPlayerResult(player.getId, 0, 0, 0, KillReasonType.FREE_AS_WINNER, false, newPlayerResult.getWinAmount))
                    })
                  }

                  players.foreach(sendPlayerCurrentRoundState(rr, _, Some(roundResult)))
              }
            }).get
          }
          stay()
        }
      case Event(msg: ScheduledStateTimeOut, _) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateTimeOut(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          goto(RSReady2End) using RDChangeStateNoData
        }
    }

    when(RSReady2End) {
      case Event(msg: ScheduledStateChange, RDChangeStateNoData) =>
        if (msg.state != stateName) {
          log.error(s"ScheduledStateChange(${msg.state}) != currentState($stateName)")
          stay()
        } else {
          val amountPlayers = players.count(r => r.playerType == PlayerType.PLAYER)
          doInThreadTransaction[RoomState]({
            val room = getRoomDao.load(roomId)
            getCurrentRound(room) match {
              case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              case Some(rr) =>
                log.info(s"$stateName($msg) round(${rr.getStageEndEnd}) current(${new JDate})")
                rr.setIsFinish(true)
            }
            if (amountPlayers < minPlayerInRoomToPlay) {
              roomFinish(room)
              stateName
            } else {
              val nr = calculateNextRound()
              //            log.info(s"currentRound($currentRound) nextRound($nr)")
              nr match {
                case 2 | 3 | 5 | 6 | 7 =>
                  val nextRound = generateNextRound(false)
                  setRoundDates(nextRound)
                  RSReady2Start
                case 4 =>
                  val nextRound = generateNextRound(true)
                  setRoundDates(nextRound)
                  RSReady2ChooseDuelist
                case 8 =>
                  roomFinish(room)
                  stateName
              }
            }
          }).get.toOption match {
            case None => stay()
            case Some(st) =>
              if (st == stateName) stay()
              else goto(st) using RDChangeStateNoData
          }
        }
    }

    whenUnhandled {
      case Event(msg: SetRoomPlayer, _) =>
        val parent = context.parent
        val replyTo = sender()
        doInThreadTransaction({
          getCurrentRound(getRoomDao.load(roomId)) match {
            case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
            case Some(rr) => newPlayerConnected(rr, msg, parent, replyTo)
          }
        }).get
        stay()

      case Event(msg: AuthUser2Room, _) =>
        players.find(_.playerActor == sender()) match {
          case None => log.error(s"Cant find Actor(${sender()}) to set PlayerId(${msg.playerId}) State($stateName)")
          case Some(rp: RoomPlayer) =>
            rp.playerId = Some(msg.playerId)
            rp.playerName = Some(msg.playerName)
        }
        stay()

      case Event(msg: GetRoomListByType, _) =>
        if (roomType == msg.roomType) {
          getRoomInfo match {
            case None =>
            case Some(ri: RoomInfo) => sender() ! ri
          }
        }
        stay()

      case Event(msg: RoomInfo2Room, _) =>
        if (msg.roomId == roomId) {
          getRoomInfo match {
            case None =>
            case Some(ri: RoomInfo) => sender() ! RoomInfo2Player(ri)
          }
        }
        stay()

      case Event(msg: ClientDisconnected2Room, _) =>
        players.find(r => r.playerActor == sender()) match {
          case None =>
          case Some(rp: RoomPlayer) =>
            players = players.filter(_ != rp)
            if (rp.playerType == PlayerType.PLAYER)
              players.foreach(_.playerActor ! PlayerExit2Player(roomId, rp.playerId.get, rp.position))
        }
        stay()

      case Event(msg: PlayerExit2Room, _) =>
        log.info(msg.toString)
        players.find(r => r.playerActor == sender()) match {
          case None =>
          case Some(rp: RoomPlayer) =>
            players = players.filter(_ != rp)
            if (rp.playerType == PlayerType.PLAYER) {
              players.foreach(_.playerActor ! PlayerExit2Player(roomId, rp.playerId.get, rp.position))
            }
        }
        stay()

      case Event(msg: GetRoomPlayers, _) =>
        if (msg.roomId == roomId) {
          val answerTo = sender()
          val actorsAsPlayers = players.filter(_.playerType == PlayerType.PLAYER).sortBy(_.position)
          if (isGameStarted) {
            //            log.info(s"PlayerInfoAmount(${actorsAsPlayers.size}) to actor(${sender()})")
            answerTo ! PlayerInfoAmount(actorsAsPlayers.size)
            actorsAsPlayers.foreach(p => answerTo ! RoomPlayerInfo(p.playerId.get, p.playerName.get, p.position, Array.empty, p.shootDirection.get))
          } else {
            if (actorsAsPlayers.isEmpty) {
              //                log.info(s"PlayerInfoAmount($maxPlayers) to actor(${sender()})")
              doInThreadTransaction({
                getCurrentRound(getRoomDao.load(roomId)) match {
                  case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                  case Some(rr) =>
                    answerTo ! PlayerInfoAmount(maxPlayers)
                    (1 to maxPlayers).foreach(r => {
                      answerTo ! RoomPlayerInfo(0, "", r, Array.empty, rr.getShootDirection)
                    })
                }
              }, ro = true)
            } else {
              doInThreadTransaction({
                getCurrentRound(getRoomDao.load(roomId)) match {
                  case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
                  case Some(rr) =>
                    val tmpPlayers = generateAbsentPlayers(rr.getShootDirection, actorsAsPlayers, List.empty)
                    //                      log.info(s"GetRoomPlayers($tmpPlayers)")
                    answerTo ! PlayerInfoAmount(tmpPlayers.size)
                    tmpPlayers.foreach(x => answerTo ! RoomPlayerInfo(x.playerId, x.playerName, x.position, Array.empty, x.shootDirection))
                }
              }, ro = true)
            }
          }
        }
        stay()

      case Event(msg: SetPlayerTypeAndPosition2Room, _) =>
        val parent = context.parent
        val replyTo = sender()
        doInThreadTransaction({
          getCurrentRound(getRoomDao.load(roomId)) match {
            case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
            case Some(rr) =>
              players.find(p => p.playerActor == sender()) match {
                case None => log.error(s"Player(${sender()}) not found at Room($self)")
                case Some(rp) => newPlayerConnected(rr, SetRoomPlayer(roomId, rp.copy(playerType = msg.playerType, position = msg.position)), parent, replyTo)
              }
          }
        }).get
        stay()

      case any =>
        log.error(s">>> Unhandled message '$any' at State($stateName)")
        stay()
    }

    onTransition {
      case RSWaiting4Player -> RSReady2Start =>
        self ! ScheduledStateChange(RSReady2Start)
        context.system.scheduler.scheduleOnce(timeout2Start.millis, self, ScheduledStateTimeOut(RSReady2Start))
      case RSReady2Start -> RSReady2End =>
        self ! ScheduledStateChange(RSReady2End)
      case RSReady2Start -> RSReady2RotateDrum =>
        self ! ScheduledStateChange(RSReady2RotateDrum)
        context.system.scheduler.scheduleOnce(timeout2RotateDrum.millis, self, ScheduledStateTimeOut(RSReady2RotateDrum))
      case RSReady2RotateDrum -> RSReady2Shoot =>
        self ! ScheduledStateChange(RSReady2Shoot)
        context.system.scheduler.scheduleOnce(timeout2Shoot.millis, self, ScheduledStateTimeOut(RSReady2Shoot))
      case RSReady2Shoot -> RSReady2Result =>
        self ! ScheduledStateChange(RSReady2Result)
        context.system.scheduler.scheduleOnce(timeout2Result.millis, self, ScheduledStateTimeOut(RSReady2Result))
      case RSReady2Result -> RSReady2End =>
        self ! ScheduledStateChange(RSReady2End)
      case RSReady2End -> RSReady2Start =>
        self ! ScheduledStateChange(RSReady2Start)
        context.system.scheduler.scheduleOnce(timeout2Start.millis, self, ScheduledStateTimeOut(RSReady2Start))
      case RSReady2End -> RSReady2ChooseDuelist =>
        self ! ScheduledStateChange(RSReady2ChooseDuelist)
        context.system.scheduler.scheduleOnce(timeout2Start.millis, self, ScheduledStateTimeOut(RSReady2ChooseDuelist))
      case RSReady2ChooseDuelist -> RSReady2Result =>
        self ! ScheduledStateChange(RSReady2Result)
        context.system.scheduler.scheduleOnce(timeout2Result.millis, self, ScheduledStateTimeOut(RSReady2Result))
    }

    @tailrec
    private def generateDuelistPos(players: List[RoomPlayer], positions: List[Int]): List[Int] = {
      if (positions.size == minPlayerInRoomToPlay) {
        positions
      } else {
        val rndPlayerIdx = scala.util.Random.nextInt(livePlayers().size)
        val playerByIdx = players(rndPlayerIdx)
        if (positions.contains(playerByIdx.position)) generateDuelistPos(players, positions)
        else generateDuelistPos(players, playerByIdx.position :: positions)
      }
    }

    case class PlayerBulletsItems(playerId: Long, hasBullet: Boolean, hasArmoredBullet: Boolean, hasBrokenBullet: Boolean, usedItems: List[String])

    def getPlayersBulletsAndItems(roomRound: RoomRound): List[PlayerBulletsItems] = {
      val playerItems = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerUsedItem WHERE" +
        s" round.id = ${roomRound.getId}" +
        s" AND dateCreate >= '${roomRound.getStageStartStart}'" +
        s" AND dateCreate <= '${roomRound.getStageStartEnd}'")
        .list().asInstanceOf[JList[RoundPlayerUsedItem]]
        .map(r => (r.getDestPlayer.getId, r.getUsedItem.getItemType))

      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerBullet WHERE" +
        s" round.id = ${roomRound.getId}" +
        s" AND dateCreate >= '${roomRound.getStageStartStart}'" +
        s" AND dateCreate <= '${roomRound.getStageStartEnd}'")
        .list().asInstanceOf[JList[RoundPlayerBullet]]
        .map(r => {
          PlayerBulletsItems(r.getPlayer.getId.toLong, r.getB6, r.getB6armored, r.getB6broken, playerItems.flatMap(x => if (r.getPlayer.getId == x._1) Some(x._2.value()) else None).toList)
        }).toList
    }

    def getPlayerBangResult(playerShoot: RoundPlayerShoot, pbi: List[PlayerBulletsItems]): RoomRoundPlayerResult = {
      val roundPlayers = livePlayers().flatMap(x => {
        pbi.find(_.playerId == x.playerId.get).map(r => {
          val shootDate = if (r.playerId == playerShoot.getPlayer.getId) Some(LocalDateTime.fromDateFields(playerShoot.getDateCreate)) else None
          TMPRoundPlayer(
            r.playerId,
            x.position,
            x.shootDirection.get,
            shootDate,
            r.hasBullet,
            r.hasArmoredBullet,
            r.hasBrokenBullet,
            r.usedItems.contains(ShopItemType.HELMET.value()),
            None,
            None)
        })
      }).sortWith(_.position > _.position)

      findNeighbor(roundPlayers)

      roundPlayers.find(x => x.playerId == playerShoot.getPlayer.getId &&
        x.shootDate.isDefined &&
        x.shootDate.get.isAfter(LocalDateTime.fromDateFields(playerShoot.getRound.getStageShootStart)) &&
        x.shootDate.get.isBefore(LocalDateTime.fromDateFields(playerShoot.getRound.getStageShootEnd))) match {
        case Some(roundRes) =>
          val nextPlayer: Option[TMPRoundPlayer] = roundRes.shootDirection match {
            case PlayerShootDirectionType.LEFT ⇒
              roundPlayers.find(x ⇒ x.playerId == roundRes.playerId).fold(Option.empty[TMPRoundPlayer])(x ⇒ {
                if (x.prev.getOrElse(roundRes.playerId) == roundRes.playerId) None
                else roundPlayers.find(_.playerId == x.prev.get)
              })
            case PlayerShootDirectionType.RIGHT ⇒
              roundPlayers.find(x ⇒ x.playerId == roundRes.playerId).fold(Option.empty[TMPRoundPlayer])(x ⇒ {
                if (x.next.getOrElse(roundRes.playerId) == roundRes.playerId) None
                else roundPlayers.find(_.playerId == x.next.get)
              })
            case _ => None
          }

          nextPlayer match {
            case None =>
              log.info(s"Cant find enemy for Player(${roundRes.playerId}) at Room($roomId) Round(${playerShoot.getRound.getId}) State($stateName)")
              // противник не найден
              RoomRoundPlayerResult(roundRes.playerId, roundRes.position, 0L, 0, KillReasonType.ENEMY_NOT_FOUND, roundRes.isHasBullet, 0L)
            case Some(rp) =>
              if (!roundRes.isHasBullet) {
                // у игрока нету патрона
                RoomRoundPlayerResult(roundRes.playerId, roundRes.position, 0L, 0, KillReasonType.NO_BULLET, false, 0L)
              }
              else if (roundRes.isBulletBroken) {
                // у игрока сломаный патрон, никого не убил
                RoomRoundPlayerResult(roundRes.playerId, roundRes.position, 0L, 0, KillReasonType.BROKEN_BULLET, false, 0L)
              }
              else if (roundRes.isBulletArmored) {
                // у игрока бронированый патрон, убил противника
                roundRes.isBulletArmored = false
                roundRes.isHasBullet = false
                RoomRoundPlayerResult(roundRes.playerId, roundRes.position, rp.playerId, rp.position, KillReasonType.KILLED_BY_PLAYER, true, 0L)
              }
              else {
                roundRes.isHasBullet = false
                if (rp.isHasHelmet) {
                  // у противника шлем, не убил
                  rp.isHasHelmet = false
                  RoomRoundPlayerResult(roundRes.playerId, roundRes.position, 0L, 0, KillReasonType.ENEMY_HAS_HELMET, true, 0L)
                }
                else {
                  // у противника нету шлема, убил
                  RoomRoundPlayerResult(roundRes.playerId, roundRes.position, rp.playerId, rp.position, KillReasonType.KILLED_BY_PLAYER, true, 0L)
                }
              }
          }
        case None =>
          val p = livePlayers().find(_.playerId.get == playerShoot.getPlayer.getId).get
          RoomRoundPlayerResult(killerId, 0, p.playerId.get, p.position, KillReasonType.KILLED_BY_KILLER_NOSHOOT, false, 0L)
      }
    }

    def livePlayers() = players.filter(_.playerType == PlayerType.PLAYER)

    def processKilledPlayers(roomRound: RoomRound, roundResults: List[RoomRoundPlayerResult]) {
      // PlayerBangResult(74) RoomRoundPlayerResult(74,5,275,3,KILLED_BY_PLAYER,true,0)
      val playerIds = roundResults.flatMap(x => x.playerId :: List(x.killedPlayerId)).toSet
      val foundPlayers = livePlayers().filter(x => playerIds.contains(x.playerId.get))
      roundResults.foreach(roundRes ⇒ {
        val killedPlayer = foundPlayers.find(_.playerId.get == roundRes.killedPlayerId).map(kp => (getPlayerDao.load(kp.playerId.get), kp))
        killedPlayer.foreach(x => {
          x._2.playerType = PlayerType.WATCHER
          x._1.setLoses(x._1.getLoses + 1)
          getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
            s" round.id = ${roomRound.getId}" +
            s" AND session.id = ${x._2.sessionId}")
            .list().asInstanceOf[JList[RoundPlayer]].headOption.foreach(rp ⇒ {
            rp.setPlayerType(x._2.playerType)
            rp.setDateEdit(LocalDateTime.now())
          })
        })
        foundPlayers.find(_.playerId.get == roundRes.playerId).foreach(r => {
          getRoundPlayerResultDao.create(RoundPlayerResult.Factory.newInstance(
            roundRes.killReason, roundRes.playerPosition,
            roundRes.killedPlayerPosition, roundRes.winAmount,
            LocalDateTime.now(), null, false,
            roomRound, getPlayerDao.load(roundRes.playerId), killedPlayer.fold(null.asInstanceOf[Player])(x => x._1)))
        })
      })
    }

    def findNeighbor(otherPlayers: List[TMPRoundPlayer]): Unit = {
      if (otherPlayers.nonEmpty) {
        val player = otherPlayers.head
        val newOtherPlayers = otherPlayers.tail
        val nextPlayer = newOtherPlayers.headOption.getOrElse(player)
        if (player.prev.isEmpty) {
          val prevPlayer = newOtherPlayers.lastOption.getOrElse(player)
          player.prev = Some(player.prev.getOrElse(prevPlayer.playerId))
          prevPlayer.next = Some(prevPlayer.next.getOrElse(player.playerId))
        }
        if (player.next.isEmpty) {
          player.next = Some(player.next.getOrElse(nextPlayer.playerId))
          nextPlayer.prev = Some(nextPlayer.prev.getOrElse(player.playerId))
        }
        if (newOtherPlayers.nonEmpty)
          findNeighbor(newOtherPlayers)
      }
    }

    private def getPlayerBullets(round: RoomRound, playerId: Long, pistolType: PistolType) = {
      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerBullet WHERE" +
        s" player.id = $playerId" +
        s" AND round.room.id = $roomId" +
        s" AND round.id = ${round.getId}")
        .list().asInstanceOf[JList[RoundPlayerBullet]].headOption match {
        case None => Left(
          (Array(false, false, false, false, false, false),
            Array(false, false, false, false, false, false),
            Array(false, false, false, false, false, false)))
        case Some(pb) =>
          Right(
            (Array(Boolean.unbox(pb.getB1), Boolean.unbox(pb.getB2), Boolean.unbox(pb.getB3), Boolean.unbox(pb.getB4), Boolean.unbox(pb.getB5), Boolean.unbox(pb.getB6)),
              Array(Boolean.unbox(pb.getB1broken), Boolean.unbox(pb.getB2broken), Boolean.unbox(pb.getB3broken), Boolean.unbox(pb.getB4broken), Boolean.unbox(pb.getB5broken), Boolean.unbox(pb.getB6broken)),
              Array(Boolean.unbox(pb.getB1armored), Boolean.unbox(pb.getB2armored), Boolean.unbox(pb.getB3armored), Boolean.unbox(pb.getB4armored), Boolean.unbox(pb.getB5armored), Boolean.unbox(pb.getB6armored))))
      }
    }

    private def shuffleBullets(bullets: (Array[Boolean], Array[Boolean], Array[Boolean])) = {
      val roundCount = Random.nextInt(15)

      for (round <- 0 to roundCount) {
        val p1Buf = bullets._1.clone()
        val p1IsBrokenBuf = bullets._2.clone()
        val p1IsArmoredBuf = bullets._3.clone()

        for (j <- 0 to 5) {
          if (j == 0) {
            bullets._1(j) = p1Buf(5)
            bullets._2(j) = p1IsBrokenBuf(5)
            bullets._3(j) = p1IsArmoredBuf(5)
          } else {
            bullets._1(j) = p1Buf(j - 1)
            bullets._2(j) = p1IsBrokenBuf(j - 1)
            bullets._3(j) = p1IsArmoredBuf(j - 1)
          }
        }
      }

      bullets
    }

    override def postStop() {
      super.postStop()
      log.info(s">>> Stopping $self")
    }

    @tailrec
    private def generateAbsentPlayers(roundShootDirection: RoundShootDirectionType, sourcePlayers: List[RoomPlayer], destPlayers: List[RoomPlayerInfo]): List[RoomPlayerInfo] = {
      if (destPlayers.isEmpty) {
        generateAbsentPlayers(roundShootDirection, sourcePlayers, sourcePlayers.map(x => {
          RoomPlayerInfo(x.playerId.get, x.playerName.get, x.position, Array.empty, x.shootDirection.get)
        }))
      } else {
        1.to(maxPlayers).filterNot(x => destPlayers.map(_.position).contains(x)).headOption match {
          case None => destPlayers.sortBy(_.position)
          case Some(x) =>
            val newPlayer = RoomPlayerInfo(0, "", x, Array.empty, roundShootDirection)
            generateAbsentPlayers(roundShootDirection, sourcePlayers, newPlayer :: destPlayers)
        }
      }
    }

    def newPlayerConnected(roomRound: RoomRound, inPlayer: SetRoomPlayer, parent: ActorRef, replyTo: ActorRef) = {
      stateName match {
        case RSWaiting4Player =>
          if (players.isEmpty && inPlayer.player.playerType == PlayerType.WATCHER) {
            inPlayer.player.position = 0
            inPlayer.player.shootDirection = Some(roomRound.getShootDirection)
            players +:= inPlayer.player
            inPlayer.player.playerActor ! RoomInit(roomId)
            getRoundPlayerDao.create(RoundPlayer.Factory.newInstance(inPlayer.player.playerType, roomRound.getShootDirection, LocalDateTime.now(), getUserSessionDao.load(inPlayer.player.sessionId), roomRound))
            parent ! CreateRoomBots(roomId)
          }
        case RSReady2Start =>
          players.find(r => r.playerActor == inPlayer.player.playerActor) match {
            // текущий игрок не найден
            case None =>
              //            log.info(s"player(${inPlayer.player.playerId.getOrElse(0L)}) not found at Round(${roomRound.getId}) at State($stateName) trying to send RoomInit to actor(${inPlayer.player.playerActor})")
              if (inPlayer.player.playerType == PlayerType.WATCHER) {
                inPlayer.player.position = 0
                getRoundPlayerDao.create(RoundPlayer.Factory.newInstance(inPlayer.player.playerType, roomRound.getShootDirection, LocalDateTime.now(), getUserSessionDao.load(inPlayer.player.sessionId), roomRound))
                players +:= inPlayer.player
                inPlayer.player.playerActor ! RoomInit(roomId)
              }
            // текущий игрок найден
            case Some(rp: RoomPlayer) =>
              //            log.info(s"player(${inPlayer.player.playerId.getOrElse(0L)}) found at Round(${roomRound.getId}) at State($stateName) trying to send RoomInit to actor(${inPlayer.player.playerActor})")
              rp.playerId match {
                case None => replyTo ! NeedAuth2Player
                case Some(_) =>
                  if (isGameStarted) {
                    // Игра стартовала и игрок хочет выйти
                    if (rp.playerType == PlayerType.PLAYER && inPlayer.player.playerType == PlayerType.WATCHER) {
                      rp.playerType = PlayerType.WATCHER
                      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
                        s" round.id = ${roomRound.getId}" +
                        s" AND session.id = ${rp.sessionId}" +
                        s" AND playerType = '${PlayerType.PLAYER}'" +
                        " AND isArchived = false")
                        .list().asInstanceOf[JList[RoundPlayer]].headOption match {
                        case None => log.error(s"Cant find Player(${rp.playerId.getOrElse(0L)}) Session(${rp.sessionId}) at Round(${roomRound.getId}) to set Watcher")
                        case Some(x) =>
                          x.setPlayerType(PlayerType.WATCHER)
                          players.foreach(_.playerActor ! PlayerExit2Player(roomId, rp.playerId.get, rp.position))
                      }
                    }
                  } else {
                    val playerByPos = playerByPosition(inPlayer.player.position)
                    (rp.playerType, inPlayer.player.playerType) match {
                      // зритель хочет стать игроком
                      case (PlayerType.WATCHER, PlayerType.PLAYER) =>
                        val player = getPlayerDao.load(rp.playerId.get)

                        if (player.getRole == UserRoleType.BOT || player.getMoney - roomRound.getRoom.getBet >= 0) {
                          if (playerByPos.isEmpty) {
                            rp.playerType = PlayerType.PLAYER
                            rp.position = inPlayer.player.position
                            rp.shootDirection = Some(roomRound.getShootDirection)
                            getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
                              s" round.id = ${roomRound.getId}" +
                              s" AND session.id = ${rp.sessionId}" +
                              s" AND playerType = '${PlayerType.WATCHER}'" +
                              " AND isArchived = false")
                              .list().asInstanceOf[JList[RoundPlayer]].headOption match {
                              case None => log.error(s"Cant find Player(${rp.playerId.getOrElse(0L)}) Session(${rp.sessionId}) at Round(${roomRound.getId}) to set Watcher -> Player.")
                              case Some(x) =>
                                player.setMoney(player.getMoney - roomRound.getRoom.getBet)
                                roomRound.getRoom.setPlayerBank(roomRound.getRoom.getPlayerBank + roomRound.getRoom.getBet)
                                x.setPlayerType(PlayerType.PLAYER)
                                x.setPos(rp.position)
                                val playerTypePos = SetPlayerTypeAndPosition2Player(roomId, RoomPlayerInfo(rp.playerId.get, rp.playerName.get, rp.position, Array.empty, rp.shootDirection.get))
                                players.foreach(_.playerActor ! playerTypePos)
                                val playerBet = PlayerBet2Player(roomId, rp.playerId.get, rp.playerId.get, PlayerBetWinType.pbwtWin, roomRound.getRoom.getBet.toLong)
                                players.foreach(_.playerActor ! playerBet)
                                val putBullets = Ready2PutBullets2Player(roomId, 0, possibleBullets)
                                players.foreach(_.playerActor ! putBullets)
                            }
                          }
                        }
                        else {
                          rp.playerActor ! NoMoney2Player(player.getMoney.toLong, roomRound.getRoom.getBet.toLong)
                        }
                      // игрок хочет стать зрителем
                      case (PlayerType.PLAYER, PlayerType.WATCHER) =>
                        getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
                          s" round.id = ${roomRound.getId}" +
                          s" AND session.id = ${rp.sessionId}" +
                          s" AND playerType = '${PlayerType.PLAYER}'" +
                          " AND isArchived = false")
                          .list().asInstanceOf[JList[RoundPlayer]].headOption match {
                          case None => log.error(s"Cant find Player(${rp.playerId.getOrElse(0L)}) Session(${rp.sessionId}) at Round(${roomRound.getId}) to set Player -> Watcher.")
                          case Some(x) =>
                            x.setPlayerType(PlayerType.WATCHER)
                            x.setPos(rp.position)
                            rp.position = 0
                            val playerTypePos = SetPlayerTypeAndPosition2Player(roomId, RoomPlayerInfo(rp.playerId.get, rp.playerName.get, rp.position, Array.empty, rp.shootDirection.get))
                            rp.playerType = PlayerType.WATCHER
                            rp.shootDirection = None
                            players.foreach(_.playerActor ! playerTypePos)
                        }
                      // игрок хочет занять другое место
                      case (PlayerType.PLAYER, PlayerType.PLAYER) =>
                        getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayer WHERE" +
                          s" round.id = ${roomRound.getId}" +
                          s" AND session.id = ${rp.sessionId}" +
                          s" AND playerType = '${PlayerType.PLAYER}'" +
                          " AND isArchived = false")
                          .list().asInstanceOf[JList[RoundPlayer]].headOption match {
                          case None => log.error(s"Cant find Player(${rp.playerId.getOrElse(0L)}) Session(${rp.sessionId}) at Round(${roomRound.getId}) to set Player -> Player")
                          case Some(x) =>
                            if (playerByPos.isEmpty && isPlayerPositionValid(inPlayer.player.position)) {
                              rp.playerType = PlayerType.WATCHER
                              rp.position = 0
                              var playerTypePos = SetPlayerTypeAndPosition2Player(roomId, RoomPlayerInfo(rp.playerId.get, rp.playerName.get, rp.position, Array.empty, rp.shootDirection.get))
                              players.foreach(_.playerActor ! playerTypePos)

                              rp.playerType = PlayerType.PLAYER
                              rp.position = inPlayer.player.position
                              x.setPos(rp.position)
                              rp.shootDirection = Some(roomRound.getShootDirection)
                              playerTypePos = SetPlayerTypeAndPosition2Player(roomId, RoomPlayerInfo(rp.playerId.get, rp.playerName.get, rp.position, Array.empty, rp.shootDirection.get))
                              players.foreach(_.playerActor ! playerTypePos)
                            }
                        }
                      case any => log.info(s">>> Unhandled setPlayer tuple $any")
                    }
                  }
              }
          }
        case RSReady2RotateDrum | RSReady2Shoot | RSReady2ChooseDuelist | RSReady2Result | RSReady2End =>
          players.find(r => r.playerActor == inPlayer.player.playerActor) match {
            // текущий игрок не найден
            case None =>
              if (inPlayer.player.playerType == PlayerType.WATCHER) {
                inPlayer.player.position = 0
                players +:= inPlayer.player
                inPlayer.player.playerActor ! RoomInit(roomId)
              }
            case _ =>
          }
        case _ =>
      }
      sendPlayerCurrentRoundState(roomRound, inPlayer.player)
    }

    def sendPlayerCurrentRoundState(roomRound: RoomRound, roomPlayer: RoomPlayer,
                                    roundResults: Option[Iterable[RoomRoundPlayerResult]] = None,
                                    roundDuelists: Option[Iterable[RoomRoundPlayerDuelist]] = None) = {
      stateName match {
        case RSWaiting4Player =>
        case RSReady2Start =>
          val time = (roomRound.getStageStartEnd.getTime - System.currentTimeMillis()) / 1000
          roomPlayer.playerActor ! Ready2Start2Player(roomId, time.toInt, roomRound.getRound, roomRound.getShootDirection, false, currentRound > 4)
          roomPlayer.playerActor ! Ready2PutBullets2Player(roomId, time.toInt, possibleBullets)
        case RSReady2RotateDrum =>
          val time = (roomRound.getStageRotateDrumEnd.getTime - System.currentTimeMillis()) / 1000
          roomPlayer.playerActor ! Ready2RotateDrum2Player(roomId, time.toInt)
        case RSReady2Shoot =>
          val time = (roomRound.getStageShootEnd.getTime - System.currentTimeMillis()) / 1000
          roomPlayer.playerActor ! Ready2Shoot2Player(roomId, time.toInt)
        case RSReady2ChooseDuelist =>
          val time = (roomRound.getStageStartEnd.getTime - System.currentTimeMillis()) / 1000
          roomPlayer.playerActor ! Ready2Start2Player(roomId, time.toInt, roomRound.getRound, roomRound.getShootDirection, true, false)
        case RSReady2Result =>
          roundResults.foreach(r ⇒ {
            val time = (roomRound.getStageResultEnd.getTime - System.currentTimeMillis()) / 1000
            roomPlayer.playerActor ! Ready2RoundResult2Player(roomId, time.toInt, r)
          })
          roundDuelists.foreach(r ⇒ {
            val time = (roomRound.getStageResultEnd.getTime - System.currentTimeMillis()) / 1000
            roomPlayer.playerActor ! Ready2DuelistResult2Player(roomId, time.toInt, r)
          })
        case RSReady2End =>
        case any => log.info(s">>> Unhandled state($any) at SendPlayerCurrentRoundState.")
      }
    }

    private def playerByPosition(pos: Int) = players.find(r => isPlayerPositionValid(pos) && r.position == pos && r.playerType == PlayerType.PLAYER)

    def isPlayerPositionValid(pos: Int): Boolean = pos >= 1 && pos <= maxPlayers

    def generateNextRound(isChooseDuelist: Boolean): RoomRound = {
      currentRound = calculateNextRound()
      val room = getRoomDao.load(roomId)
      val newRoomRound = RoomActor.generateNextRound(room, currentRound)(getRoomRoundDao)

      possibleBullets = if (isChooseDuelist) possibleBullets else possibleBullets + 1

      players.foreach(x ⇒ {
        x.shootDirection = Some(newRoomRound.getShootDirection)
        val session = getUserSessionDao.load(x.sessionId)
        val newRoundPlayer = RoundPlayer.Factory.newInstance(x.playerType, x.position, x.shootDirection.get, LocalDateTime.now(), null, false, session, newRoomRound)
        getRoundPlayerDao.create(newRoundPlayer)
      })

      newRoomRound
    }

    def calculateNextRound() = {
      val playersAmountAsPlayer = players.count(r => r.playerType == PlayerType.PLAYER)
      if (currentRound == 3) {
        if (playersAmountAsPlayer > minPlayerInRoomToPlay) currentRound + 1
        else currentRound + 2
      }
      else currentRound + 1
    }

    def roomFinish(room: Room): Unit = {
      log.info(s">>> RoomFinish($roomId)")
      room.setIsArchived(true)
      players.foreach(_.playerActor ! Ready2End2Player(roomId, gameWinner))
      players.foreach(_.playerActor ! RoomIsFinish)
      context.stop(self)
    }

    private def setRoundDates(round: RoomRound) {
      val stageStartStart = new LocalDateTime
      var stageStartEnd = new LocalDateTime
      var stageRotateDrumStart = Option.empty[LocalDateTime]
      var stageRotateDrumEnd = Option.empty[LocalDateTime]
      var stageShootStart = Option.empty[LocalDateTime]
      var stageShootEnd = Option.empty[LocalDateTime]
      var stageResultStart = Option.empty[LocalDateTime]
      var stageResultEnd = Option.empty[LocalDateTime]
      var stageEndStart = new LocalDateTime
      var stageEndEnd = new LocalDateTime

      if (round.getRound == 4) {
        stageStartEnd = stageStartStart.plus(Period.millis(timeout2Start))
        stageResultStart = Some(stageStartEnd)
        stageResultEnd = stageResultStart.map(_.plus(Period.millis(timeout2Result)))
        stageEndStart = stageResultEnd.get
        stageEndEnd = stageEndStart.plus(Period.millis(timeout2End))
      } else {
        stageStartEnd = stageStartStart.plus(Period.millis(timeout2Start))
        stageRotateDrumStart = Some(stageStartEnd)
        stageRotateDrumEnd = stageRotateDrumStart.map(_.plus(Period.millis(timeout2RotateDrum)))
        stageShootStart = stageRotateDrumEnd
        stageShootEnd = stageShootStart.map(_.plus(Period.millis(timeout2Shoot)))
        stageResultStart = stageShootEnd
        stageResultEnd = stageResultStart.map(_.plus(Period.millis(timeout2Result)))
        stageEndStart = stageResultEnd.get
        stageEndEnd = stageEndStart.plus(Period.millis(timeout2End))
      }

      //    log.info(s"RoundDates start(${roundStartDate.toDate}) " +
      //      s"putBullets(${putBulletsDate.toDate}) " +
      //      s"rotateDrum(${rotateDrumDate.toDate}) " +
      //      s"shoot(${shootDate.toDate}) " +
      //      s"result(${resultDate.toDate}) " +
      //      s"end(${endDate.toDate})")

      round.setStageStartStart(stageStartStart.toDate)
      round.setStageStartEnd(stageStartEnd.toDate)
      round.setStageRotateDrumStart(stageRotateDrumStart.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageRotateDrumEnd(stageRotateDrumEnd.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageShootStart(stageShootStart.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageShootEnd(stageShootEnd.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageResultStart(stageResultStart.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageResultEnd(stageResultEnd.fold(null.asInstanceOf[JDate])(_.toDate))
      round.setStageEndStart(stageEndStart.toDate)
      round.setStageEndEnd(stageEndEnd.toDate)
    }

    private def getRoomInfo: Option[RoomInfo] = {
      doInThreadTransaction({
        if (currentRound < 1) {
          log.error(s">>> Room($roomId) cant have current round = 0 State($stateName).")
          None
        }
        else {
          val room = getRoomDao.load(roomId)
          getCurrentRound(room) match {
            case None => log.error(s">>> Room($roomId) cant find current round State($stateName).")
              None
            case Some(rr) =>
              Some(RoomInfo(
                roomId,
                bet,
                maxRounds,
                room.getCurrentRound,
                maxPlayers,
                players.count(r => r.playerType == PlayerType.PLAYER),
                room.getPlayerBank,
                room.getInvestorBank,
                rr.getShootDirection,
                room.getIsGameStarted
              ))
          }
        }
      }, ro = true).get.get
    }

    private def getCurrentRound(room: Room): Option[RoomRound] = {
      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoomRound WHERE" +
        s" room.id = $roomId" +
        s" AND round = ${room.getCurrentRound}")
        .setMaxResults(1)
        .list().asInstanceOf[JList[RoomRound]].headOption
    }

    private def setPlayerBullets(round: RoomRound, playerId: Long, pistolType: PistolType, bullets: (Array[Boolean], Array[Boolean], Array[Boolean])) {
      if (bullets._1.length == 6 && bullets._2.length == 6 && bullets._3.length == 6) {
        log.info(s"setPlayerBullets bullets(${bullets._1.mkString(",")}) broken(${bullets._2.mkString(",")}) armored(${bullets._3.mkString(",")})")
        // TODO: only for duelist test >>>
        //        for (i <- 0 until bullets._1.length) {
        //          bullets._1(i) = false
        //          bullets._2(i) = false
        //          bullets._3(i) = false
        //        }
        // <<<
        val playerBullet =
          getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.RoundPlayerBullet WHERE" +
            s" player.id = $playerId" +
            s" AND round.room.id = $roomId" +
            s" AND round.id = ${round.getId}")
            .list().asInstanceOf[JList[RoundPlayerBullet]].headOption match {
            case None => getRoundPlayerBulletDao.create(RoundPlayerBullet.Factory.newInstance(pistolType, LocalDateTime.now(), getPlayerDao.load(playerId), round))
            case Some(pb: RoundPlayerBullet) => pb
          }

        playerBullet.setB1(bullets._1(0))
        playerBullet.setB2(bullets._1(1))
        playerBullet.setB3(bullets._1(2))
        playerBullet.setB4(bullets._1(3))
        playerBullet.setB5(bullets._1(4))
        playerBullet.setB6(bullets._1(5))
        playerBullet.setB1broken(bullets._2(0))
        playerBullet.setB2broken(bullets._2(1))
        playerBullet.setB3broken(bullets._2(2))
        playerBullet.setB4broken(bullets._2(3))
        playerBullet.setB5broken(bullets._2(4))
        playerBullet.setB6broken(bullets._2(5))
        playerBullet.setB1armored(bullets._3(0))
        playerBullet.setB2armored(bullets._3(1))
        playerBullet.setB3armored(bullets._3(2))
        playerBullet.setB4armored(bullets._3(3))
        playerBullet.setB5armored(bullets._3(4))
        playerBullet.setB6armored(bullets._3(5))
      }
    }

    case class TMPRoundPlayer(playerId: Long,
                              position: Int,
                              shootDirection: PlayerShootDirectionType,
                              shootDate: Option[LocalDateTime],
                              var isHasBullet: Boolean,
                              var isBulletArmored: Boolean,
                              var isBulletBroken: Boolean,
                              var isHasHelmet: Boolean,
                              var prev: Option[Long],
                              var next: Option[Long])

    case class ScheduledStateChange(state: RoomState)

    case class ScheduledStateTimeOut(state: RoomState)

    case object RSWaiting4Player extends RoomState

    case object RSReady2Start extends RoomState

    case object RSReady2RotateDrum extends RoomState

    case object RSReady2Shoot extends RoomState

    case object RSReady2ChooseDuelist extends RoomState

    case object RSReady2Result extends RoomState

    case object RSReady2End extends RoomState

    case object RDNoData extends RoomData

    case object RDChangeStateNoData extends RoomData

  }

}