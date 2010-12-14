#include "container.h"

#include "statuswindow.h"
#include "channelwindow.h"
#include "querywindow.h"

Container::Container(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags)
{
        this->toolbar = new QToolBar(this);
        this->toolbar->setObjectName(QString::fromUtf8("toolBar"));

	this->MainAction = new QAction(QIcon(":/images/whois.png"), tr(""), this->toolbar);
	this->MainAction->setToolTip(tr("Whois"));
	this->toolbar->addAction(this->MainAction);

        this->addToolBar(Qt::TopToolBarArea, toolbar);

	// Create the dock window
	//this->contextBar = new ContextBar(this, 0);
	//this->addDockWidget(Qt::TopDockWidgetArea, this->contextBar);

	// Create the mdi area
	this->mdiArea = new QMdiArea(this);
	this->setCentralWidget(this->mdiArea);

        this->statusbar = new QStatusBar(this);
        this->statusbar->setObjectName(QString::fromUtf8("statusbar"));
        this->setStatusBar(statusbar);

	this->newWindow();
}

void Container::newWindow()
{
	StatusWindow *window = new StatusWindow(this->mdiArea);
	window->setTitle(tr("Not Connected"));

	ChannelWindow *channelWindow = new ChannelWindow(this->mdiArea);
	channelWindow->setTitle(tr("#Channel Window"));

	QueryWindow *queryWindow = new QueryWindow(this->mdiArea);
	queryWindow->setTitle(tr("@Query Window"));
}
