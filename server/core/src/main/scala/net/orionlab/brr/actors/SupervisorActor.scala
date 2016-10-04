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

object SupervisorActor {

  import akka.actor._

  def props() = {
    Props(classOf[SupervisorActor])
  }

  class SupervisorActor extends Actor with ActorLogging {

    import akka.actor.OneForOneStrategy
    import akka.actor.SupervisorStrategy._
    import scala.concurrent.duration._
    import net.orionlab.brr.actors.UserManager._

    override val supervisorStrategy =
      OneForOneStrategy(maxNrOfRetries = 10000, withinTimeRange = 10000 seconds) {
        case _: ArithmeticException ⇒ Stop
        case _: NullPointerException ⇒ Stop
        case _: IllegalArgumentException ⇒ Stop
        case _: Exception ⇒ Stop
      }

    val messageRouter = context.actorOf(MessageRouter.props(), "MessageRouterActor")

    def receive = {
      case msg@(_: ClientConnected | ClientDisconnected) => messageRouter.forward(msg)
    }

    override def postStop(): scala.Unit = {
      super.postStop()
      log.info(s">>> Stopping ${self.path}")
    }
  }

}