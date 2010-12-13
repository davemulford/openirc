#include "container.h"
#include "statuswindow.h"

Container::Container()
{
	this->mdiArea = new QMdiArea(this);
	setCentralWidget(this->mdiArea);
	//this->mdiArea->setActivationOrder(WindowOrder::CreationOrder );

	this->newWindow();
}

void Container::newWindow()
{
	Window *window = new Window(this->mdiArea);
	window->setTitle("Not Connected");
}

