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

object PlayerType {
  type TPlayerType = Int
  val ptWatcher: TPlayerType = 1
  val ptPlayer: TPlayerType = 2
}

case class Player(id: Long,
                  playerType: PlayerType.TPlayerType,
                  pos: Int,
                  var prev: Option[Long] = None,
                  var next: Option[Long] = None)

val isClockWise = false
val allPlayers =
  List(
    Player(1, PlayerType.ptPlayer, 6),
    Player(2, PlayerType.ptPlayer, 3),
    Player(3, PlayerType.ptPlayer, 1),
    Player(4, PlayerType.ptWatcher, 0),
    Player(5, PlayerType.ptPlayer, 2)
  )

def findNeighbor(otherPlayers: List[Player]): Unit = {
  if (otherPlayers.nonEmpty) {
    val player = otherPlayers.head
    val newOtherPlayers = otherPlayers.tail
    val nextPlayer = newOtherPlayers.headOption.getOrElse(player)
    if (player.prev.isEmpty) {
      val prevPlayer = newOtherPlayers.lastOption.getOrElse(player)
      player.prev = Some(player.prev.getOrElse(prevPlayer.id))
      prevPlayer.next = Some(prevPlayer.next.getOrElse(player.id))
    }
    if (player.next.isEmpty) {
      player.next = Some(player.next.getOrElse(nextPlayer.id))
      nextPlayer.prev = Some(nextPlayer.prev.getOrElse(player.id))
    }
    if (newOtherPlayers.nonEmpty)
      findNeighbor(newOtherPlayers)
  }
}

// sort players by direction
val players = allPlayers.filter(_.playerType == PlayerType.ptPlayer)
  .sortWith((a, b) ⇒ if (isClockWise) a.pos > b.pos else a.pos < b.pos)

findNeighbor(players)
players.foreach(x ⇒ println("id=%d type=%d pos=%d - prevId=%d nextId=%d".format(x.id, x.playerType, x.pos, x.prev.getOrElse(-1L), x.next.getOrElse(-1L))))

