#include "channelwindow.h"


ChannelWindow::ChannelWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
}

void ChannelWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void ChannelWindow::inputBufferReturnPressed()
{
	// TODO: Do something with this.
}
