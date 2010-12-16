#include "ircclient.h"
#include "pcrecpp.h"

using namespace std;

int IRCClient::Cid = 0;

IRCClient::IRCClient(QObject *parent, const QString &server, const int port)
  : QTcpSocket(parent)
{
	this->cid = Cid++;

	 // Connect the signals and slots
	connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(this, SIGNAL(connected()), this, SLOT(connectedToIRCHost()));
	connect(this, SIGNAL(disconnected()), this, SLOT(disconnectedFromIRCHost()));
	connect(this, SIGNAL(error(SocketError)), this, SLOT(error(SocketError)));

	 if (server != 0) {
		 // TODO: Connect to the server
	 }
}

void IRCClient::changeNick(const QString &newNick)
{
	QString changeNickString("NICK ");
	changeNickString.append(newNick);

	this->write(changeNickString.toAscii());
}

void IRCClient::sendRawMessage(const QString &rawMessage)
{
	QString message = QString(rawMessage);
	message.append("\n");
	this->write(message.toAscii());
}

void IRCClient::connectedToIRCHost()
{
	emit connected(this);
}

void IRCClient::disconnectedFromIRCHost()
{
	emit disconnected(this);
}

void IRCClient::networkError(SocketError error)
{
	emit ircError(this, error);
}

void IRCClient::dataReceived()
{
	string NorS;
	string Event;
	string Args;
	string Extra;

	pcrecpp::RE ParseLine("^(?:\\x3a(\\S+) )?(\\d{3}|[a-zA-Z]+)(?: ((?:[^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)(?: [^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)*))?(?: \\x3a([^\\x00\\x0a\\x0d]*))?\\x20*$");
	pcrecpp::RE NickOrServer("^[^!@]+$");
	pcrecpp::RE NickUser("^([^!]+)!(.*)$");
	pcrecpp::RE IsChan("^\\#");

	while (this->canReadLine()) {
		QString line = this->readLine();
		line.remove('\r');
		line.remove('\n');
		if (!line.isEmpty()) {
  			if (ParseLine.PartialMatch(line.toStdString(), &NorS, &Event, &Args, &Extra)) {
				if (NorS == "") {
	    				if (Event == "PING") { this->sendRawMessage(QString::fromStdString("PONG " + Extra)); }
				}
				else {
					if (NickOrServer.PartialMatch(NorS)) {
						//Server Message
						emit incomingData(this, line);
					}
					else {
						//Nickname Message
						string Nick;
						string Address;
						NickUser.PartialMatch(NorS, &Nick, &Address);
						if (Event == "PRIVMSG") {
							if (IsChan.PartialMatch(Args)) {
								emit incomingData(this, line);
							}
							else { 
								emit privateMessageReceived(this, QString::fromStdString(Nick).trimmed(),QString::fromStdString(Address).trimmed(),QString::fromStdString(Extra).trimmed());
							}
						}
						else { emit incomingData(this, line); }
					}
				}
			}
		}
	}

	//QByteArray data = this->readAll();
	//emit incomingData(this, QString(data));
}

