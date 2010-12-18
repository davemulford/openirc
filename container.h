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
#include "channelwindow.h"
#include "windowtree.h"
#include "mdiwindow.h"

class Container : public QMainWindow
{
  Q_OBJECT

  public:
	Container(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	QueryWindow *newQueryWindow(IRCClient *client, const QString &queryName, const QString &address);
	ChannelWindow *newChannelWindow(IRCClient *client, const QString &chanName);

	/*newQueryWindow();
	  newStatusWindow();
	  newChannelWindow();*/

	/*protected:
	  void closeEvent(QCloseEvent *event);*/

  public slots:
	void newStatusWindow(const QString &server = QString(), const int port = 0);

  	void optionsButtonClicked();
  	void serversButtonClicked();

  	void tileButtonClicked();
  	void tileCascadeButtonClicked();

	void previousWindowButtonClicked();
	void nextWindowButtonClicked();

	void connected(IRCClient *client);
	void disconnected(IRCClient *client);

	void ircError(IRCClient *client, QAbstractSocket::SocketError error);

  	//void channelJoined(IRCClient *client, const QString &channel, const QString &nick);
	//void channelParted(IRCClient *client, const QString &channel, const QString &nick);

	void privateMessageReceived(IRCClient *client, const QString &nick, const QString &address, const QString &message);
	void channelMessageReceived(IRCClient *client, const QString &chan, const QString &event, const QString &nick, const QString &address, const QString &message);

	void incomingData(IRCClient *client, const QString &data); // FIXME: Remove this later

	// Miscellaneous QDialg slots
	void serversWindowConnectClicked(const QString &server, const int port);

	// The slot to handle when an item is clicked in the window tree
  	void windowItemClicked(MdiWindow *subWindow);

	// Handles when a child window has been closed
	void subWindowClosed(const int cid, const QString &hashName);

  private:
	QMenuBar *menubar;
	QMenu *menu_File;
	QAction *menu_File_Exit;

	ContextBar *contextBar;
	WindowTree *windowTree;

	QMdiArea *mdiArea;
	QStatusBar *statusbar;
	QToolBar *toolbar;

	QAction *MainAction;

	QList<IRCClient *> clients;
	QHash<int, QHash<QString, MdiWindow *> > windows;

	IniFile *configFile;
	void readConfigFile(const QString &filename = "openirc.ini");
};

#endif
