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

import net.orionlab.brr.ServiceLocator
import net.orionlab.brr.domain._
import org.hibernate.SessionFactory

trait CoreDao {
  def getAbstractUserDao = ServiceLocator.instance().getService("abstractUserDao").asInstanceOf[AbstractUserDao]

  def getPlayerDao = ServiceLocator.instance().getService("playerDao").asInstanceOf[PlayerDao]

  def getPlayerShopItemDao = ServiceLocator.instance().getService("playerShopItemDao").asInstanceOf[PlayerShopItemDao]

  def getPlayerPaymentRequestDao = ServiceLocator.instance().getService("playerPaymentRequestDao").asInstanceOf[PlayerPaymentRequestDao]

  def getUserSessionDao = ServiceLocator.instance().getService("userSessionDao").asInstanceOf[UserSessionDao]

  def getSessionFactoryDao = ServiceLocator.instance().getService("sessionFactory").asInstanceOf[SessionFactory]

  def getShopItemLocaleDao = ServiceLocator.instance().getService("shopItemLocaleDao").asInstanceOf[ShopItemLocaleDao]

  def getShopItemDao = ServiceLocator.instance().getService("shopItemDao").asInstanceOf[ShopItemDao]

  def getShopItemCollectionDao = ServiceLocator.instance().getService("shopItemCollectionDao").asInstanceOf[ShopItemCollectionDao]

  def getShopItemCollectionItemDao = ServiceLocator.instance().getService("shopItemCollectionItemDao").asInstanceOf[ShopItemCollectionItemDao]

  def getRoomDao = ServiceLocator.instance().getService("roomDao").asInstanceOf[RoomDao]

  def getRoomRoundDao = ServiceLocator.instance().getService("roomRoundDao").asInstanceOf[RoomRoundDao]

  def getRoundPlayerDao = ServiceLocator.instance().getService("roundPlayerDao").asInstanceOf[RoundPlayerDao]

  def getRoundPlayerBulletDao = ServiceLocator.instance().getService("roundPlayerBulletDao").asInstanceOf[RoundPlayerBulletDao]

  def getRoundPlayerShootDao = ServiceLocator.instance().getService("roundPlayerShootDao").asInstanceOf[RoundPlayerShootDao]

  def getRoundPlayerResultDao = ServiceLocator.instance().getService("roundPlayerResultDao").asInstanceOf[RoundPlayerResultDao]

  def getRoundPlayerUsedItemDao = ServiceLocator.instance().getService("roundPlayerUsedItemDao").asInstanceOf[RoundPlayerUsedItemDao]

  def getRoundPlayerBetDao = ServiceLocator.instance().getService("roundPlayerBetDao").asInstanceOf[RoundPlayerBetDao]

  def getRoundPlayerDuelistDao = ServiceLocator.instance().getService("roundPlayerDuelistDao").asInstanceOf[RoundPlayerDuelistDao]

  def getSystemPropertyDao = ServiceLocator.instance().getService("systemPropertyDao").asInstanceOf[SystemPropertyDao]
}
