#include "querywindow.h"
#include "cctohtml.h"

QueryWindow::QueryWindow(IRCClient *client, const QString &otherNick, QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	this->setWindowIcon(QIcon(":/images/openirc.png"));
	// Set the minimum size of the query window
	this->setMinimumSize(250, 250);

	this->client = client;
	this->otherNick = otherNick;

	// Create internalWidget
	this->internalWidget = new QWidget(this);

	// Create the layout
	this->layout = new QVBoxLayout(this->internalWidget);
	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	// Create the toolbar
	this->toolbar = new QToolBar(this);

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
	this->layout->addWidget(this->toolbar);
	this->layout->addWidget(this->chatBuffer);
	this->layout->addWidget(this->inputBuffer);

	// Set the widget of the window to internalWidget
	this->setWidget(this->internalWidget);

	// Connect signals to slots
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void QueryWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void QueryWindow::appendBuffer(const QString &string)
{
	this->chatBuffer->append(string);
}

void QueryWindow::inputBufferReturnPressed()
{
	QString msg = this->inputBuffer->text();

	if (!msg.startsWith("/")) {
		// TODO: Use the IRCCommandParser to check for any commands
		this->client->sendRawMessage("PRIVMSG " + this->otherNick + " :" + msg);

		QString AddLine = Qt::escape("9<" + QString::fromStdString(this->client->Me) + "9> " + msg);
		CCtoHTML str(AddLine.toStdString());

		this->chatBuffer->append(QString::fromStdString(str.translate()));
	}

	this->inputBuffer->clear();
}
