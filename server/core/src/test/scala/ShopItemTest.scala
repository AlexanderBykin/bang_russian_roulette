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

import net.orionlab.brr.domain.{PlayerShopItem, ShopItemType}
import java.util
import net.orionlab.brr.utils.CoreTransaction
import collection.JavaConversions._
import org.testng.annotations.Test
import org.slf4j._

class ShopItemTest extends CoreTransaction {
  private val log = LoggerFactory.getLogger(this.getClass.getName)

  //@Test
  def testPlayerInventoryItems() {
    doInThreadTransaction({
      val playerId = 63
      getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.PlayerShopItem WHERE" +
        s" player.id = ${playerId}" +
        s" AND shopItem.itemType <> '${ShopItemType.MONEY}'" +
        s" AND isArchived = false" +
        s" AND shopItem.isVisible = true" +
        s" AND shopItem.isArchived = false")
        .list().asInstanceOf[util.List[PlayerShopItem]]
        .map(r => (r.getShopItem.getName, r.getShopItem.getImageName, r.getShopItem.getLocales.toList))
        .groupBy(r => r).mapValues(_.size).foreach(r => {
        log.info(s"name=${r._1._1} image=${r._1._2} locales=${r._1._3} count=${r._2}")
      })
    }, ro = true)
  }

  @Test
  def testPlayerInventoryItemsWithShop() {
    doInThreadTransaction({
      val playerId = 295L

      val query = getSessionFactoryDao.getCurrentSession.createSQLQuery("select si.id, si.name, si.image_name, count(psi.id) from shop_item si " +
        "left join player_shop_item psi on psi.shop_item_fk = si.id " +
        s"where coalesce(psi.player_fk, :pId) = :pId " +
        "and coalesce(psi.is_archived, false) = false " +
        s"and si.item_type <> '${ShopItemType.MONEY}' " +
        s"and si.is_visible = true and si.is_archived = false " +
        "group by si.id, si.name, si.image_name")
      query.setParameter("pId", playerId)
      query.list().asInstanceOf[util.List[Array[Object]]].foreach(r => {
        val item = getShopItemDao.load(r(0).asInstanceOf[java.math.BigInteger].longValue())
        log.info(s"id=${r(0)} name=${r(1)} image=${r(2)} locales=${item.getLocales} count=${r(3)}")
      })
    }, ro = true)
  }
}