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

object BotActor {

  import akka.actor._
  import net.orionlab.brr.utils.CoreTransaction

  def props(userId: Long, playerName: String) = {
    Props(classOf[BotActor], userId, playerName)
  }

  class BotActor(userId: Long, playerName: String) extends Actor with ActorLogging with CoreTransaction {

    import net.orionlab.brr.actors.UserActor._
    import net.orionlab.brr.domain.{PlayerType, UserSession}
    import net.orionlab.brr.actors.RoomManager._
    import net.orionlab.brr.actors.RoomPlayerActor._
    import net.orionlab.brr.actors.RoomActor._
    import net.orionlab.brr.actors.BotManager._
    import concurrent.duration._
    import org.joda.time.LocalDateTime
    import net.orionlab.brr.utils.CoreUtils._
    import context.dispatcher

    val sessionId = createUserSession()
    var roomId = Option.empty[Long]
    var roomActor = Option.empty[ActorRef]
    var playerInfoAmount = Int.MaxValue
    var playerInfos = List.empty[RoomPlayerInfo]
    var timeoutScheduler = Option.empty[Cancellable]

    override def postStop() {
      super.postStop()
      log.info(s"Stopping BotActor $self with RoomId(${roomId.getOrElse(0L)})")
    }

    def receive = {
      case msg: RoomPlayerInit2Room =>
        roomId = Some(msg.roomId)
        context.become(wait3RoomInit)
        sender() ! SetRoomPlayer(msg.roomId, RoomPlayer(self, sessionId, Some(userId), Some(playerName), PlayerType.WATCHER, 0, None))
        timeoutScheduler = Some(context.system.scheduler.scheduleOnce(2.seconds, self, RoomNotFound))

      case any =>
    }

    def wait3RoomInit: Receive = {
      case msg: RoomInit =>
        cancelTimeoutScheduler()
        if (msg.roomId == roomId.getOrElse(0L)) {
          roomActor = Some(sender())
          context.become(wait4RoomPlayers())
          context.system.scheduler.scheduleOnce(util.Random.nextInt(301).min(100).millis, sender(), GetRoomPlayers(roomId.get))
          timeoutScheduler = Some(context.system.scheduler.scheduleOnce(3.seconds, self, RoomNotFound))
        }
        else botGameOver()

      case RoomNotFound =>
        //      log.info("Wait4RoomInit > RoomNotFound")
        botGameOver()

      case any =>
    }

    def wait4RoomPlayers(): Receive = {
      case msg: PlayerInfoAmount =>
        playerInfoAmount = msg.amount

      case msg: RoomPlayerInfo =>
        playerInfos ::= msg

        if (playerInfos.size == playerInfoAmount) {
          cancelTimeoutScheduler()
          val emptyPositions = playerInfos.filter(r => r.playerId == 0)
          //        log.info(s"emptyPositions(${emptyPositions.length})")

          if (emptyPositions.isEmpty) {
            //          log.info("EmptyPositions is empty.")
            botGameOver()
          } else {
            val rndPos = util.Random.nextInt(emptyPositions.length)
            playerInfoAmount = Int.MaxValue
            playerInfos = List.empty[RoomPlayerInfo]
            context.become(wait4ChoosePosition())
            roomActor.get ! SetPlayerTypeAndPosition2Room(roomId.get, PlayerType.PLAYER, emptyPositions(rndPos).position)
            timeoutScheduler = Some(context.system.scheduler.scheduleOnce(3.seconds, self, RoomNotFound))
          }
        }

      case RoomNotFound =>
        //      log.info("Wait4RoomPlayers > StateTimeout")
        botGameOver()

      case any =>
    }

    def wait4ChoosePosition(): Receive = {
      case msg: SetPlayerTypeAndPosition2Player =>
        cancelTimeoutScheduler()
        playerInfos.find(p => p.position == msg.playerInfo.position) match {
          case None =>
          case Some(x) => x.playerId = msg.playerInfo.playerId
        }
        context.become(ready2Play())

      case RoomNotFound =>
        //      log.info("Wait4ChoosePosition > StateTimeout")
        context.become(wait4RoomPlayers())
        playerInfoAmount = Int.MaxValue
        playerInfos = List.empty[RoomPlayerInfo]
        roomActor.foreach(_ ! GetRoomPlayers(roomId.get))
        timeoutScheduler = Some(context.system.scheduler.scheduleOnce(3.seconds, self, RoomNotFound))

      case any =>
    }

    def ready2Play(): Receive = {
      case msg: SetPlayerTypeAndPosition2Player =>
        cancelTimeoutScheduler()
        playerInfos.find(p => p.position == msg.playerInfo.position) match {
          case None =>
          case Some(x) => x.playerId = msg.playerInfo.playerId
        }

      case msg: Ready2Start2Player =>

      case msg: Ready2PutBullets2Player =>
        val bullets = 1.to(6).map(r => r <= msg.possibleBullets).toArray
        roomActor.foreach(_ ! SetPistolBullets2Room(roomId.get, bullets))

      case msg: Ready2RotateDrum2Player =>
        context.system.scheduler.scheduleOnce(util.Random.nextInt(1001).min(800).millis, roomActor.get, RotateDrum2Room(roomId.get, userId))

      case msg: RotateDrum2Player =>
        if (math.random % 2 == 0)
          context.system.scheduler.scheduleOnce(util.Random.nextInt(1001).min(800).millis, roomActor.get, RotateDrum2Room(roomId.get, userId))

      case msg: Ready2Shoot2Player =>
        context.system.scheduler.scheduleOnce(util.Random.nextInt(3000).min(1000).millis, roomActor.get, PlayerBang2Room(roomId.get))

      case msg: Ready2RoundResult2Player =>
        msg.roundResult.find(r => r.killedPlayerId == userId) match {
          case None =>
          case Some(killedPlayer) =>
            doInThreadTransaction({
              val player = getPlayerDao.load(userId)
              player.setLoses(player.getLoses + 1)
            })
            //          log.info("Bot killed.")
            botGameOver()
        }

      case msg: PlayerBang2Player =>
        if(msg.result.killedPlayerId == userId) {
          doInThreadTransaction({
            val player = getPlayerDao.load(userId)
            player.setLoses(player.getLoses + 1)
          })
          //          log.info("Bot killed.")
          botGameOver()
        }

      case msg: RoomPlayerDuelists2Player =>
        msg.duelists.find(r => r.playerId == userId && r.isDuelist) match {
          case None =>
            //          log.info("RoomPlayerDuelists2Player > not duelist.")
            botGameOver()
          case Some(x) =>
        }

      case msg: Ready2End2Player =>
        doInThreadTransaction({
          val player = getPlayerDao.load(userId)
          player.setWins(player.getWins + 1)
        })
        log.info("Ready2End2Player")
        botGameOver()

      case RoomIsFinish =>
        roomId = None
        roomActor = None
        botGameOver()

      case msg@(_: Ready2Start2Player |
                _: Ready2End2Player |
                _: PlayerExit2Player |
                _: SetRoomPlayerDuelist2Player |
                _: Ready2DuelistResult2Player |
                _: UsePlayerItem2Player |
                _: PlayerBet2Player) => // ignore this messages

      case any => log.error(s">>> Unhandled message '$any'")
    }

    def cancelTimeoutScheduler(): Unit = {
      timeoutScheduler.foreach(_.cancel())
      timeoutScheduler = None
    }

    def botGameOver() = {
      cancelTimeoutScheduler()

      if (roomActor.isDefined && roomId.isDefined)
        roomActor.get ! PlayerExit2Room(roomId.get, userId)

      roomId = None
      roomActor = None
      playerInfoAmount = Int.MaxValue
      playerInfos = List.empty[RoomPlayerInfo]

      context.parent ! RoomBotFinish(userId)

      context.become(receive)
    }

    def createUserSession() = {
      doInThreadTransaction({
        val session = getUserSessionDao.create(UserSession.Factory.newInstance("127.0.0.1", LocalDateTime.now()))
        session.setUser(getAbstractUserDao.load(userId))
        session.getId
      }).get.get
    }
  }

}