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
	//connect(this, SIGNAL(error(SocketError)), this, SLOT(networkError(SocketError)));

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
						/*
						Server Message
						trigger RAW event
						*/
						Me = Args;
						if (Event == "001") {
							//set server NorS
							//find out our userhost info
							this->sendRawMessage(QString::fromStdString("USERHOST " + Me));
						}
						/*
						SERIOUS parsing of 005 for chanmodes, chantypes, modes, network, prefix, nickmode,namesx,uhnames...
						else if (Event == "005") {
						}
						*/
						else if (Event == "302") {
							//userhost return raw use to set ial of ourself
						}
						else if (Event == "305") {
							//set back from being away
						}
						else if (Event == "306") {
							//we set ourself away
						}
						emit incomingData(this, line);
					}
					else {
						//Nickname Message
						string Nick;
						string Address;
						NickUser.PartialMatch(NorS, &Nick, &Address);
						if (Event == "JOIN" || Event == "PART") {
							emit channelMessageReceived(this, QString::fromStdString((IsChan.PartialMatch(Extra) > 0 ? Extra : Args)).trimmed(),QString::fromStdString(Event).trimmed(),QString::fromStdString(Nick).trimmed(),QString::fromStdString(Address).trimmed(),QString::fromStdString(Extra).trimmed());
						}
						else if (Event == "PRIVMSG") {
							if (IsChan.PartialMatch(Args)) {
								//emit incomingData(this, line);
								emit channelMessageReceived(this, QString::fromStdString(Args).trimmed(),QString::fromStdString(Event).trimmed(),QString::fromStdString(Nick).trimmed(),QString::fromStdString(Address).trimmed(),QString::fromStdString(Extra).trimmed());
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

