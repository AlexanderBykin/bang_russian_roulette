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

import pushka.json._
import pushka.annotation.pushka
import scala.math.BigDecimal.RoundingMode

@pushka
case class AccountEntry(entryByPartyName: String, amount: BigDecimal)

@pushka
case class AccountingTransaction(accountingDate: java.util.Date, entries: List[AccountEntry])

implicit val bigDecimal = new pushka.RW[BigDecimal] {
  def read(value: pushka.Ast): BigDecimal = value match {
    case pushka.Ast.Str(x) ⇒ BigDecimal(x)
    case _ ⇒ throw pushka.PushkaException(value, BigDecimal.getClass)
  }

  def write(value: BigDecimal): pushka.Ast = {
    pushka.Ast.Str(value.setScale(2, RoundingMode.HALF_UP).toString)
  }
}

val acce1 = AccountEntry("CMSC", BigDecimal(1))
val acce2 = AccountEntry("OCMSP", BigDecimal(2))

val acct = AccountingTransaction(new java.util.Date(),
  List(
    acce1,
    acce2))

write(acce1)
