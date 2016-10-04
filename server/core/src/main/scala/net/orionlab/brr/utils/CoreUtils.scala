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

import ProtoMessages.AuthTypeBase.eAuthType
import ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType
import net.orionlab.brr.domain._
import ProtoMessages._
import ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition
import ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection
import ProtoMessages.RoomShootDirectionBase.RoomShootDirection
import org.joda.time.LocalDateTime
import MessageResponseShopItemBase.MessageResponseShopItem.eUsageType
import MessageRequestSetPlayerTypeAndPosition.ePlayerType

object CoreUtils {
  implicit def localDateTime2javaDate(ld: LocalDateTime): java.util.Date = ld.toDate

  implicit def playerShootDirectionDB2PlayerShootDirectionProto(playerShootDirection: PlayerShootDirectionType): PlayerShootDirection = {
    playerShootDirection match {
      case PlayerShootDirectionType.LEFT => PlayerShootDirectionBase.PlayerShootDirection.psdLEFT
      case PlayerShootDirectionType.RIGHT => PlayerShootDirectionBase.PlayerShootDirection.psdRIGHT
      case PlayerShootDirectionType.BOTH => PlayerShootDirectionBase.PlayerShootDirection.psdDOUBLE
    }
  }

  implicit def roundShootDirectionDB2RoomShootDirectionProto(roundShootDirection: RoundShootDirectionType): RoomShootDirection = {
    roundShootDirection match {
      case RoundShootDirectionType.LEFT => RoomShootDirectionBase.RoomShootDirection.rsdLEFT
      case RoundShootDirectionType.RIGHT => RoomShootDirectionBase.RoomShootDirection.rsdRIGHT
    }
  }

  implicit def roundShootDirectionDB2PlayerShootDirectionProto(roundShootDirection: RoundShootDirectionType): PlayerShootDirection = {
    roundShootDirection match {
      case RoundShootDirectionType.LEFT => PlayerShootDirectionType.LEFT
      case RoundShootDirectionType.RIGHT => PlayerShootDirectionType.RIGHT
    }
  }

  implicit def roundShootDirectionDB2PlayerShootDirectionDB(roundShootDirection: RoundShootDirectionType): PlayerShootDirectionType = {
    roundShootDirection match {
      case RoundShootDirectionType.LEFT => PlayerShootDirectionType.LEFT
      case RoundShootDirectionType.RIGHT => PlayerShootDirectionType.RIGHT
    }
  }

  implicit def playerTypeProto2PlayerTypeDB(playerType: MessageRequestSetPlayerTypeAndPosition.ePlayerType): PlayerType = {
    playerType match {
      case ePlayerType.ptINVESTOR => PlayerType.INVESTOR
      case ePlayerType.ptPLAYER => PlayerType.PLAYER
      case ePlayerType.ptWATCHER => PlayerType.WATCHER
    }
  }

  implicit def authTypeProto2AuthTypeDB(authType: eAuthType): AuthType = {
    authType match {
      case eAuthType.atAppleGameCenter => AuthType.APPLEGAMECENTER
      case eAuthType.atGooglePlay => AuthType.GOOGLEPLAY
      case _ => AuthType.GOOGLEPLAY
    }
  }

  implicit def betTypeProto2BetTypeDB(betType: PlayerBetWinType): RoundPlayerResultType = {
    betType match {
      case PlayerBetWinType.pbwtWin ⇒ RoundPlayerResultType.WIN
      case PlayerBetWinType.pbwtLose ⇒ RoundPlayerResultType.LOSE
    }
  }

  implicit def shopItemUsageTypeDB2UsageTypeProto(value: ShopItemUsageType): eUsageType = {
    value match {
      case ShopItemUsageType.PLAYER => eUsageType.utPlayer
      case ShopItemUsageType.ENEMY => eUsageType.utEnemy
      case ShopItemUsageType.BOTH => eUsageType.utBoth
      case ShopItemUsageType.NONE => eUsageType.utNone
    }
  }
}
