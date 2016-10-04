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

package net.orionlab.brr.utils

import ProtoMessages.ProtoMessageTypeBase.eProtoMessageType
import ProtoMessages.MessageResponseBase.MessageResponse
import com.google.protobuf.ByteString
import com.google.protobuf.MessageLite.Builder
import akka.actor._
import net.orionlab.brr.actors.SocketClientActor.OutgoingMessage

trait SocketMessage {

  def getClientActor(): ActorRef

  def sendSocketMessage(messageType: eProtoMessageType, data: Option[Array[Byte]]): Unit = {
    Option(getClientActor()) match {
      case None => CoreSystem.log.error(s"Channel can not be null in '${this}'")
      case Some(actor) =>
        val msgResponse = MessageResponse.newBuilder()
        msgResponse.setMessageType(messageType)
        msgResponse.setMessageBody(if (data.isDefined && data.get.length > 0) ByteString.copyFrom(data.get) else ByteString.EMPTY)
        msgResponse.setErrorCode(0)
        actor ! OutgoingMessage(msgResponse.build())
    }
  }

  def sendSocketMessage(messageType: eProtoMessageType, builder: Builder): Unit = {
    sendSocketMessage(messageType, if (builder == null) None else Some(builder.build().toByteArray))
  }

  def wrapSocketMessage(messageType: eProtoMessageType, data: Option[Array[Byte]]): OutgoingMessage = {
    val msgResponse = MessageResponse.newBuilder()
    msgResponse.setMessageType(messageType)
    msgResponse.setMessageBody(if (data.isDefined && data.get.length > 0) ByteString.copyFrom(data.get) else ByteString.EMPTY)
    msgResponse.setErrorCode(0)
    OutgoingMessage(msgResponse.build())
  }

  def wrapSocketMessage(messageType: eProtoMessageType, builder: Builder): OutgoingMessage = {
    wrapSocketMessage(messageType, if (builder == null) None else Some(builder.build().toByteArray))
  }
}
