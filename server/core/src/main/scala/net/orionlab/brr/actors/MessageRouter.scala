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

object MessageRouter {

  import akka.actor._
  import net.orionlab.brr.actors.UserManager._
  import net.orionlab.brr.utils.CoreTransaction

  def props() = {
    Props(classOf[MessageRouterActor])
  }

  object ActorManagerType extends Enumeration {
    type ActorManagerType = Value
    val mtUser, mtRoom, mtBot, mtPaymentRequest, mtNotification = Value
  }

  case class GetRoomManager(actor: Option[ActorRef])

  case class GetUserManager(actor: Option[ActorRef])

  case class GetBotManager(actor: Option[ActorRef])

  case class GetPaymentRequestManager(actor: Option[ActorRef])

  case class GetNotificationManager(actor: Option[ActorRef])

  class MessageRouterActor extends Actor with ActorLogging with CoreTransaction {

    import net.orionlab.brr.actors.MessageRouter.ActorManagerType.ActorManagerType

    getOrCreateManagerActor(ActorManagerType.mtPaymentRequest)
    getOrCreateManagerActor(ActorManagerType.mtBot)
    getOrCreateManagerActor(ActorManagerType.mtRoom)
    getOrCreateManagerActor(ActorManagerType.mtUser)
    getOrCreateManagerActor(ActorManagerType.mtNotification)

    def receive = {
      case msg: ClientConnected ⇒ getOrCreateManagerActor(ActorManagerType.mtUser).forward(msg)
      case msg: ClientDisconnected ⇒ getOrCreateManagerActor(ActorManagerType.mtUser).forward(msg)
      case msg: GetRoomManager ⇒ sender() ! GetRoomManager(Some(getOrCreateManagerActor(ActorManagerType.mtRoom)))
      case msg: GetUserManager ⇒ sender() ! GetUserManager(Some(getOrCreateManagerActor(ActorManagerType.mtUser)))
      case msg: GetBotManager ⇒ sender() ! GetBotManager(Some(getOrCreateManagerActor(ActorManagerType.mtBot)))
      case msg: GetPaymentRequestManager => sender() ! GetPaymentRequestManager(Some(getOrCreateManagerActor(ActorManagerType.mtPaymentRequest)))
      case msg: GetNotificationManager => sender() ! GetNotificationManager(Some(getOrCreateManagerActor(ActorManagerType.mtNotification)))
      case any ⇒ log.error(s">>> Unhandled message '$any'")
    }

    def getOrCreateManagerActor(managerType: ActorManagerType): ActorRef = {
      val (props, managerName) = managerType match {
        case ActorManagerType.mtUser ⇒
          (UserManager.props(), "UserManagerActor")
        case ActorManagerType.mtRoom ⇒
          (RoomManager.props(), "RoomManagerActor")
        case ActorManagerType.mtBot ⇒
          (BotManager.props(), "BotManagerActor")
        case ActorManagerType.mtPaymentRequest =>
          (PaymentRequestManager.props(), "PaymentRequestManagerActor")
        case ActorManagerType.mtNotification =>
          (NotificationManager.props(), "NotificationManagerActor")
      }
      context.child(managerName).fold(context.actorOf(props, managerName))(x ⇒ x)
    }

    override def postStop(): Unit = {
      super.postStop()
      log.info(s">>> Stopping ${self.path}")
    }
  }

}