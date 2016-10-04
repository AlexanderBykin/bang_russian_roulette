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

import net.orionlab.brr.domain.UserRoleType
import net.orionlab.brr.utils.{CoreDao, CoreTransaction}
import java.lang.{Long => JLong}
import java.util.{List => JList}
import org.testng.annotations.Test

class PlayerTest extends CoreTransaction with CoreDao {
  @Test
  def testPlayerIdCorrect() {
    doInThreadTransaction({
      println(getSessionFactoryDao.getCurrentSession.createQuery("SELECT id FROM net.orionlab.brr.domain.AbstractUser WHERE" +
        s" role = '${UserRoleType.KILLER}'")
        .list().asInstanceOf[JList[JLong]])
    })
  }
}
