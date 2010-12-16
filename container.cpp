#include "container.h"

#include "statuswindow.h"
#include "channelwindow.h"
#include "querywindow.h"
#include "optionswindow.h"
#include "serverswindow.h"

Container::Container(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags)
{
	this->menu_File_Exit = new QAction(this);
	this->menubar = new QMenuBar(this);
	this->menu_File = new QMenu(this->menubar);
	this->setMenuBar(this->menubar);

	this->menubar->addAction(this->menu_File->menuAction());
	this->menu_File->addAction(this->menu_File_Exit);

	this->menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
	this->menu_File_Exit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));

	/*this->toolbar = new QToolBar(this);
	this->toolbar->setObjectName(QString::fromUtf8("toolBar"));

	this->MainAction = new QAction(QIcon(":/images/whois.png"), tr(""), this->toolbar);
	this->MainAction->setToolTip(tr("Whois"));
	this->toolbar->addAction(this->MainAction);

	this->addToolBar(Qt::TopToolBarArea, toolbar);*/

	// Create the dock window
	this->contextBar = new ContextBar(this, 0);
	this->addDockWidget(Qt::TopDockWidgetArea, this->contextBar);

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
	connect(this->contextBar, SIGNAL(tileHorizontalClicked()), this, SLOT(tileHorizontalButtonClicked()));
	connect(this->contextBar, SIGNAL(tileCascadeClicked()), this, SLOT(tileCascadeButtonClicked()));
	connect(this->contextBar, SIGNAL(previousWindowClicked()), this, SLOT(previousWindowButtonClicked()));
	connect(this->contextBar, SIGNAL(nextWindowClicked()), this, SLOT(nextWindowButtonClicked()));

	this->readConfigFile();
	this->newStatusWindow();
}

void Container::newStatusWindow()
{
	// Create the new status window
	StatusWindow *statusWindow = new StatusWindow(this->mdiArea);
	statusWindow->setTitle(tr("Not Connected"));

	// Create the new IRCClient
	IRCClient *client = new IRCClient(this);
	statusWindow->setClient(client);

	this->statusWindows.append(statusWindow);

	// Connect the IRCClient signals to the Container slots
	connect(client, SIGNAL(connected(IRCClient *)), this, SLOT(connected(IRCClient *)));
	connect(client, SIGNAL(disconnected(IRCClient *)), this, SLOT(disconnected(IRCClient *)));
	connect(client, SIGNAL(ircError(IRCClient *, QAbstractSocket::SocketError error)), this, SLOT(ircError(IRCClient *, QAbstractSocket::SocketError error)));
	connect(client, SIGNAL(incomingData(IRCClient *, const QString &)), this, SLOT(incomingData(IRCClient *, const QString &)));

	/*ChannelWindow *channelWindow = new ChannelWindow(this->mdiArea);
	channelWindow->setTitle(tr("#Channel Window"));

	QueryWindow *queryWindow = new QueryWindow(this->mdiArea);
	queryWindow->setTitle(tr("@Query Window"));*/
}

void Container::readConfigFile(const QString &filename)
{
	this->configFile = new IniFile(filename);
}

void Container::optionsButtonClicked()
{
	OptionsWindow optionsWindow;//(/*this->configFile*/);
	optionsWindow.exec();
}

void Container::serversButtonClicked()
{
	IniFile *serversFile = new IniFile("servers.ini");
	ServersWindow serversWindow(serversFile);//(/*this->configFile*/);
	serversWindow.exec();
}

void Container::tileHorizontalButtonClicked()
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
	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer("--- Connected to server");
			//client->changeNick("mw007\n\rUSER mw007 mw007 irc.webchat.org :mw");
			client->sendRawMessage(tr("NICK mw007"));
			client->sendRawMessage(tr("USER mw mw irc.webchat.org :mw"));
		}
	}
}

void Container::disconnected(IRCClient *client)
{
	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer("--- Disconnected from server");
		}
	}
}

void Container::ircError(IRCClient *client, QAbstractSocket::SocketError error)
{
	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer("!!! A socket error occurred");
		}
	}
}

void Container::incomingData(IRCClient *client, const QString &data) // FIXME: Remove this later
{
	int statusWindowsCount = statusWindows.count();

	for (int i = 0; i < statusWindowsCount; i++) {
		StatusWindow *statusWindow = statusWindows.at(i);
		if (statusWindow->client() == client) {
			statusWindow->appendToMainBuffer(data);
		}
	}
}

