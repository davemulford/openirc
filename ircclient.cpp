#include "ircclient.h"

int IRCClient::cid;

IRCClient::IRCClient(QObject *parent, const QString &server, const int port)
  : QTcpSocket(parent)
{
	this->cid++;

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
	QByteArray data = this->readAll();
	emit incomingData(this, QString(data));
}

