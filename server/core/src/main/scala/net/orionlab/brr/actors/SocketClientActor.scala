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

object SocketClientActor {

  import net.orionlab.brr.actors.UserManager.{ClientDisconnected, ClientConnected}
  import net.orionlab.brr.actors.MessageExtractorActor.{CompleteMessage, ExtractMessage}
  import akka.actor.{Props, ActorLogging, Actor, ActorRef}
  import akka.io.Tcp
  import ProtoMessages.MessageRequestBase.MessageRequest
  import ProtoMessages.MessageResponseBase.MessageResponse
  import net.orionlab.brr.utils.CoreSystem
  import net.orionlab.brr.serializer.BinarySerializer
  import akka.util.ByteString

  case class IncomingMessage(message: MessageRequest)

  case class OutgoingMessage(message: MessageResponse)

  def props(connection: ActorRef, ipAddress: String) = {
    Props(classOf[SocketClientActor], connection, ipAddress)
  }

  class SocketClientActor(connection: ActorRef, ipAddress: String) extends Actor with ActorLogging {

    import Tcp._

    val actorId = System.nanoTime()
    val messageExtractor = context.actorOf(MessageExtractorActor.props(256))
    var userActor: Option[ActorRef] = None

    CoreSystem.supervisor.foreach(_ ! ClientConnected(self, actorId, ipAddress))

    def receive = {
      case msg: ClientConnected =>
        if (msg.actor == self && msg.actorId == actorId) {
          log.info(s"ClientConnected '${sender()}'")
          userActor = Some(sender())
        }
      case Received(data) =>
        log.info("ReceivedMessage parse it")
        messageExtractor ! ExtractMessage(data.toArray)

      case CompleteMessage(data) =>
        userActor match {
          case None => log.error(s"Cant send CompleteMessage to empty UserActor.")
          case Some(actor) =>
            BinarySerializer.deserialize(data) match {
              case Some(msgIn) =>
                log.info(s"Request messageType <${msgIn.getMessageType}>")
                actor ! IncomingMessage(msgIn)
              case None => log.warning(s"Impossible to send empty Request message to <$actor>")
            }
        }
      case OutgoingMessage(message) =>
        //        log.info(s"Received OutgoingMessage(${message.getMessageType}), send it to $connection")
        BinarySerializer.serialize(message) match {
          case Some(msgOut) =>
            log.info(s"Response messageType <${message.getMessageType}>")
            connection ! Write(ByteString(msgOut))
          case None => log.warning(s"Impossible send empty Response message to <$connection>")
        }

      case Closed | Aborted | ConfirmedClosed | PeerClosed =>
        log.info(s"ClientDisconnect $connection")
        CoreSystem.supervisor.foreach(_ ! ClientDisconnected(self, actorId))
        context.stop(self)

      case msg: ErrorClosed =>
        log.info(s"ClientDisconnect(${msg.cause}) $connection")
        CoreSystem.supervisor.foreach(_ ! ClientDisconnected(self, actorId))
        context.stop(self)

      case any => log.warning(s"Unhandled event <$any>")
    }

    override def postStop(): Unit = {
      super.postStop()
      connection ! Close
    }
  }

}

