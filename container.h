#pragma once
#ifndef OPENIRC_CONTAINER_H
#define OPENIRC_CONTAINER_H

#include <QtGui>
#include <QtNetwork>

#include "statuswindow.h"
#include "contextbar.h"
#include "ircclient.h"
#include "inifile.h"
#include "querywindow.h"

class Container : public QMainWindow
{
  Q_OBJECT

  public:
	Container(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	void newStatusWindow(void);
	QueryWindow *newQueryWindow(IRCClient *client, const QString &queryName, const QString &address);

	/*newQueryWindow();
	  newStatusWindow();
	  newChannelWindow();*/

	/*protected:
	  void closeEvent(QCloseEvent *event);*/

  public slots:
  	void optionsButtonClicked();
  	void serversButtonClicked();

  	void tileHorizontalButtonClicked();
  	void tileCascadeButtonClicked();

	void previousWindowButtonClicked();
	void nextWindowButtonClicked();

	void connected(IRCClient *client);
	void disconnected(IRCClient *client);

	void ircError(IRCClient *client, QAbstractSocket::SocketError error);

  	//void channelJoined(IRCClient *client, const QString &channel, const QString &nick);
	//void channelParted(IRCClient *client, const QString &channel, const QString &nick);

	void privateMessageReceived(IRCClient *client, const QString &nick, const QString &address, const QString &message);

	void incomingData(IRCClient *client, const QString &data); // FIXME: Remove this later

  private:
	QMenuBar *menubar;
	QMenu *menu_File;
	QAction *menu_File_Exit;

	QMdiArea *mdiArea;
	ContextBar *contextBar;
	QStatusBar *statusbar;
	QToolBar *toolbar;

	QAction *MainAction;

	QList<IRCClient *> clients;

	QHash<int, QHash<QString, QMdiSubWindow *> > windows;

	//QList<StatusWindow *> statusWindows;
	//QList<QMdiSubWindow *> channelWindows;
	//QList<QMdiSubWindow *> queryWindows;

	IniFile *configFile;
	void readConfigFile(const QString &filename = "openirc.ini");
};

#endif
