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

object NotificationManager {

  import akka.routing.RoundRobinPool
  import scala.util.{Failure, Success, Try}

  case class EmailNotification(email: String, subject: String, body: String)

  def props() = {
    Props(classOf[NotificationManagerActor])
  }

  class NotificationManagerActor extends Actor with ActorLogging {

    import concurrent.duration._
    import context.dispatcher

    val config = context.system.settings.config
    val notificationPoolSize = Try(config.getInt("gameProperties.notificationPoolSize")).toOption.getOrElse(10)
    val (defaultFrom, smtpHost, smtpPort, smtpLogin, smtpPass, smtpUseSSL) = Try((
      config.getString("emailSettings.defaultFrom"),
      config.getString("emailSettings.smtpHost"),
      config.getInt("emailSettings.smtpPort"),
      config.getString("emailSettings.smtpLogin"),
      config.getString("emailSettings.smtpPass"),
      config.getBoolean("emailSettings.smtpUseSSL")
      )).toOption.getOrElse(("", "", 0, "", "", false))
    val workers = context.actorOf(RoundRobinPool(notificationPoolSize).props(
      Props(classOf[EmailNotificationWorker], defaultFrom, smtpHost, smtpPort, smtpLogin, smtpPass, smtpUseSSL)), "roundRouter")

    context.system.scheduler.scheduleOnce(20.seconds, self, EmailNotification("alex.shniperson@gmail.com", "brr test", "brr test"))

    def receive: Receive = {
      case msg: EmailNotification => workers.forward(msg)
    }
  }

  class EmailNotificationWorker(sentFrom: String,
                                smtpHost: String,
                                smtpPort: Int,
                                smtpLogin: String,
                                smtpPass: String,
                                smtpUseSSL: Boolean) extends Actor with ActorLogging {

    import org.apache.commons.mail._

    case class Mail(from: (String, String), // (email -> name)
                    to: Seq[String],
                    cc: Seq[String] = Seq.empty,
                    bcc: Seq[String] = Seq.empty,
                    subject: String,
                    message: String,
                    richMessage: Option[String] = None,
                    attachment: Option[java.io.File] = None)

    sealed abstract class MailType

    case object Plain extends MailType

    case object Rich extends MailType

    case object MultiPart extends MailType

    def receive: Receive = {
      case msg: EmailNotification if !List(sentFrom, smtpHost, smtpLogin, smtpPass).forall(_.isEmpty) =>
        sendMail(Mail(
          (sentFrom, "NoReply"),
          Seq(msg.email),
          Seq.empty,
          Seq.empty,
          msg.subject,
          msg.body,
          Option.empty,
          Option.empty))

      case any => log.warning(s">>> Unhandled message <$any> or SMTP configured bad.")
    }

    def sendMail(mail: Mail): Unit = {
      Try {
        val format =
          if (mail.attachment.isDefined) MultiPart
          else if (mail.richMessage.isDefined) Rich
          else Plain

        val commonsMail: Email = format match {
          case Plain => new SimpleEmail().setMsg(mail.message)
          case Rich => new HtmlEmail().setHtmlMsg(mail.richMessage.get).setTextMsg(mail.message)
          case MultiPart =>
            val attachment = new EmailAttachment()
            attachment.setPath(mail.attachment.get.getAbsolutePath)
            attachment.setDisposition(EmailAttachment.ATTACHMENT)
            attachment.setName(mail.attachment.get.getName)
            new MultiPartEmail().attach(attachment).setMsg(mail.message)
        }

        // TODO Set authentication from your configuration, sys properties or w/e
        commonsMail.setHostName(smtpHost)
        commonsMail.setSmtpPort(smtpPort)
        commonsMail.setAuthentication(smtpLogin, smtpPass)
        if (smtpUseSSL)
          commonsMail.setSSLOnConnect(true)

        // Can't add these via fluent API because it produces exceptions
        mail.to.foreach(x => commonsMail.addTo(x))
        mail.cc.foreach(x => commonsMail.addCc(x))
        mail.bcc.foreach(x => commonsMail.addBcc(x))

        commonsMail.
          setFrom(mail.from._1, mail.from._2).
          setSubject(mail.subject).
          send()
      } match {
        case Success(_) =>
        case Failure(fail) => log.error(fail, "MailNotificator")
      }
    }
  }

}