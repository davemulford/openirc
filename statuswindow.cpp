#include "statuswindow.h"
#include "irccommandparser.h"

#include <iostream>
using namespace std;

StatusWindow::StatusWindow(QWidget *parent)
  : MdiWindow(parent) 
{
	// Create the widgets that the window will hold.
	this->mainBuffer = new QTextEdit(this);
	this->mainBuffer->setReadOnly(true);

	this->inputBuffer = new QLineEdit(this);

	this->newConnectionAction = new QAction(QIcon(":/images/new_connection.png"), tr(""), this->toolbar);
	this->newConnectionAction->setToolTip(tr("New Connection"));
	this->toolbar->addAction(this->newConnectionAction);

	this->connectDisconnectAction = new QAction(QIcon(":/images/connect.png"), tr(""), this->toolbar);
	this->connectDisconnectAction->setToolTip(tr("Connect"));
	this->toolbar->addAction(this->connectDisconnectAction);

	// We add the controls to the vertical layout
	layout->addWidget(this->mainBuffer);
	layout->addWidget(this->inputBuffer);

	// Connect any signals/slots we want
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
	connect(this->newConnectionAction, SIGNAL(triggered(bool)), this, SLOT(newButtonClicked(bool)));
	connect(this->connectDisconnectAction, SIGNAL(triggered(bool)), this, SLOT(connectDisconnectButtonClicked(bool)));
}

void StatusWindow::append(const QString &string)
{
	this->mainBuffer->append(string);

	QScrollBar *sb = this->mainBuffer->verticalScrollBar();
	sb->setValue(sb->maximum());
}

MdiWindow::WindowType StatusWindow::windowType()
{
	return(MdiWindow::StatusWindow);
}

void StatusWindow::inputBufferReturnPressed()
{
	QString inputText = this->inputBuffer->text();

	IRCCommandParser *parser = new IRCCommandParser(inputText);

	if ((parser->type() == IRCCommandParser::OfflineCommand) && (parser->command() == "SERVER")) {
		QStringList serverArgs = parser->argList();

		if (serverArgs.isEmpty()) {
			this->mainBuffer->append(tr("!!! /server: two arguments possible: host (required), port (optional)"));
		} else {
			QString host = serverArgs.at(0);
			int port = (serverArgs.count() > 1 ? (serverArgs.at(1).toInt()) : 6667);
			this->append(tr("--- Connecting to server..."));
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
	this->append(tr("*** Connect/Disconnect button clicked"));
}

void StatusWindow::closeEvent(QCloseEvent *event)
{
	if (this->client()->state() == QAbstractSocket::ConnectedState) {
		this->client()->sendRawMessage("QUIT :Leaving");
	}

	MdiWindow::closeEvent(event);
}
