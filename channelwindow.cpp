#include "channelwindow.h"
#include "cctohtml.h"

ChannelWindow::ChannelWindow(IRCClient *client, const QString &channel, QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	this->setWindowIcon(QIcon(":/images/openirc.png"));
	this->client = client;
	this->channel = channel;

	// Create our main internal widget
	this->internalWidget = new QWidget(this);

	// Create our layouts and container widgets
	this->chatContainer = new QWidget(this->internalWidget);
	this->chatLayout = new QHBoxLayout(this->chatContainer);
	this->mainLayout = new QVBoxLayout(this->internalWidget);

	// Create the toolbar
	this->toolbar = new QToolBar(this);

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

	// Connect signals to slots
	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void ChannelWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}
void ChannelWindow::appendBuffer(const QString &string)
{
	this->chatBuffer->append(string);
}

void ChannelWindow::inputBufferReturnPressed()
{
	QString msg = this->inputBuffer->text();

	if (!msg.startsWith("/")) {
		// TODO: Use the IRCCommandParser to check for any commands
		this->client->sendRawMessage("PRIVMSG " + this->channel + " :" + msg);

		QString AddLine = Qt::escape("9<" + QString::fromStdString(this->client->Me) + "9> " + msg);
		CCtoHTML str(AddLine.toStdString());

		this->chatBuffer->append(QString::fromStdString(str.translate()));
	}

	this->inputBuffer->clear();
}
