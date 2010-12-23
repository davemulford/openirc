#include "querywindow.h"
#include "cctohtml.h"
#include <QSize>

QueryWindow::QueryWindow(QWidget *parent)
  : MdiWindow(parent)
{
	this->Buffer = new QStringList;
	this->setWindowIcon(QIcon(":/images/query.png"));
	this->toolbar->setStyleSheet("QToolBar { border: 0px }");
	this->setGeometry(0,0,320,240);

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

void QueryWindow::append(int color, const QString &string)
{
	CCtoHTML *str;
	str = new CCtoHTML;
	QString AddLine = str->TimeStamp() + " " + string;
	if (this->Buffer->size() >= 500) { 
		this->Buffer->pop_front();
		//this->chatBuffer->setText(this->Buffer->join("\n"));
		QTextCursor tc = this->chatBuffer->textCursor();
		tc.movePosition(QTextCursor::Start);
		tc.movePosition(QTextCursor::NextBlock,QTextCursor::KeepAnchor);
		tc.removeSelectedText();
	}
	this->Buffer->push_back("<div style=\"color: " + QString::fromStdString(str->ColorChart[color]) + "; white-space: pre-wrap\">" + QString::fromLocal8Bit(str->translate(AddLine.toStdString()).c_str()) + "</div>");
	this->chatBuffer->append(this->Buffer->last());
	delete str;
}

void QueryWindow::appendInput(const QString &text)
{
	inputBuffer->setText(inputBuffer->text() + text);
}

MdiWindow::WindowType QueryWindow::windowType()
{
	return(MdiWindow::QueryWindow);
}

void QueryWindow::scrollToBottom()
{
	QScrollBar *sb = this->chatBuffer->verticalScrollBar();
	if (sb->value() != sb->maximum()) { sb->setValue(sb->maximum()); }
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
		this->append(1,Qt::escape("9<" + QString::fromStdString(this->client()->Me) + "9> " + msg));
	}

	this->inputBuffer->clear();
}
