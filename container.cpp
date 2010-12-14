#include "container.h"
#include "statuswindow.h"
#include "channelwindow.h"

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
	window->setTitle("Not Connected");

	ChannelWindow *channelWindow = new ChannelWindow(this->mdiArea);
	channelWindow->setTitle(tr("#Channel Window"));
}
