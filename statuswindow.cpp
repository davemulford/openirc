#include "statuswindow.h"

StatusWindow::StatusWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0) 
{
	// Set the minimum size of the status window
	this->setMinimumSize(250, 250);

	// Create the controls that the window will hold.
	this->mainBuffer = new QTextEdit(this);
	this->inputBuffer = new QLineEdit(this);

	// Create the toolbar buttons
	this->toolbarButtons = new QWidget(this);
	this->toolbarLayout = new QHBoxLayout(this->toolbarButtons);
	this->toolbarLayout->setAlignment(Qt::AlignLeft);

	this->btnNew = new QPushButton(QIcon(":/images/new_connection.png"), tr(""), this->toolbarButtons);
	this->btnNew->setMaximumWidth(32);
	this->btnNew->setMinimumWidth(32);
	this->btnNew->setMaximumHeight(32);
	this->btnNew->setMinimumHeight(32);
	this->toolbarLayout->addWidget(this->btnNew);

	this->btnConnectDisconnect = new QPushButton(QIcon(":/images/connect.png"), tr(""), this->toolbarButtons);
	this->btnConnectDisconnect->setMaximumWidth(32);
	this->btnConnectDisconnect->setMinimumWidth(32);
	this->btnConnectDisconnect->setMaximumHeight(32);
	this->btnConnectDisconnect->setMinimumHeight(32);
	this->toolbarLayout->addWidget(this->btnConnectDisconnect);

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

	// We add the controls to the vertical layout
	layout->addWidget(this->toolbarButtons);
	layout->addWidget(this->mainBuffer);
	layout->addWidget(this->inputBuffer);

	// The QMdiSubWindow class has this setWidget() function
	// which allows us to simply set the main widget for the window.
	// Basically, we can add anything we want to the generic widget,
	// and the QMdiSubWindow won't care.
	this->setWidget(this->internalWidget);

	// Connect any signals/slots we want
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
	connect(this->btnNew, SIGNAL(released()), this, SLOT(newButtonClicked()));
	connect(this->btnConnectDisconnect, SIGNAL(released()), this, SLOT(connectDisconnectButtonClicked()));
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
