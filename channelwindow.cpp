#include "channelwindow.h"

ChannelWindow::ChannelWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	// Create our main internal widget
	this->internalWidget = new QWidget(this);

	// Create our layouts and container widgets
	this->chatContainer = new QWidget(this->internalWidget);
	this->chatLayout = new QHBoxLayout(this->chatContainer);
	this->mainLayout = new QVBoxLayout(this->internalWidget);

	// Create the toolbar
	this->toolbar = new QToolBar(this);
	this->toolbar->addAction(new QAction(QIcon(":/images/info.png"), tr(""), this->toolbar));
	this->toolbar->addAction(new QAction(QIcon(":/images/chanstats.png"), tr(""), this->toolbar));
	this->toolbar->addAction(new QAction(QIcon(":/images/reload.png"), tr(""), this->toolbar));

	// Create the chat section
	this->chatBuffer = new QTextEdit(this->chatContainer);
	this->nickList = new QListView(this->chatContainer);

	this->nickList->setMaximumWidth(100);

	this->chatLayout->addWidget(this->chatBuffer);
	this->chatLayout->addWidget(this->nickList);

	this->inputBuffer = new QLineEdit(this->internalWidget);

	// Add the main widgets to mainLayout
	this->mainLayout->addWidget(this->toolbar);
	this->mainLayout->addWidget(this->chatContainer);
	this->mainLayout->addWidget(this->inputBuffer);

	// Set some properties of mainLayout
	this->chatLayout->setSpacing(0);
	this->chatLayout->setContentsMargins(0,0,0,0);

	this->mainLayout->setSpacing(0);
	this->mainLayout->setContentsMargins(0,0,0,0);

	this->setWidget(this->internalWidget);
}

void ChannelWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void ChannelWindow::inputBufferReturnPressed()
{
	// TODO: Do something with this.
}
