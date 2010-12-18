#include "channelwindow.h"
#include "cctohtml.h"

ChannelWindow::ChannelWindow(QWidget *parent)
  : MdiWindow(parent)
{
	// Create our layouts and container widgets
	this->chatContainer = new QWidget(this->internalWidget);
	this->chatLayout = new QHBoxLayout(this->chatContainer);

	this->channelInfoAction = new QAction(QIcon(":/images/info.png"), tr(""), this->toolbar);
	this->channelInfoAction->setToolTip(tr("Channel Info"));
	this->toolbar->addAction(this->channelInfoAction);

	this->channelStatsAction = new QAction(QIcon(":/images/chanstats.png"), tr(""), this->toolbar);
	this->channelStatsAction->setToolTip(tr("Channel Stats"));
	this->toolbar->addAction(this->channelStatsAction);

	this->cycleChannelAction = new QAction(QIcon(":/images/reload.png"), tr(""), this->toolbar);
	this->cycleChannelAction->setToolTip(tr("Cycle Channel"));
	this->toolbar->addAction(this->cycleChannelAction);

	// Create the chat section
	this->chatBuffer = new QTextEdit(this->chatContainer);
	this->nickList = new QListView(this->chatContainer);

	this->chatBuffer->setReadOnly(true);
	this->nickList->setMaximumWidth(350);
	this->nickList->setMinimumWidth(120);

	this->chatSplitter = new QSplitter(this->chatContainer);
	this->chatSplitter->addWidget(this->chatBuffer);
	this->chatSplitter->addWidget(this->nickList);

	QList<int> splitterSizes;

	splitterSizes << 300 << 100;
	this->chatSplitter->setSizes(splitterSizes);

	this->chatLayout->addWidget(this->chatSplitter);

	this->inputBuffer = new QLineEdit(this->internalWidget);

	// Add the main widgets to layout
	this->layout->addWidget(this->chatContainer);
	this->layout->addWidget(this->inputBuffer);

	// Set some properties of mainLayout
	this->chatLayout->setSpacing(0);
	this->chatLayout->setContentsMargins(0,0,0,0);

	// Connect signals to slots
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void ChannelWindow::append(const QString &string)
{
	this->chatBuffer->append(string);
}

MdiWindow::WindowType ChannelWindow::windowType()
{
	return(MdiWindow::ChannelWindow);
}

QString ChannelWindow::channel()
{
	return(this->Channel);
}

void ChannelWindow::setChannel(const QString &channel)
{
	this->Channel = channel;
}

void ChannelWindow::inputBufferReturnPressed()
{
	QString msg = this->inputBuffer->text();

	if (!msg.startsWith("/")) {
		// TODO: Use the IRCCommandParser to check for any commands
		this->client()->sendRawMessage("PRIVMSG " + this->Channel + " :" + msg);

		QString AddLine = Qt::escape("9<" + QString::fromStdString(this->client()->Me) + "9> " + msg);
		CCtoHTML str(AddLine.toStdString());

		this->append(QString::fromStdString(str.translate()));
	}

	this->inputBuffer->clear();
}

void ChannelWindow::closeEvent(QCloseEvent *event)
{
	qDebug() << "ChannelWindow::closeEvent() -- Attempting to close a channel window" << endl;

	if (this->client()->state() == QAbstractSocket::ConnectedState) {
		qDebug() << "ChannelWindow::closeEvent() -- Attempt to gracefully PART from " << this->channel() << endl;
		this->client()->sendRawMessage("PART " + this->channel());
	}

	MdiWindow::closeEvent(event);
}
