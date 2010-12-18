#include "mdiwindow.h"

MdiWindow::MdiWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	// Setup UI elements shared among descendants
	this->setMinimumSize(250, 250);
	this->setWindowIcon(QIcon(":/images/openirc.png"));

	// Generate UUID for use with the Container classes internal hashes
	this->uuid = QUuid::createUuid().toString();

	// The toolbar holds all the QActions which will be created
	// by descendant classes. Windows can either use them, or not.
	this->toolbar = new QToolBar(this);

	// The internalWidget is the 'container' for all the controls in the window.
	// That's just how a QMdiSubWindow works.
	this->internalWidget = new QWidget(this);

	// We create a vertical layout, cause it's easier and
	// requires no specific code for the resizing of windows.
	//
	// A subtle thing here is that the generic internalWidget is
	// the parent of the vertical layout.
	this->layout = new QVBoxLayout(this->internalWidget);
	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	layout->addWidget(this->toolbar);

	// The QMdiSubWindow class has this setWidget() function
	// which allows us to simply set the main widget for the window.
	// Basically, we can add anything we want to the generic widget,
	// and the QMdiSubWindow won't care.
	this->setWidget(this->internalWidget);
}

QString MdiWindow::hashName()
{
	return(this->uuid);
}

IRCClient *MdiWindow::client()
{
	return(this->Client);
}

void MdiWindow::setClient(IRCClient *client)
{
	this->Client = client;
}
