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

package net.orionlab.brr

import net.orionlab.brr.utils.CoreSystem
import javax.servlet.{ServletContextEvent, ServletContextListener}

class ContextLoaderListener extends ServletContextListener {
  override def contextInitialized(sce: ServletContextEvent): Unit = {
    ServiceLocator.instance().getDumbService.doDumb()
    CoreSystem.initSystem()
  }

  override def contextDestroyed(sce: ServletContextEvent): Unit = {
    CoreSystem.stopSystem()
  }
}