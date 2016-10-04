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

object UserManager {

  import akka.actor.{ActorRef, Props, ActorLogging, Actor}
  import net.orionlab.brr.utils.CoreTransaction
  import net.orionlab.brr.actors.MessageRouter._
  import net.orionlab.brr.actors.RoomManager._
  import net.orionlab.brr.actors.RoomActor._
  import net.orionlab.brr.actors.UserActor._
  import concurrent.duration._
  import net.orionlab.brr.actors.PaymentRequestManager.CheckPaymentRequest
  import net.orionlab.brr.actors.NotificationManager.EmailNotification

  case class ClientConnected(actor: ActorRef, actorId: Long, ipAddress: String)

  case class ClientDisconnected(actor: ActorRef, actorId: Long)

  case class ClientDisconnected2Room(actorId: Long, playerId: Long)

  def props() = {
    Props(classOf[UserManagerActor])
  }

  class UserManagerActor extends Actor with ActorLogging with CoreTransaction {

    import net.orionlab.brr.utils.CoreUtils._
    import context.dispatcher

    var roomManager = Option.empty[ActorRef]
    var paymentRequestManager = Option.empty[ActorRef]
    var notificationManager = Option.empty[ActorRef]

    context.system.scheduler.scheduleOnce(500.millis, context.parent, GetRoomManager(None))
    context.system.scheduler.scheduleOnce(500.millis, context.parent, GetPaymentRequestManager(None))
    context.system.scheduler.scheduleOnce(500.millis, context.parent, GetNotificationManager(None))

    def receive = {
      case msg: GetRoomManager ⇒ roomManager = msg.actor

      case msg: GetPaymentRequestManager ⇒ paymentRequestManager = msg.actor

      case msg: GetNotificationManager => notificationManager = msg.actor

      case msg: ClientConnected ⇒
        val userActor = context.actorOf(UserActor.props(msg.actor, msg.actorId, msg.ipAddress), getUserActorName(msg.actorId))
        sender().tell(msg, userActor)
        log.info(s"Connected ChannelId='${msg.actorId}'")

      case msg: ClientDisconnected ⇒
        val actorName = getUserActorName(msg.actorId)
        context.child(actorName) match {
          case None ⇒ log.error(s">>> Cant find UserActor($actorName) to ClientDisconnected.")
          case Some(ar: ActorRef) ⇒ ar ! UserDisconnected
        }

      case UserDisconnected ⇒ context.stop(sender())

      case msg@(_: GenerateRoomByType |
                _: GetRoomListByType |
                _: SetRoomPlayer) ⇒ roomManager.foreach(_ forward msg)

      case msg: CheckPaymentRequest => paymentRequestManager.foreach(_.forward(msg))

      case msg: EmailNotification => notificationManager.foreach(_.forward(msg))

      case any ⇒ log.error(s">>> Unhandled message '$any'")
    }

    def getUserActorName(channelId: Long) = s"UserActor:$channelId"

    override def postStop() {
      super.postStop()
      log.info(s">>> Stopping $self")
    }
  }

}