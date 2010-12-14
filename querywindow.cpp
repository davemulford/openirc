#include "querywindow.h"

QueryWindow::QueryWindow(QWidget *parent)
  : QMdiSubWindow(parent)
{
	// Set the minimum size of the query window
	this->setMinimumSize(250, 250);

	// Create internalWidget
	this->internalWidget = new QWidget(this);

	// Create the layout
	this->layout = new QVBoxLayout(this->internalWidget);
	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	// Create the toolbar
	this->toolbar = new QToolBar(this->internalWidget);

	this->whoisAction = new QAction(QIcon(":/images/whois.png"), tr(""), this->toolbar);
	this->whoisAction->setToolTip(tr("Whois"));
	this->toolbar->addAction(this->whoisAction);

	this->toolbar->addSeparator();

	this->ctcpPingAction = new QAction(QIcon(":/images/ctcp_ping.png"), tr(""), this->toolbar);
	this->ctcpPingAction->setToolTip(tr("Ping"));
	this->toolbar->addAction(this->ctcpPingAction);

	this->ctcpVersionAction = new QAction(QIcon(":/images/ctcp_version.png"), tr(""), this->toolbar);
	this->ctcpVersionAction->setToolTip(tr("Version"));
	this->toolbar->addAction(this->ctcpVersionAction);

	this->toolbar->addSeparator();

	this->dccChatAction = new QAction(QIcon(":/images/dcc_chat.png"), tr(""), this->toolbar);
	this->dccChatAction->setToolTip(tr("DCC Chat"));
	this->toolbar->addAction(this->dccChatAction);

	this->dccSendAction = new QAction(QIcon(":/images/dcc_send.png"), tr(""), this->toolbar);
	this->dccSendAction->setToolTip(tr("DCC Send"));
	this->toolbar->addAction(this->dccSendAction);

	this->toolbar->addSeparator();

	this->addNotifyAction = new QAction(QIcon(":/images/add_notify.png"), tr(""), this->toolbar);
	this->addNotifyAction->setToolTip(tr("Add To Notify"));
	this->toolbar->addAction(this->addNotifyAction);

	// Create the text and line edit controls
	this->chatBuffer = new QTextEdit(this->internalWidget);
	this->inputBuffer = new QLineEdit(this->internalWidget);

	// Add the controls to the layout
	this->layout->addWidget(this->toolbar);
	this->layout->addWidget(this->chatBuffer);
	this->layout->addWidget(this->inputBuffer);

	// Set the widget of the window to internalWidget
	this->setWidget(this->internalWidget);
}

void QueryWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void QueryWindow::inputBufferReturnPressed()
{
}
