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

object RoomManager {

  import akka.actor.{ActorRef, Props, ActorLogging, Actor}
  import net.orionlab.brr.utils.CoreTransaction
  import net.orionlab.brr.domain._

  case class GenerateRoomByType(roomType: RoomType)

  case class RoomNotFound(roomId: Long)

  case object RoomPlanned2Stop

  def props() = {
    Props(classOf[RoomManagerActor])
  }

  class RoomManagerActor extends Actor with ActorLogging with CoreTransaction {

    import context.dispatcher
    import net.orionlab.brr.actors.BotManager._
    import net.orionlab.brr.actors.UserManager._
    import net.orionlab.brr.actors.MessageRouter._
    import net.orionlab.brr.actors.RoomActor._
    import org.joda.time.LocalDateTime
    import concurrent.duration._
    import collection.JavaConversions._
    import net.orionlab.brr.utils.CoreUtils._

    case object CheckPlanned2Stop

    private var planned2Stop = false
    private var userManager = Option.empty[ActorRef]
    private var botManager = Option.empty[ActorRef]
    private lazy val (
      maxRoomAmountPerType,
      timeout2Start,
      timeout2RotateDrum,
      timeout2Shoot,
      timeout2Result,
      timeout2End) = doInThreadTransaction({
      val keyValue = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.SystemProperty WHERE" +
        " key in ('maxRoomAmountPerType', 'timeout2Start', 'timeout2RotateDrum', 'timeout2Shoot', 'timeout2Result', 'timeout2End')")
        .list().asInstanceOf[java.util.List[SystemProperty]]
      (
        keyValue.find(_.getKey == "maxRoomAmountPerType").fold(10)(x => x.getValue.toInt),
        keyValue.find(_.getKey == "timeout2Start").fold(15000)(x => x.getValue.toInt),
        keyValue.find(_.getKey == "timeout2RotateDrum").fold(5000)(x => x.getValue.toInt),
        keyValue.find(_.getKey == "timeout2Shoot").fold(3000)(x => x.getValue.toInt),
        keyValue.find(_.getKey == "timeout2Result").fold(3000)(x => x.getValue.toInt),
        keyValue.find(_.getKey == "timeout2End").fold(0)(x => x.getValue.toInt)
        )
    }).get.get

    context.system.scheduler.scheduleOnce(500.millis, context.parent, GetUserManager(None))
    context.system.scheduler.scheduleOnce(500.millis, context.parent, GetBotManager(None))
    context.system.scheduler.schedule(1.minute, 3.minute, self, CheckPlanned2Stop)

    def receive = {
      case msg: GetUserManager => userManager = msg.actor

      case msg: GetBotManager => botManager = msg.actor

      case msg: GetRoomListByType =>
        val roomByTypeList = context.children.filter(r => r.path.name.contains(msg.roomType.value()))
        if (roomByTypeList.nonEmpty) {
          sender() ! RoomListAmountByType(msg.roomType, roomByTypeList.size)
          roomByTypeList.foreach(_.forward(msg))
        }

      case msg: ClientDisconnected2Room => context.children.foreach(_ ! msg)

      case GenerateRoomByType(roomType) =>
        if (!planned2Stop) generateRoomByType(roomType)
        else log.info(">>> Game planned to stop, room generation disabled.")

      case msg: SetRoomPlayer =>
        context.children.find(r => r.path.name.contains(s"RoomActor:${msg.roomId}")) match {
          case None => msg.player.playerActor ! RoomNotFound(msg.roomId)
          case Some(ar: ActorRef) => ar.forward(msg)
        }

      case msg: CreateRoomBots => botManager.foreach(_.forward(msg))

      case CheckPlanned2Stop =>
        doInThreadTransaction({
          getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.SystemProperty WHERE" +
            " key = 'planned2Stop'" +
            " and isEnabled = true")
            .list().asInstanceOf[java.util.List[SystemProperty]]
            .headOption.foreach(x => {
            x.setIsEnabled(false)
            planned2Stop = x.getValue == "true"
          })
        }).get
        if (planned2Stop) {
          context.children.foreach(_ ! RoomPlanned2Stop)
        }

      case any => log.error(s">>> Unhandled message '$any'")
    }

    private def generateRoomByType(roomType: RoomType) {
      val (minBet, maxBet) = roomType match {
        case RoomType.TINY => (10, 110)
        case RoomType.SMALL => (150, 250)
        case RoomType.MEDIUM => (300, 400)
        case RoomType.BIG => (450, 550)
      }

      val found = context.children.count(r => r.path.name.contains(roomType.value()))

      if (found < maxRoomAmountPerType) {
        doInThreadTransaction({
          (1 to maxRoomAmountPerType - found).foreach(r => {
            val currentRound = 1
            val roomBet = util.Random.nextInt(maxBet - minBet + 1) + minBet
            val newRoom = getRoomDao.create(Room.Factory.newInstance(roomType, LocalDateTime.now()))
            newRoom.setBet(roomBet)
            newRoom.setMaxPlayers(6)
            newRoom.setMaxRounds(6)
            RoomActor.generateNextRound(newRoom, currentRound)(getRoomRoundDao)
            context.actorOf(RoomActor.props(
              newRoom.getId,
              roomType,
              roomBet,
              newRoom.getMaxRounds,
              currentRound,
              newRoom.getMaxPlayers,
              timeout2Start,
              timeout2RotateDrum,
              timeout2Shoot,
              timeout2Result,
              timeout2End), s"RoomActor:${newRoom.getId}:${roomType.value()}")

          })
        }).get
      }
    }

    override def postStop() {
      super.postStop()
      log.info(s">>> Stopping $self")
    }
  }

}