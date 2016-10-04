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

package net.orionlab.brr.service

import net.orionlab.brr.utils.{CoreDao, CoreTransaction}

class DumbServiceImpl extends DumbServiceBase with CoreDao with CoreTransaction {

  import scala.collection.JavaConversions._
  import org.joda.time.LocalDateTime
  import net.orionlab.brr.utils.CoreUtils._
  import org.slf4j._
  import java.util.{List => JList}
  import net.orionlab.brr.domain._

  private val log = LoggerFactory.getLogger(classOf[DumbService])

  protected def handleDoDumb() {
    doInThreadTransaction({
      if(getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.SystemProperty")
      .list().isEmpty) {
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("timeout2Start", "15000", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("timeout2RotateDrum", "5000", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("timeout2Shoot", "3000", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("timeout2Result", "3000", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("timeout2End", "0", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("maxRoomAmountPerType", "10", true))
        getSystemPropertyDao.create(SystemProperty.Factory.newInstance("planned2Stop", "true", false))
      }
    }).get

    doInThreadTransaction({
      val killerExists = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
        s" role = '${UserRoleType.KILLER}'")
        .list().isEmpty
      if (killerExists) {
        val newKiller = Player.Factory.newInstance()
        newKiller.setIsBlocked(true)
        newKiller.setLoses(0)
        newKiller.setMoney(0L)
        newKiller.setWins(0)
        newKiller.setDateCreate(LocalDateTime.now())
        newKiller.setRole(UserRoleType.KILLER)
        newKiller.setDateLastActivity(LocalDateTime.now())
        newKiller.setPassword("")
        newKiller.setDisplayName("killer")
        newKiller.setEmail(java.util.UUID.randomUUID().toString)
        newKiller.setAuthType(AuthType.EMAIL)
        newKiller.setVerifyCode(newKiller.getEmail)
        getPlayerDao.create(newKiller)
      }
    }).get

    doInThreadTransaction({
      val botNames = Array("Philip J. Fry", "Turanga Leela", "Bender Bending Rodriguez", "Hubert Farnsworth", "Hermes Conrad", "John D. Zoidberg",
        "Emy Wong", "Zapp Brannigan", "Nibbler", "Morbo the Annihilator", "Kif Kroker", "Scruffy", "The Donbot", "Joey Mousepad", "Clamps", "Richard Nixon",
        "Roberto", "Robot Devil", "Robot Santa", "Barbados Slim", "Calculon", "Elzar", "Hedonismbot", "Hyperchicken", "Hypnotoad", "Officer Smitty",
        "Officer URL", "Petunia", "Sal", "Tinny Tim", "Brain Slugs", "Brainspawn", "The Crushinator", "Guenter", "Gypsy-Bot", "Homer Simpson", "Marge Simpson",
        "Bart Simpson", "The Rich Texan", "Mr. Costington", "Drederick Tatum", "Reverend Lovejoy", "Old Sea Captain", "Rainier Wolfcastle", "Arnie Pye",
        "Arthur Crandall", "Baby Gerald", "Birch Barlow", "\"Bleeding Gums\" Murphy", "Brandine Spuckler", "Groundskeeper Willie", "Kent Brockman",
        "Fat Tony", "Ned Flanders", "Barney Gumble", "The Itchy", "The Scratchy", "Kang and Kodos", "Comic Book Guy", "Mr. Burns", "Bumblebee Man ",
        "Kearney Zzyzwicz", "Krusty the Clown ", "Nelson Muntz", "Apu Nahasapeemapetilon", "Martin Prince", "Sideshow Bob", "Principal Skinner",
        "Cletus Spuckler", "Moe Szyslak", "Clancy Wiggum", "Ralph Wiggum", "Tim the Bear", "Cleveland Brown, Jr.", "Cleveland Brown", "Stan Smith",
        "Francine Smith", "Hayley Smith", "Steve Smith", "Roger", "Klaus Heissler", "Avery Bullock", "Reginald the Koala", "Principal Brian Lewis",
        "Barry Robinson", "Captain Monty", "Peter Griffin", "Lois Griffin", "Stewie Griffin", "Brian Griffin", "Jasper", "Joseph \"Joe\" Swanson",
        "Glenn Quagmire", "Evil Monkey", "Jake Tucker", "Ernie The Giant Chicken", "Bruce", "John Herbert", "Meg Griffin", "Chris Griffin")

      val bots = getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.AbstractUser WHERE" +
        s" role = '${UserRoleType.BOT}'")
        .list().asInstanceOf[JList[AbstractUser]]

      if (bots.size() < 100) {
        (bots.size() + 1).to(100).foreach(r => {
          val newBot = Player.Factory.newInstance()
          newBot.setIsBlocked(true)
          newBot.setLoses(0)
          newBot.setMoney(0L)
          newBot.setWins(0)
          newBot.setDateCreate(LocalDateTime.now())
          newBot.setRole(UserRoleType.BOT)
          newBot.setDateLastActivity(LocalDateTime.now())
          newBot.setPassword("")
          newBot.setDisplayName(botNames(r - 1))
          newBot.setEmail(java.util.UUID.randomUUID().toString)
          newBot.setAuthType(AuthType.EMAIL)
          newBot.setVerifyCode(newBot.getEmail)
          getPlayerDao.create(newBot)
        })
      }
    }).get

    doInThreadTransaction({
      if (getShopItemDao.loadAll().isEmpty) {
        var locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "The armoured bullet gives you an ability to breach your enemy's helmet and defeat the enemy.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Бронированный патрон - дает возможность пробить шлем и победить противника.", LocalDateTime.now()))
        )
        var newShopItem = ShopItem.Factory.newInstance(ShopItemType.BULLET, "brr_armored_bullet", "ShopItemArmoredBullet.png", 83, 1, ShopItemUsageType.PLAYER, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)

        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "The broken bullet - prevents your enemy from shooting at you.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Сломанный патрон - при выстреле противником, делает выстрел холостым.", LocalDateTime.now()))
        )
        newShopItem = ShopItem.Factory.newInstance(ShopItemType.BULLET, "brr_broken_bullet", "ShopItemBrokenBullet.png", 83, 2, ShopItemUsageType.ENEMY, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)

        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "The helmet - protects you from bullet except the armoured bullet.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Шлем - защищает от всех пуль, кроме бронебойных.", LocalDateTime.now()))
        )
        newShopItem = ShopItem.Factory.newInstance(ShopItemType.HELMET, "brr_helmet", "ShopItemHelmet.png", 500, 3, ShopItemUsageType.PLAYER, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)

        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Track of a bullet - changes the direction of the shooting to the opposite.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Направление стрельбы - меняет направление стрельбы игрока на противоположное.", LocalDateTime.now()))
        )
        newShopItem = ShopItem.Factory.newInstance(ShopItemType.SHOOTDIRECTION, "brr_change_shoot_direction", "ShopItemChangeShootDirection.png", 200, 5, ShopItemUsageType.BOTH, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)

        getShopItemDao.create(ShopItem.Factory.newInstance(ShopItemType.MONEY, "brr_money", "ShopItemMoney.png", 1, 6, ShopItemUsageType.NONE, false, LocalDateTime.now(), null, false, null))

        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Vungle video ad - watch it and you get 50 credits.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Vungle видео реклама - посмотрите и получите 50 кредитов.", LocalDateTime.now()))
        )
        newShopItem = ShopItem.Factory.newInstance(ShopItemType.VIDEOAD, "brr_videoad_vungle", "ShopItemVideoADVungle.png", 50, 1, ShopItemUsageType.NONE, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)

        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "AdColony video ad - watch it and you get 50 credits.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "AdColony видео реклама - посмотрите и получите 50 кредитов.", LocalDateTime.now()))
        )
        newShopItem = ShopItem.Factory.newInstance(ShopItemType.VIDEOAD, "brr_videoad_adcolony", "ShopItemVideoADColony.png", 50, 1, ShopItemUsageType.NONE, true, LocalDateTime.now(), null, false, locales)
        getShopItemDao.create(newShopItem)
      }
    }).get

    doInThreadTransaction({
      if (getShopItemCollectionDao.loadAll().isEmpty) {
        var locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Collection of twelve armored bullet.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Коллекция из двенадцати бронированных патронов.", LocalDateTime.now()))
        )
        var item1 = getShopItemDao.searchUniqueName("brr_armored_bullet")
        var collectionItems = Set(
          getShopItemCollectionItemDao.create(getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(12, LocalDateTime.now(), null, false, item1)))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_collection_12_armored_bullet", "ShopItemTwelveArmoredBullet.png", 1000, 1, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Collection of twelve broken bullet.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Коллекция из двенадцати сломанных патронов.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_broken_bullet")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(12, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_collection_12_broken_bullet", "ShopItemTwelveBrokenBullet.png", 1000, 2, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Collection of helmet + six armored bullet.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Коллекция из шлема + шести бронированных патронов.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_helmet")
        var item2 = getShopItemDao.searchUniqueName("brr_armored_bullet")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(1, LocalDateTime.now(), null, false, item1)),
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(6, LocalDateTime.now(), null, false, item2))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_collection_6_armored_bullet_helmet", "ShopItemHelmetSixArmoredBullet.png", 1000, 3, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "Collection of helmet + six armored bullet.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "Коллекция из шлема + шести бронированных патронов.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_helmet")
        item2 = getShopItemDao.searchUniqueName("brr_broken_bullet")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(1, LocalDateTime.now(), null, false, item1)),
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(6, LocalDateTime.now(), null, false, item2))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_collection_6_broken_bullet_helmet", "ShopItemHelmetSixBrokenBullet.png", 1000, 4, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "1000 credits.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "1000 кредитов.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(1000, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_1000", "ShopItemMoney1000.png", 1000, 1, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "2000 credits + 25% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "2000 кредитов + 25% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(2500, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_2000", "ShopItemMoney2000.png", 2500, 2, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "4000 credits + 30% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "4000 кредитов + 30% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(5200, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_4000", "ShopItemMoney4000.png", 5200, 3, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "8000 credits + 35% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "8000 кредитов + 35% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(10800, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_8000", "ShopItemMoney8000.png", 10800, 4, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "16000 credits + 40% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "16000 кредитов + 40% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(22400, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_16000", "ShopItemMoney16000.png", 22400, 5, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "32000 credits + 45% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "32000 кредитов + 45% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(46400, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_32000", "ShopItemMoney32000.png", 46400, 6, LocalDateTime.now(), null, false, collectionItems, locales))

        // ******
        locales = Set(
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("en", "64000 credits + 50% free.", LocalDateTime.now())),
          getShopItemLocaleDao.create(ShopItemLocale.Factory.newInstance("ru", "64000 кредитов + 50% бесплатно.", LocalDateTime.now()))
        )
        item1 = getShopItemDao.searchUniqueName("brr_money")
        collectionItems = Set(
          getShopItemCollectionItemDao.create(ShopItemCollectionItem.Factory.newInstance(96000, LocalDateTime.now(), null, false, item1))
        )
        getShopItemCollectionDao.create(ShopItemCollection.Factory.newInstance("brr_money_64000", "ShopItemMoney64000.png", 96000, 7, LocalDateTime.now(), null, false, collectionItems, locales))
      }
    }).get
  }
}