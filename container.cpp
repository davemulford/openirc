#include "container.h"

#include "statuswindow.h"
#include "channelwindow.h"
#include "querywindow.h"

Container::Container()
{
	this->mdiArea = new QMdiArea(this);
	setCentralWidget(this->mdiArea);
	//this->mdiArea->setActivationOrder(WindowOrder::CreationOrder );

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
