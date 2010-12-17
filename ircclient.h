#ifndef OPENIRC_IRCCLIENT_H
#define OPENIRC_IRCCLIENT_H

#include <QtNetwork>
#include <string>

using namespace std;

class IRCClient : public QTcpSocket
{
	Q_OBJECT

  private:
  	static int Cid;
  public:
	string Me;
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
