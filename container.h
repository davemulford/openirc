#pragma once
#ifndef OPENIRC_CONTAINER_H
#define OPENIRC_CONTAINER_H

#include <QtGui>
#include <QtNetwork>

#include "statuswindow.h"
#include "contextbar.h"
#include "ircclient.h"

class Container : public QMainWindow
{
  Q_OBJECT

  public:
	Container(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	void newStatusWindow(void);

	/*newQueryWindow();
	  newStatusWindow();
	  newChannelWindow();*/

	/*protected:
	  void closeEvent(QCloseEvent *event);*/

  public slots:
  	void tileHorizontalButtonClicked();
  	void tileCascadeButtonClicked();

	void previousWindowButtonClicked();
	void nextWindowButtonClicked();

	void connected(IRCClient *client);
	void disconnected(IRCClient *client);

	void ircError(IRCClient *client, QAbstractSocket::SocketError error);

  	//void channelJoined(IRCClient *client, const QString &channel, const QString &nick);
	//void channelParted(IRCClient *client, const QString &channel, const QString &nick);

	void incomingData(IRCClient *client, const QString &data); // FIXME: Remove this later
	//void privateMessageReceived(IRCClient *client, const QString &nick, const QString &message);



  private:
	QMdiArea *mdiArea;
	ContextBar *contextBar;
	QStatusBar *statusbar;
	QToolBar *toolbar;

	QAction *MainAction;

	QList<IRCClient *> clients;

	QList<StatusWindow *> statusWindows;
	QList<QMdiSubWindow *> channelWindows;
	QList<QMdiSubWindow *> queryWindows;
};

#endif
