#include "channelwindow.h"


ChannelWindow::ChannelWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	/*
	// Create our main internal widget
	this->internalWidget = new QWidget(this);

	// Create our layouts
	chatLayout = new QHboxLayout(this->internalWidget);
	mainLayout = new QVBoxLayout(this->internalWidget);
	toolbarLayout = new QHBoxLayout(this->internalWidget);
	*/
}

void ChannelWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void ChannelWindow::inputBufferReturnPressed()
{
	// TODO: Do something with this.
}
