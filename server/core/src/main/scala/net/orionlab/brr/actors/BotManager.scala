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

object BotManager {

  import akka.actor.{Props, ActorRef, ActorLogging, Actor}
  import net.orionlab.brr.utils.CoreTransaction
  import net.orionlab.brr.domain.{AbstractUser, UserRoleType}
  import net.orionlab.brr.actors.UserActor._
  import collection.JavaConversions._
  import scala.annotation.tailrec
  import java.util.{List => JList}

  case class CreateRoomBots(roomId: Long)

  case class RoomBotFinish(botId: Long)

  def props() = {
    Props(classOf[BotManagerActor])
  }

  class BotManagerActor extends Actor with ActorLogging with CoreTransaction {
    val botIds = doInThreadTransaction({
      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
        s" role = '${UserRoleType.BOT}'")
        .list().asInstanceOf[JList[AbstractUser]].map(x => (x.getId.longValue(), x.getDisplayName))
    }, ro = true).get.get
    var busyBots = List.empty[Long]

    botIds.foreach(x => getOrCreateBotActor(x._1, x._2))

    def receive = {
      case msg: CreateRoomBots =>
        val freeBots = getFreeBots
        val rnd = 2
        //      val rnd = util.Random.nextInt(2) + 1
        val amountBots = freeBots.length.min(rnd)
        log.info(s">>> CreateRoomBots for room(${msg.roomId}) available(${freeBots.length}) amount($amountBots)")
        val b4r = getBots4Room(freeBots, List.empty, amountBots)
        log.info(s">>> GeneratedBots for room(${msg.roomId}) $b4r")
        b4r.foreach(bot => {
          busyBots ::= bot._1
          getOrCreateBotActor(bot._1, bot._2).forward(RoomPlayerInit2Room(msg.roomId))
        })

      case msg: RoomBotFinish =>
        //      log.info(s"RoomBotFinish(${sender()})")
        busyBots = busyBots.filter(_ != msg.botId)
    }

    def getBotActorName(botId: Long) = s"BotActor:$botId"

    def getOrCreateBotActor(botId: Long, botName: String): ActorRef = {
      val (props, actorName) = (BotActor.props(botId, botName), getBotActorName(botId))
      context.child(actorName).fold(context.actorOf(props, actorName))(x => x)
    }

    @tailrec
    final def getBots4Room(freeBots: List[(Long, String)], bots: List[(Long, String)], amount: Int, tryGen: Int = 1): List[(Long, String)] = {
      if (bots.size == amount || freeBots.length * 10 < tryGen)
        bots
      else {
        val rndPos = util.Random.nextInt(freeBots.size)
        val bot = freeBots(rndPos)
        bots.find(x => x._1 == bot._1 || busyBots.contains(bot._1)) match {
          case None => getBots4Room(freeBots, bot :: bots, amount, tryGen + 1)
          case Some(_) => getBots4Room(freeBots, bots, amount, tryGen + 1)
        }
      }
    }

    def getFreeBots = botIds.filter(x => !busyBots.contains(x._1)).toList
  }

}