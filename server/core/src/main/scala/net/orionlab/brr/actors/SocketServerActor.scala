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

object SocketServerActor {

  import akka.actor.{ActorLogging, Actor, Props}
  import akka.io.{IO, Tcp}
  import java.net.InetSocketAddress

  def props(port: Int) = {
    Props(classOf[SocketServerActor], port)
  }

  class SocketServerActor(serverPort: Int) extends Actor with ActorLogging {

    import Tcp._
    import context.system

    log.info("SocketServerActor created\nTrying to bind socket.")
    val opts = List(SO.KeepAlive(on = false), SO.TcpNoDelay(on = true))
    IO(Tcp) ! Bind(self, new InetSocketAddress(serverPort), options = opts)

    def receive = {
      case Bound(localAddress) => log.info(s"Server listening on $localAddress")
      case CommandFailed(_: Bind) => context stop self
      case Connected(remote, local) =>
        val sb = remote.getAddress.getAddress.addString(new StringBuilder(), "tcp-", "_", "x").append(remote.getPort)
        val actorName = local.getAddress.getAddress.addString(sb, "-", "_", "x").append(local.getPort).toString()
        val connection = sender()
        val handler = context.actorOf(SocketClientActor.props(connection, remote.getAddress.getHostAddress), actorName)
        connection ! Register(handler)
      case any => log.info(s">>> Unhandled message '$any'")
    }
  }

}