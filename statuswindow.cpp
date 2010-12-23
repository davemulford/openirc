#include "statuswindow.h"
#include "irccommandparser.h"
#include "cctohtml.h"
#include <iostream>
using namespace std;

StatusWindow::StatusWindow(QWidget *parent)
  : MdiWindow(parent) 
{
	this->Buffer = new QStringList;
	this->toolbar->setStyleSheet("QToolBar { border: 0px }");
	this->setGeometry(0,0,320,240);

	// Create the widgets that the window will hold.
	this->chatBuffer = new QTextEdit(this);
	this->chatBuffer->setReadOnly(true);

	this->inputBuffer = new QLineEdit(this);

	this->newConnectionAction = new QAction(QIcon(":/images/new_connection.png"), tr(""), this->toolbar);
	this->newConnectionAction->setToolTip(tr("New Connection"));
	this->toolbar->addAction(this->newConnectionAction);

	this->connectDisconnectAction = new QAction(QIcon(":/images/connect.png"), tr(""), this->toolbar);
	this->connectDisconnectAction->setToolTip(tr("Connect"));
	this->toolbar->addAction(this->connectDisconnectAction);

	// We add the controls to the vertical layout
	layout->addWidget(this->chatBuffer);
	layout->addWidget(this->inputBuffer);

	// Connect any signals/slots we want
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
	connect(this->newConnectionAction, SIGNAL(triggered(bool)), this, SLOT(newButtonClicked(bool)));
	connect(this->connectDisconnectAction, SIGNAL(triggered(bool)), this, SLOT(connectDisconnectButtonClicked(bool)));
}

void StatusWindow::append(int color, const QString &string)
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

MdiWindow::WindowType StatusWindow::windowType()
{
	return(MdiWindow::StatusWindow);
}

void StatusWindow::scrollToBottom()
{
	QScrollBar *sb = this->chatBuffer->verticalScrollBar();
	if (sb->value() != sb->maximum()) { sb->setValue(sb->maximum()); }
}

void StatusWindow::inputBufferReturnPressed()
{
	QString inputText = this->inputBuffer->text();

	IRCCommandParser *parser = new IRCCommandParser(inputText);

	if ((parser->type() == IRCCommandParser::OfflineCommand) && (parser->command() == "SERVER")) {
		QStringList serverArgs = parser->argList();

		if (serverArgs.isEmpty()) {
			this->append(1,tr("!!! /server: two arguments possible: host (required), port (optional)"));
		} else {
			QString host = serverArgs.at(0);
			int port = (serverArgs.count() > 1 ? (serverArgs.at(1).toInt()) : 6667);
			this->append(1,tr("--- Connecting to server..."));
			this->client()->connectToHost(host, port);
		}
	} else if (parser->type() == IRCCommandParser::IRCMessage) {
		this->client()->sendRawMessage(parser->command());
	}

	// Clear the input buffer
	this->inputBuffer->clear();
}

void StatusWindow::newButtonClicked(bool checked) {
	emit newStatusWin();
}

void StatusWindow::connectDisconnectButtonClicked(bool checked)
{
	this->append(1,tr("*** Connect/Disconnect button clicked"));
}

void StatusWindow::closeEvent(QCloseEvent *event)
{
	if (this->client()->state() == QAbstractSocket::ConnectedState) {
		this->client()->sendRawMessage("QUIT :Leaving");
	}

	MdiWindow::closeEvent(event);
}
