#include "ircclient.h"
#include "pcrecpp.h"
#include <sstream>

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
	string args;
	string Extra;
	string Action;

	string JoinPrefix;
	string JoinNick;
	string JoinAddress;

	pcrecpp::RE ParseLine("^(?:\\x3a(\\S+) )?(\\d{3}|[a-zA-Z]+)(?: ((?:[^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)(?: [^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)*))? ?(?:\\x3a([^\\x00\\x0a\\x0d]*))?\\x20*$");
	pcrecpp::RE ParseJoin("(?:^| )([\\@\\+\\-]+)?([^! ]+)!?([^ ]+)?");
	pcrecpp::RE NickOrServer("^[^!@]+$");
	pcrecpp::RE NickUser("^([^!]+)!(.*)$");
	pcrecpp::RE IsChan("^\\#");
	pcrecpp::RE IsAction("^ACTION (.*)$");

	while (this->canReadLine()) {
		QString line = this->readLine();
		line.remove('\r');
		line.remove('\n');
		if (!line.isEmpty()) {
  			if (ParseLine.PartialMatch(line.toStdString(), &NorS, &Event, &args, &Extra)) {
			//qDebug() << "Split Data: NorS(" + QString::fromStdString(NorS) + ") Event(" + QString::fromStdString(Event) + ") args(" + QString::fromStdString(args) + ") Extra(" + QString::fromStdString(Extra) + ")";

				istringstream oss(args);
    				vector<string> Args;
				string word;
				while(oss >> word) {
					Args.push_back(word);
				}

				if (NorS == "") {
	    				if (Event == "PING") { this->sendRawMessage(QString::fromStdString("PONG " + Extra)); }
				}
				else {
					if (NickOrServer.PartialMatch(NorS)) {
						/*
						Server Message
						trigger RAW event
						*/
						Me = Args.at(0);
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
						else if (Event == "353") {
							pcrecpp::StringPiece ExData(Extra);
							while (ParseJoin.Consume(&ExData,&JoinPrefix,&JoinNick,&JoinAddress)) {
								emit channelJoined(this,QString::fromStdString(Args.at(1) == "=" ? Args.at(2) : Args.at(1)),QString::fromStdString(JoinNick));
							}							
						}
						emit incomingData(this, line);
					}
					else {
						//Nickname Message
						string Nick;
						string Address;
						NickUser.PartialMatch(NorS, &Nick, &Address);
						if (Event == "JOIN" || Event == "PART") {
							emit channelMessageReceived(this, QString::fromStdString((IsChan.PartialMatch(Extra) > 0 ? Extra : Args.at(0))),QString::fromStdString(Event),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Extra));
							if (Event == "JOIN") {
								emit channelJoined(this,QString::fromStdString((IsChan.PartialMatch(Extra) > 0 ? Extra : Args.at(0))),QString::fromStdString(Nick));
							}
							else {
								emit channelParted(this,QString::fromStdString((IsChan.PartialMatch(Extra) > 0 ? Extra : Args.at(0))),QString::fromStdString(Nick));
							}
						}
						else if (Event == "PRIVMSG") {
							if (IsChan.PartialMatch(Args.at(0))) {
								if (IsAction.PartialMatch(Extra,&Action)) {
									emit channelMessageReceived(this, QString::fromStdString(Args.at(0)),QString::fromStdString("ACTION"),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Action));
								}
								else {
									emit channelMessageReceived(this, QString::fromStdString(Args.at(0)),QString::fromStdString(Event),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Extra));
								}
							}
							else { 
								emit privateMessageReceived(this, QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Extra));
							}
						}
						else { emit incomingData(this, line); }
					}
				}
			}
		}
		else {
			qDebug() << "Parse Failed! line(" + line + ")";
		}
	}

	//QByteArray data = this->readAll();
	//emit incomingData(this, QString(data));
}

