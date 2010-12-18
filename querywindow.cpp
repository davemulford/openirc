#include "querywindow.h"
#include "cctohtml.h"

QueryWindow::QueryWindow(QWidget *parent)
  : MdiWindow(parent)
{
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

	this->chatBuffer->setReadOnly(true);

	// Add the controls to the layout
	this->layout->addWidget(this->chatBuffer);
	this->layout->addWidget(this->inputBuffer);

	// Connect signals to slots
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void QueryWindow::append(const QString &string)
{
	this->chatBuffer->append(string);
}

MdiWindow::WindowType QueryWindow::windowType()
{
	return(MdiWindow::QueryWindow);
}

QString QueryWindow::otherNick()
{
	return(this->them);
}

void QueryWindow::setOtherNick(const QString &otherNick)
{
	this->them = otherNick;
}

void QueryWindow::inputBufferReturnPressed()
{
	QString msg = this->inputBuffer->text();

	if (!msg.startsWith("/")) {
		// TODO: Use the IRCCommandParser to check for any commands
		this->client()->sendRawMessage("PRIVMSG " + this->them + " :" + msg);

		QString AddLine = Qt::escape("9<" + QString::fromStdString(this->client()->Me) + "9> " + msg);
		CCtoHTML str(AddLine.toStdString());

		this->append(QString::fromStdString(str.translate()));
	}

	this->inputBuffer->clear();
}
