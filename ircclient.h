#ifndef OPENIRC_IRCCLIENT_H
#define OPENIRC_IRCCLIENT_H

#include "ialitem.h"
#include <QtNetwork>
#include <QString>
#include <string>

using namespace std;

class IRCClient : public QTcpSocket
{
	Q_OBJECT

  private:
  	static int Cid;
	QHash<QString, QStringList> tempChannelJoins;
	QHash<QString, IALItem> ial;

  public:
	//================ Dedicated IRC Parser Variables ==================
	string Me;
	string chanmodes;
	string chantypes;
	int modespl;
	string network;
	string nickmode;
	string prefix;
	bool usenamesx; //extended names protocol, show all modes @%+nick
	bool useuhnames; //extended names protocol, show nick!user@host in raw
	bool away;
	int awaytime;
	//==================================================================


	//==================== Internal List Functions =====================
	void IALAdd (const QString &nick);
	void IALDel (const QString &nick);
	void IALRen (const QString &nick, const QString &newnick);
	void IALChanAdd(const QString &nick, const QString &chan, QString &prefix);
	void IALChanDel(const QString &nick, const QString &chan);
	IALItem* GetIAL(const QString &nick);
	//==================================================================

	int cid;
  	IRCClient(QObject *parent = 0, const QString &server = 0, const int port = 6667);
	void joinChannel(const QString &channel);
	void partChannel(const QString &channel);

	void changeNick(const QString &newNick);
	void sendPrivateMessage(const QString &nick, const QString &message);

	void sendRawMessage(const QString &rawMessage);

  Q_SIGNALS:
	void connected(IRCClient *client);
	void disconnected(IRCClient *client);

	void ircError(IRCClient *client, SocketError error);

  	void channelJoined(IRCClient *client, const QString &channel, const QString &nick);
	void channelParted(IRCClient *client, const QString &channel, const QString &nick);
	void channelJoinCompleteNickList(IRCClient *client, const QString &channel, const QStringList &list);

	void privateMessageReceived(IRCClient *client, const QString &nick, const QString &address, const QString &message);
	void channelMessageReceived(IRCClient *client, const QString &chan, const QString &event, const QString &nick, const QString &address, const QString &message);

	void incomingData(IRCClient *client, const QString &data); // FIXME: Remove this later

  public slots:
  	void connectedToIRCHost();
	void disconnectedFromIRCHost();
	void networkError(SocketError error);

	void dataReceived();
};

#endif
