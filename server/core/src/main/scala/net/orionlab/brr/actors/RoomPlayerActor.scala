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

object RoomPlayerActor {

  import akka.actor._
  import net.orionlab.brr.actors.UserActor._
  import net.orionlab.brr.actors.RoomActor._
  import net.orionlab.brr.actors.RoomManager._
  import net.orionlab.brr.actors.UserManager._

  case class PlayerInfoAmount(amount: Int)

  case class RoomPlayerInfos(roomId: Long, infos: List[RoomPlayerInfo])

  case class RoomInit(roomId: Long)

  def props(roomId: Long) = {
    Props(classOf[RoomPlayerActor], roomId)
  }

  class RoomPlayerActor(roomId: Long) extends Actor with ActorLogging {
    private var playerInfoAmount = Int.MaxValue
    private var playerInfos = List.empty[RoomPlayerInfo]
    private var roomActor: Option[ActorRef] = None

    def receive = {
      case msg: RoomInit =>
        if (msg.roomId != roomId)
          context.parent ! RoomNotFound(roomId)
        else {
          roomActor = Some(sender())
          context.parent ! RoomPlayerInit2Player(roomId)
        }
      case RoomIsFinish => context.parent ! RoomIsFinish
      case NeedAuth2Player => context.parent ! NeedAuth2Player
      case msg@(_: RoomNotFound |
                _: RoomPlayerDuelists2Player |
                _: SetRoomPlayerDuelist2Player |
                _: Ready2Start2Player |
                _: Ready2PutBullets2Player |
                _: Ready2RotateDrum2Player |
                _: Ready2Shoot2Player |
                _: Ready2RoundResult2Player |
                _: Ready2DuelistResult2Player |
                _: Ready2End2Player |
                _: PlayerBet2Player |
                _: UsePlayerItem2Player |
                _: SetPlayerTypeAndPosition2Player |
                _: RotateDrum2Player |
                _: PlayerExit2Player |
                _: RoomInfo2Player |
                _: NoMoney2Player |
                _: PlayerBang2Player) =>
        context.parent ! msg
      case msg: SetPlayerTypeAndPosition2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: RoomPlayerDuelists2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: SetRoomPlayerDuelist2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: RoomInfo2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: AuthUser2Room =>
        roomActor.foreach(x => x ! msg)
      case msg: PlayerExit2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: PlayerBet2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: UsePlayerItem2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: SetPistolBullets2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: RotateDrum2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: PlayerBang2Room =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: GetRoomPlayers =>
        if (msg.roomId == roomId)
          roomActor.foreach(_ ! msg)
      case msg: PlayerInfoAmount => playerInfoAmount = msg.amount
      case msg: RoomPlayerInfo =>
        playerInfos ::= msg

        if (playerInfos.size == playerInfoAmount) {
          context.parent ! RoomPlayerInfos(roomId, playerInfos)
          playerInfoAmount = Int.MaxValue
          playerInfos = List.empty[RoomPlayerInfo]
        }
      case msg: ClientDisconnected2Room => roomActor.foreach(_ ! msg)
      case any => log.error(s">>> Unhandled message '$any'")
    }

    override def postStop() {
      super.postStop()
      log.info(s">>> Stopping $self")
    }
  }

}