#ifndef OPENIRC_IRCCLIENT_H
#define OPENIRC_IRCCLIENT_H

#include <QtNetwork>
#include "ircclient.h"

class IRCClient : public QTcpSocket
{
	Q_OBJECT

  public:
  	static int cid;
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

	void incomingData(IRCClient *client, const QString &data); // FIXME: Remove this later
	void privateMessageReceived(IRCClient *client, const QString &nick, const QString &message);

  public slots:
  	void connectedToIRCHost();
	void disconnectedFromIRCHost();
	void networkError(SocketError error);

	void dataReceived();

  private:
  	IRCClient *client;
};

#endif
