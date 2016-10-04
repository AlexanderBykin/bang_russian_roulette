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

import akka.actor._
import net.orionlab.brr.domain._
import ProtoMessages.MessageRequestBuyShopItemBase.MessageRequestBuyShopItem.eItemType
import net.orionlab.brr.utils.{CoreSystem, CoreTransaction}

object PaymentRequestManager {

  case class CheckPaymentRequest(requestId: Option[Long] = None, itemType: eItemType)

  case class PaymentRequestResult(id: Long, itemName: String, itemType: eItemType, result: PaymentRequestStatus)

  def props() = {
    Props(classOf[PaymentRequestManagerActor])
  }

  class PaymentRequestManagerActor extends Actor with ActorLogging {
    def receive = {
      case msg: CheckPaymentRequest => context.actorOf(Props(classOf[PaymentRequestWorker])).forward(msg)
    }
  }

  class PaymentRequestWorker extends Actor with ActorLogging with CoreTransaction {

    import collection.JavaConversions._
    import java.io.DataOutputStream
    import java.net.{HttpURLConnection, URL}
    import java.util.{List => JList, Date => JDate}

    def receive = {
      case msg: CheckPaymentRequest =>
        val replyTo = sender()
        doInThreadTransaction({
          getSessionFactoryDao.getCurrentSession.createQuery("FROM net.orionlab.brr.domain.PlayerPaymentRequest WHERE" +
            msg.requestId.fold("")(x => s" id = $x") +
            s" AND approveStatus = '${PaymentRequestStatus.NEW}'")
            .list().asInstanceOf[JList[PlayerPaymentRequest]]
            .map(x => {
              val approveStatus = isReceiptValid(x.getReceipt, x.getMarketType)
              x.setApproveStatus(approveStatus)
              x.setDateEdit(new JDate)
              PaymentRequestResult(x.getId, x.getItemName, msg.itemType, approveStatus)
            })
        }).get.toOption.foreach(_.foreach(x => replyTo ! x))
        context.stop(self)
    }

    def isReceiptValid(receiptData: Array[Byte], marketType: MarketType): PaymentRequestStatus = {
      import pushka.json._

      val (urlString, isNeedRequest) = marketType match {
        case MarketType.APPLE =>
          if (CoreSystem.isDebugMode) ("https://sandbox.itunes.apple.com/verifyReceipt", true)
          else ("https://buy.itunes.apple.com/verifyReceipt", true)
        case MarketType.GOOGLE => ("", false)
      }

      if (isNeedRequest) {
        val encodedReceipt = new sun.misc.BASE64Encoder().encode(receiptData)
        val json = write(Map("receipt-data" -> encodedReceipt)).toString

        //    log.info(s"checking json receipt='$json'")

        val url = new URL(urlString)
        val connection = url.openConnection().asInstanceOf[HttpURLConnection]
        connection.setDoOutput(true)
        connection.setDoInput(true)
        connection.setInstanceFollowRedirects(false)
        connection.setRequestMethod("POST")
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded")
        connection.setRequestProperty("charset", "utf-8")
        connection.setRequestProperty("Content-Length", json.length().toString)
        connection.setUseCaches(false)

        val writer = new DataOutputStream(connection.getOutputStream)
        writer.writeBytes(json)
        writer.flush()

        val response = io.Source.fromInputStream(connection.getInputStream).getLines().mkString("")

        writer.close()
        connection.disconnect()

        val respMap = read[Map[String, Int]](response)
        if (respMap.getOrElse("status", -1) == 0) PaymentRequestStatus.SUCCESS
        else PaymentRequestStatus.FAILED
      } else PaymentRequestStatus.SUCCESS
    }

  }

}