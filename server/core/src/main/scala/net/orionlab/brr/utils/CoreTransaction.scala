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

trait CoreTransaction extends CoreDao {

  import java.util.concurrent.Callable
  import org.springframework.transaction.support.DefaultTransactionDefinition
  import org.springframework.transaction.{PlatformTransactionManager, TransactionDefinition, TransactionStatus}
  import net.orionlab.brr.ServiceLocator
  import scala.util._

  private def tm = ServiceLocator.instance().getService("transactionManager").asInstanceOf[PlatformTransactionManager]

  def commit(tx: TransactionStatus) = tm.commit(tx)

  def rollback(tx: TransactionStatus) = if (!tx.isCompleted) tm.rollback(tx)

  def beginTransaction(trxName: String, readOnly: Boolean = false, defType: Int = TransactionDefinition.PROPAGATION_REQUIRES_NEW, iso: Int = TransactionDefinition.ISOLATION_DEFAULT /*, timeout: Int = 600*/) = {
    val txDef = new DefaultTransactionDefinition()
    txDef.setName(trxName)
    txDef.setIsolationLevel(iso)
    txDef.setPropagationBehavior(defType)
    txDef.setReadOnly(readOnly)
    //    txDef.setTimeout(timeout)
    tm.getTransaction(txDef)
  }

  //  def inTransaction[T](body: => T, name: String = "",
  //                       ro: Boolean = false,
  //                       propType: Int = TransactionDefinition.PROPAGATION_REQUIRES_NEW,
  //                       onException: (String, String) => Unit = (m: String, c: String) => {},
  //                       onSuccess: (T) => Unit = (ret: T) => {}): T = {
  //
  //    val tx = beginTransaction(name, readOnly = ro, defType = propType) //, timeout = timeOut)
  //    val ret = try {
  //        val res = body
  //        commit(tx)
  //        onSuccess(res)
  //        res
  //      } catch {
  //        case e: Throwable =>
  //          CoreSystem.syslog.error(s"\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ERROR $e\n ${e.getMessage}\n\n <<<<<<<<<<<<<<<<<<<<<<<<<<")
  //          rollback(tx)
  //          onException(e.getMessage, e.getClass.getSimpleName)
  //          e.printStackTrace()
  //          throw e
  //      }
  //    ret
  //  }

  def doInThreadTransaction[T](body: ⇒ T,
                               trxName: String = System.currentTimeMillis().toString,
                               ro: Boolean = false,
                               propType: Int = TransactionDefinition.PROPAGATION_REQUIRES_NEW,
                               onException: (String, String) => Unit = (m: String, c: String) => {},
                               onSuccess: (T) => Unit = (ret: T) => {}) = {
    CoreSystem.transactionExecutorPool.submit(new Callable[Try[T]] {
      override def call() = {
        var tx = Option.empty[TransactionStatus]
        Try {
          tx = Option(beginTransaction(trxName = trxName, readOnly = ro, defType = propType))
          val res = body
          tx.foreach(commit)
          onSuccess(res)
          res
        } match {
          case r: Success[T] => r
          case ex: Failure[T] =>
            tx.foreach(rollback)
            tx = None
            onException(ex.exception.getMessage, ex.getClass.getSimpleName)
            CoreSystem.log.error(s"doInThreadTransaction($trxName) failed", ex.exception)
            ex
        }
      }
    })
  }

}
