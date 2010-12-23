#include "ircclient.h"
#include "pcrecpp.h"

using namespace std;

int IRCClient::Cid = 0;

IRCClient::IRCClient(QObject *parent, const QString &server, const int port)
  : QTcpSocket(parent) 

{
	// Setup default values for various variables incase they aren't passed in raw 005
	this->cid = Cid++;
	this->prefix = "@%+";
	this->nickmode = "ohv";
	this->chanmodes = "bIe,k,l";
	this->chantypes = "#&";
	this->modespl = 3;
	this->usenamesx = false;
	this->useuhnames = false;
	this->away = false;

	 // Connect the signals and slots
	connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(this, SIGNAL(connected()), this, SLOT(connectedToIRCHost()));
	connect(this, SIGNAL(disconnected()), this, SLOT(disconnectedFromIRCHost()));
	//connect(this, SIGNAL(error(SocketError)), this, SLOT(networkError(SocketError)));

	 if (server != 0) {
		 // TODO: Connect to the server
	 }
}

void IRCClient::AddIAL(const QString &nick)
{
	if (this->ial.contains(nick) == false) {
		IALItem pushme;
		this->ial.insert(nick,pushme);
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
	string word;
	QStringList Args;
	QString line;

	pcrecpp::RE ParseLine("^(?:\\x3a(\\S+) )?(\\d{3}|[a-zA-Z]+)(?: ((?:[^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)(?: [^\\x00\\x0a\\x0d\\x20\\x3a][^\\x00\\x0a\\x0d\\x20]*)*))? ?(?:\\x3a([^\\x00\\x0a\\x0d]*))?\\x20*$");
	pcrecpp::RE NickOrServer("^[^!@]+$");
	pcrecpp::RE NickUser("^([^!]+)!(.*)$");
	pcrecpp::RE IsAction("^ACTION (.*)$");

	while (this->canReadLine()) {
		line = this->readLine();
		line.remove('\r');
		line.remove('\n');
		if (line.isEmpty()) { return; }
		else {
  			if (ParseLine.FullMatch(line.toStdString(), &NorS, &Event, &args, &Extra)) {
			//qDebug() << "Split Data: NorS(" + QString::fromStdString(NorS) + ") Event(" + QString::fromStdString(Event) + ") args(" + QString::fromStdString(args) + ") Extra(" + QString::fromStdString(Extra) + ")";
				Args.clear();
				Args = QString::fromStdString(args).split(" ");
				if (NorS == "") {
	    				if (Event == "PING") { this->sendRawMessage(QString::fromStdString("PONG " + Extra)); }
				}
				else {
					if (NickOrServer.PartialMatch(NorS)) {
						/*
						Server Message
						trigger RAW event
						*/
						if (Event == "001") {
							//set server NorS
							//find out our userhost info
							Me = Args.at(0).toStdString();
							this->sendRawMessage(QString::fromStdString("USERHOST " + Me));
						}
						else if (Event == "005") {
							pcrecpp::RE ChanModes("^CHANMODES=([^ ]+)$");
							pcrecpp::RE ChanTypes("^CHANTYPES=([^ ]+)$");
							pcrecpp::RE Modes("^MODES=([\\d]+)$");
							pcrecpp::RE Network("^NETWORK=([^ ]+)$");
							pcrecpp::RE Prefix("^PREFIX=\\((\\w+)\\)([^ ]+)$");
							for (int x = 0; x < Args.size(); x++) {
								ChanModes.FullMatch(Args.at(x).toStdString(),&chanmodes);
								ChanTypes.FullMatch(Args.at(x).toStdString(),&chantypes);
								Modes.FullMatch(Args.at(x).toStdString(),&modespl);
								Network.FullMatch(Args.at(x).toStdString(),&network);
								Prefix.FullMatch(Args.at(x).toStdString(),&nickmode,&prefix);
								if (Args.at(x) == "NAMESX") { 
									usenamesx = true;
									this->sendRawMessage("PROTOCTL NAMESX");
								}
								if (Args.at(x) == "UHNAMES") {
									useuhnames = true;
									this->sendRawMessage("PROTOCTL UHNAMES");
								}
							}
						}
						else if (Event == "302") {
							string unick,uaddy;
							pcrecpp::RE ParseUhost("^([^=*]+)(?:\\*)?=(?:[+-])([^ ]+)$");
							if (ParseUhost.FullMatch(Extra,&unick,&uaddy)) {
								AddIAL(QString::fromStdString(unick));
								IALItem *entry = &this->ial[QString::fromStdString(unick)];
								entry->address = QString::fromStdString(uaddy);
								qDebug() << "test set of addy: " << entry->address;
							}
							//userhost return raw use to set ial of ourself
						}
						else if (Event == "305") {
							//set back from being away
						}
						else if (Event == "306") {
							//we set ourself away
						}
						else if (Event == "353") {
							QString channel = Args.at(Args.size() - 1);
							QStringList nicklist;

							if (this->tempChannelJoins.contains(channel)) {
								nicklist = this->tempChannelJoins[channel];
							}

							pcrecpp::StringPiece ExData(Extra);
							pcrecpp::RE ParseJoin("(?:^| )([" + this->prefix + "]+)?([^! ]+)!?([^ ]+)?");

							while (ParseJoin.Consume(&ExData,&JoinPrefix,&JoinNick,&JoinAddress)) {
								nicklist << QString::fromStdString(JoinPrefix + JoinNick);
							//	emit channelJoined(this,QString::fromStdString(Args.at(Args.size() - 1)),QString::fromStdString(JoinNick));
							}

							if (!this->tempChannelJoins.contains(channel)) {
								this->tempChannelJoins.insert(channel, nicklist);
							}
						} else if (Event == "366") {
							QString channel = Args.at(Args.size() - 1);

							if (this->tempChannelJoins.contains(channel)) {
								QStringList nicklist = this->tempChannelJoins.take(channel);
								emit channelJoinCompleteNickList(this, channel, nicklist);
							}
						}
						emit incomingData(this, line);
					}
					else {
						pcrecpp::RE IsChan("^[" + this->chantypes + "]");
						//Nickname Message
						string Nick;
						string Address;
						if (NickUser.PartialMatch(NorS, &Nick, &Address)) {
							AddIAL(QString::fromStdString(Nick));
							IALItem *entry = &this->ial[QString::fromStdString(Nick)];
							entry->address = QString::fromStdString(Address);
							qDebug() << "test set of addy: " << entry->address;

							if (Event == "JOIN" || Event == "PART") {
								emit channelMessageReceived(this, (IsChan.PartialMatch(Extra) > 0 ? QString::fromStdString(Extra) : Args.at(0)),QString::fromStdString(Event),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Extra));
								if (Event == "JOIN") {
									emit channelJoined(this,(IsChan.PartialMatch(Extra) > 0 ? QString::fromStdString(Extra) : Args.at(0)),QString::fromStdString(Nick));
								}
								else {
									emit channelParted(this,(IsChan.PartialMatch(Extra) > 0 ? QString::fromStdString(Extra) : Args.at(0)),QString::fromStdString(Nick));
								}
							}
							else if (Event == "PRIVMSG") {
								if (IsChan.PartialMatch(Args.at(0).toStdString())) {
									if (IsAction.PartialMatch(Extra,&Action)) {
										emit channelMessageReceived(this, Args.at(0),QString::fromStdString("ACTION"),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Action));
									}
									else {
										emit channelMessageReceived(this, Args.at(0),QString::fromStdString(Event),QString::fromStdString(Nick),QString::fromStdString(Address),QString::fromStdString(Extra));
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
		}
	}
	//QByteArray data = this->readAll();
	//emit incomingData(this, QString(data));
}

