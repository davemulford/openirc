#include "statuswindow.h"

StatusWindow::StatusWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0) 
{
	// Set the minimum size of the status window
	this->setMinimumSize(250, 250);

	// Create the controls that the window will hold.
	this->mainBuffer = new QTextEdit(this);
	this->inputBuffer = new QLineEdit(this);

	this->toolbar = new QToolBar(this->internalWidget);

	this->newConnectionAction = new QAction(QIcon(":/images/new_connection.png"), tr(""), this->toolbar);
	this->newConnectionAction->setToolTip(tr("New Connection"));
	this->toolbar->addAction(this->newConnectionAction);

	this->connectDisconnectAction = new QAction(QIcon(":/images/connect.png"), tr(""), this->toolbar);
	this->connectDisconnectAction->setToolTip(tr("Connect"));
	this->toolbar->addAction(this->connectDisconnectAction);

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

	// We add the controls to the vertical layout
	layout->addWidget(this->toolbar);
	layout->addWidget(this->mainBuffer);
	layout->addWidget(this->inputBuffer);

	// The QMdiSubWindow class has this setWidget() function
	// which allows us to simply set the main widget for the window.
	// Basically, we can add anything we want to the generic widget,
	// and the QMdiSubWindow won't care.
	this->setWidget(this->internalWidget);

	// Connect any signals/slots we want
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void StatusWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void StatusWindow::inputBufferReturnPressed()
{
	this->mainBuffer->append(this->inputBuffer->text());
	this->inputBuffer->clear();
}

void StatusWindow::newButtonClicked() {
	this->mainBuffer->append(tr("*** New connection button clicked"));
}

void StatusWindow::connectDisconnectButtonClicked()
{
	this->mainBuffer->append(tr("*** Connect/Disconnect button clicked"));
}
