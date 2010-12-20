#include "container.h"

#include "statuswindow.h"
#include "channelwindow.h"
#include "optionswindow.h"
#include "serverswindow.h"
#include "pcrecpp.h"
#include "cctohtml.h"

#include <QTextDocument>

Container::Container(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags)
{
	this->setWindowIcon(QIcon(":/images/openirc.png"));
	this->setWindowTitle("OpenIRC");

	this->menu_File_Exit = new QAction(this);
	this->menubar = new QMenuBar(this);
	this->menu_File = new QMenu(this->menubar);
	this->setMenuBar(this->menubar);

	this->menubar->addAction(this->menu_File->menuAction());
	this->menu_File->addAction(this->menu_File_Exit);

	this->menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
	this->menu_File_Exit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));

	// Create the dock window
	this->contextBar = new ContextBar(this, 0);
	this->addDockWidget(Qt::TopDockWidgetArea, this->contextBar);

	this->windowTree = new WindowTree(this, 0);
	this->addDockWidget(Qt::LeftDockWidgetArea, this->windowTree);

	connect(this->windowTree, SIGNAL(windowItemClicked(MdiWindow *)), this, SLOT(windowItemClicked(MdiWindow *)));

	// Create the mdi area
	this->mdiArea = new QMdiArea(this);
	//this->mdiArea->setViewMode(QMdiArea::TabbedView);
	this->setCentralWidget(this->mdiArea);

	this->statusbar = new QStatusBar(this);
	this->statusbar->setObjectName(QString::fromUtf8("statusbar"));
	this->setStatusBar(statusbar);

	// Connect the contextbar signals
	connect(this->contextBar, SIGNAL(optionsClicked()), this, SLOT(optionsButtonClicked()));
	connect(this->contextBar, SIGNAL(serversClicked()), this, SLOT(serversButtonClicked()));
	connect(this->contextBar, SIGNAL(tileClicked()), this, SLOT(tileButtonClicked()));
	connect(this->contextBar, SIGNAL(tileCascadeClicked()), this, SLOT(tileCascadeButtonClicked()));
	connect(this->contextBar, SIGNAL(previousWindowClicked()), this, SLOT(previousWindowButtonClicked()));
	connect(this->contextBar, SIGNAL(nextWindowClicked()), this, SLOT(nextWindowButtonClicked()));

	this->readConfigFile();
	this->newStatusWindow();
}

void Container::newStatusWindow(const QString &server, const int port)
{
	// Create the new status window
	StatusWindow *statusWindow = new StatusWindow(this->mdiArea);
	statusWindow->setWindowTitle(tr("Not Connected"));

	// Create the new IRCClient
	IRCClient *client = new IRCClient(this);
	statusWindow->setClient(client);

	// Add an entry in the window tree
	this->windowTree->addStatusWindow(client->cid, server, statusWindow);

	char newbuf[100];
	sprintf(newbuf,"--- Connection id: %d",client->cid);
	statusWindow->append(1,newbuf);

	QHash<QString, MdiWindow *> windowHash;
	windowHash.insert(statusWindow->hashName(), statusWindow);

	this->windows.insert(client->cid, windowHash);

	if ((!server.isEmpty()) && (port > 0)) {
		// TODO: Connect to the server
		statusWindow->append(1,"--- Connecting to " + server + " (" + QString::number(port) + ")");
		client->connectToHost(server, port);
	}

	// Connect the IRCClient signals to the Container slots
	connect(client, SIGNAL(connected(IRCClient *)), this, SLOT(connected(IRCClient *)));
	connect(client, SIGNAL(disconnected(IRCClient *)), this, SLOT(disconnected(IRCClient *)));
	//connect(client, SIGNAL(ircError(IRCClient *, QAbstractSocket::SocketError)), this, SLOT(ircError(IRCClient *, QAbstractSocket::SocketError)));
	connect(client, SIGNAL(privateMessageReceived(IRCClient *, const QString &, const QString &, const QString &)), this, SLOT(privateMessageReceived(IRCClient *, const QString &, const QString &, const QString &)));
	connect(client, SIGNAL(channelMessageReceived(IRCClient *, const QString &, const QString &, const QString &, const QString &, const QString &)), this, SLOT(channelMessageReceived(IRCClient *, const QString &, const QString &, const QString &, const QString &, const QString &)));
	connect(client, SIGNAL(incomingData(IRCClient *, const QString &)), this, SLOT(incomingData(IRCClient *, const QString &)));

	// connect the new status button to new status window
	connect(statusWindow, SIGNAL(newStatusWin()), this, SLOT(newStatusWindow()));
	connect(statusWindow, SIGNAL(closeEventTriggered(const int, const QString &)), this, SLOT(subWindowClosed(const int, const QString &)));

	statusWindow->show();
}

QueryWindow *Container::newQueryWindow(IRCClient *client, const QString &queryName, const QString &address)
{
	QueryWindow *queryWindow = 0;

	if ((client != 0) && (this->windows.contains(client->cid))) {

		// Create the query window
		queryWindow = new QueryWindow(this->mdiArea);

		queryWindow->setWindowTitle(queryName + " (" + address + ")");
		queryWindow->setOtherNick(queryName);
		queryWindow->setClient(client);

		// Add an entry in the window tree
		this->windowTree->addQueryWindow(client->cid, queryName, queryWindow);

		this->windows[client->cid].insert(queryWindow->hashName(), queryWindow);
		queryWindow->show();

		// Connect any signals to slots
		connect(queryWindow, SIGNAL(closeEventTriggered(const int, const QString &)), this, SLOT(subWindowClosed(const int, const QString &)));
	}

	return(queryWindow);
}

ChannelWindow *Container::newChannelWindow(IRCClient *client, const QString &chanName)
{
	ChannelWindow *chanWindow = 0;

	if ((client != 0) && (this->windows.contains(client->cid))) {

		// Create the query window
		chanWindow = new ChannelWindow(this->mdiArea);

		chanWindow->setWindowTitle(chanName);
		chanWindow->setChannel(chanName);
		chanWindow->setClient(client);
		//this->mdiArea->addSubWindow(chanWindow);

		// Add an entry in the window tree
		this->windowTree->addChannelWindow(client->cid, chanName, chanWindow);

		this->windows[client->cid].insert(chanWindow->hashName(), chanWindow);
		chanWindow->show();

		// Connect any signals to slots
		connect(chanWindow, SIGNAL(closeEventTriggered(const int, const QString &)), this, SLOT(subWindowClosed(const int, const QString &)));
	}

	return(chanWindow);
}
void Container::readConfigFile(const QString &filename)
{
	this->configFile = new IniFile(filename);
}

void Container::optionsButtonClicked()
{
	OptionsWindow optionsWindow(this->configFile);
	optionsWindow.exec();
}

void Container::serversButtonClicked()
{
	IniFile *serversFile = new IniFile("servers.ini");

	ServersWindow serversWindow(serversFile);

	connect(&serversWindow, SIGNAL(clicked(const QString &, const int)), this, SLOT(serversWindowConnectClicked(const QString &, const int)));
	serversWindow.exec();
}

void Container::tileButtonClicked()
{
	this->mdiArea->tileSubWindows();
}

void Container::tileCascadeButtonClicked()
{
	this->mdiArea->cascadeSubWindows();
}

void Container::previousWindowButtonClicked()
{
	QList<QMdiSubWindow *> subWindows = this->mdiArea->subWindowList();
	int indexOfActiveSubWindow = subWindows.indexOf(this->mdiArea->activeSubWindow());

	if (indexOfActiveSubWindow == 0) {
		this->mdiArea->setActiveSubWindow(subWindows.last());
	} else{
		this->mdiArea->setActiveSubWindow(subWindows.at(indexOfActiveSubWindow - 1));
	}
}

void Container::nextWindowButtonClicked()
{
	QList<QMdiSubWindow *> subWindows = this->mdiArea->subWindowList();
	int indexOfActiveSubWindow = subWindows.indexOf(this->mdiArea->activeSubWindow());

	if (this->mdiArea->activeSubWindow() == subWindows.last()) {
		this->mdiArea->setActiveSubWindow(subWindows.first());
	} else{
		this->mdiArea->setActiveSubWindow(subWindows.at(indexOfActiveSubWindow + 1));
	}
}

void Container::connected(IRCClient *client)
{
	//int statusWindowsCount = statusWindows.count();
	StatusWindow *statusWindow = 0;

	QHash<QString, MdiWindow *>::const_iterator windowIter;
	QHash<QString, MdiWindow *> windows = this->windows[client->cid];

	for (windowIter = windows.constBegin(); windowIter != windows.constEnd(); windowIter++) {
		MdiWindow *window = *windowIter;

		if (window->windowType() == MdiWindow::StatusWindow) {
			statusWindow = (StatusWindow *)(*windowIter);
			break;
		}
	}

	if (statusWindow == 0) {
		return;
	}

	this->windowTree->renameItem(client->cid, statusWindow->hashName(), client->peerName());
	statusWindow->setWindowTitle("Status: " + this->configFile->value("UserInfo", "nick") + " on (" + client->peerName() + ")");
	statusWindow->append(1,"--- Connected to " + client->peerName());

        char newbuf[100];
        sprintf(newbuf,"--- Connection id: %d",client->cid);
        statusWindow->append(1,newbuf);


	client->sendRawMessage("NICK " + this->configFile->value("UserInfo", "nick"));

        QString Email = this->configFile->value("UserInfo", "email");
        QString Server = this->configFile->value("IrcServer", "server");
        QString RealName = this->configFile->value("UserInfo", "realName");
        string Email1;
        string Email2;

        pcrecpp::RE re("^([^@]+)@(.*)$");

	if (!re.PartialMatch(Email.toStdString(), &Email1, &Email2)) {
		Email1 = "OpenIRC";
		Email2 = "OpenIRC.Linux.Sh";
	}
	// USER Email1 "Email2" "server" :fullname
	client->sendRawMessage(QString::fromStdString("USER " + Email1 + " \"" + Email2 + "\" \"" + Server.toStdString() + "\" :" + RealName.toStdString()));

//	for (int i = 0; i < statusWindowsCount; i++) {
//		StatusWindow *statusWindow = statusWindows.at(i);
//		if (statusWindow->client() == client) {
//			statusWindow->appendToMainBuffer("--- Connected to server");
//			//client->changeNick("mw007\n\rUSER mw007 mw007 irc.webchat.org :mw");
//			client->sendRawMessage(tr("NICK mw007"));
//			client->sendRawMessage(tr("USER mw mw irc.webchat.org :mw"));
//		}
//	}
}

void Container::disconnected(IRCClient *client)
{
	//StatusWindow *statusWindow = (StatusWindow *)this->windows[client->cid]["__STATUS__"];
	//statusWindow->append("--- Disconnected from server");

/*	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer("--- Disconnected from server");
		}
	}
*/
}

void Container::ircError(IRCClient *client, QAbstractSocket::SocketError error)
{
/*	
	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer("!!! A socket error occurred");
		}
	}
*/
}

void Container::privateMessageReceived(IRCClient *client, const QString &nick, const QString &address, const QString &message)
{
	QueryWindow *queryWindow = 0;

	QHash<QString, MdiWindow *>::const_iterator queryIter;
	QHash<QString, MdiWindow *> queryWindows = this->windows[client->cid];

	for (queryIter = queryWindows.constBegin(); queryIter != queryWindows.constEnd(); queryIter++) {
		MdiWindow *mdiWindow = (*queryIter);

		if ((mdiWindow->windowType() == MdiWindow::QueryWindow) && (((QueryWindow *)mdiWindow)->otherNick() == nick)) {
			queryWindow = (QueryWindow *)mdiWindow;
		}
	}

	if (queryWindow == 0) {
		queryWindow = this->newQueryWindow(client, nick, address);
	}

	this->windowTree->maybeHighlightItem(client->cid, queryWindow->hashName());
	queryWindow->append(1,"12<" + nick + "12> " + message);
}

void Container::channelMessageReceived(IRCClient *client, const QString &chan, const QString &event, const QString &nick, const QString &address, const QString &message)
{
	ChannelWindow *chanWindow = 0;

	QHash<QString, MdiWindow *>::const_iterator chanIter;
	QHash<QString, MdiWindow *> chanWindows = this->windows[client->cid];

	for (chanIter = chanWindows.constBegin(); chanIter != chanWindows.constEnd(); chanIter++) {
		MdiWindow *mdiWindow = (*chanIter);

		if ((mdiWindow->windowType() == MdiWindow::ChannelWindow) && (((ChannelWindow *)mdiWindow)->channel() == chan)) {
			chanWindow = (ChannelWindow *)mdiWindow;
		}
	}

	// Only open a window on client JOIN
	if ((chanWindow == 0) && (event == "JOIN") && (nick == QString::fromStdString(client->Me))) {
		chanWindow = this->newChannelWindow(client, chan);
	}

	if (chanWindow == 0) {
		return;
	}

	this->windowTree->maybeHighlightItem(client->cid, chanWindow->hashName());

	if (event == "JOIN") { chanWindow->append(10,Qt::escape("* Joins: " + nick + " (" + address + ")")); }
	else if (event == "PART") { chanWindow->append(10,Qt::escape("10* Parts: " + nick + " (" + address + ")")); }
	else if (event == "PRIVMSG") { chanWindow->append(1,Qt::escape("12<" + nick + "12> " + message)); }
	else if (event == "ACTION") { chanWindow->append(7,Qt::escape("7* " + nick + " " + message)); }
        else {
		chanWindow->append(12,"* Error: chan(" + chan + ") event(" + event + ") nick(" + nick + ") addres(" + address + ") message(" + message + ")");
	}
}

void Container::incomingData(IRCClient *client, const QString &data) // FIXME: Remove this later
{
	//StatusWindow *statusWindow = (StatusWindow *)this->windows[client->cid]["__STATUS__"];
	//statusWindow->append(data);

	QHash<QString, MdiWindow *>::const_iterator windowIter;
	QHash<QString, MdiWindow *> windows = this->windows[client->cid];

	for (windowIter = windows.constBegin(); windowIter != windows.constEnd(); windowIter++) {
		MdiWindow *window = *windowIter;

		if (window->windowType() == MdiWindow::StatusWindow) {
			window->append(1,data);
			break;
		}
	}
}

void Container::serversWindowConnectClicked(const QString &server, const int port)
{
	qDebug() << "Servers window closed and we want to connect to: " << server << " (" << port << ")" << endl;

	QString awesome("awesome");
	qDebug() << awesome << endl;
	this->newStatusWindow(server, port);
}

void Container::windowItemClicked(MdiWindow *subWindow)
{
	this->mdiArea->setActiveSubWindow(subWindow);
}

void Container::subWindowClosed(const int cid, const QString &hashName)
{
	qDebug() << "Container::subWindowClosed() -- Attempting to remove window from window hash" << endl;
	// Remove the window from the internal hash list
	if (this->windows.contains(cid)) {
		qDebug() << "Container::subWindowClosed() -- Removing <" << cid << " , " << hashName << "> from internal window hash" << endl;
		this->windows[cid].remove(hashName);
	}

	// Remove the window from the window tree
	this->windowTree->removeItem(cid, hashName);

	//qDebug() << "Child window closed (cid=" << cid << ") (hashName=" << hashName << ")" << endl;
}
