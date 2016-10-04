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

object CoreSystem {

  import akka.actor.{ActorRef, ActorSystem}
  import net.orionlab.brr.actors.{SocketServerActor, SupervisorActor}
  import com.typesafe.config.ConfigFactory
  import java.lang.{Boolean => JBoolean}
  import java.util.concurrent.Executors
  import org.slf4j.LoggerFactory
  import scala.util._

  val config = ConfigFactory.load().getConfig("BRRServer")
  val log = LoggerFactory.getLogger("CoreSystem")
  lazy val system = ActorSystem("BrrServerApp", config)
  var supervisor = Option.empty[ActorRef]
  val isDebugMode = Try[JBoolean](config.getBoolean("ioServer.isDebugMode")).toOption.getOrElse(JBoolean.FALSE)
  val transactionExecutorPool = Executors.newFixedThreadPool(Try[Int](config.getInt("gameProperties.transactionPoolSize")).toOption.getOrElse(10))

  def initSystem() {
    log.info("CoreSystem init")
    supervisor = Some(system.actorOf(SupervisorActor.props(), "BRRSupervisor"))
    system.actorOf(SocketServerActor.props(config.getInt("ioServer.port")), "BRRSocketServer")
    log.info("******************* Brr core context initialization finished *******************")
  }

  def stopSystem() {
    log.info("******************* Brr going shutdown *******************")
    system.terminate()
  }
}