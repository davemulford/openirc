#include "channelwindow.h"
#include "cctohtml.h"

ChannelWindow::ChannelWindow(QWidget *parent)
  : MdiWindow(parent)
{
	this->Buffer = new QStringList;
	this->setWindowIcon(QIcon(":/images/channel.png"));
	this->toolbar->setStyleSheet("QToolBar { border: 0px }");
	this->setGeometry(-1,-1,400,240);

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
	//this->chatBuffer->setStyleSheet("QToolBar { border: 0px }");
	this->nickList->setMaximumWidth(350);
	this->nickList->setMinimumWidth(120);

	this->chatSplitter = new QSplitter(this->chatContainer);
	this->chatSplitter->addWidget(this->chatBuffer);
	this->chatSplitter->addWidget(this->nickList);

	QList<int> splitterSizes;

	splitterSizes << 400 << 100;
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
	this->Buffer->push_back("<div style=\"white-space: pre-wrap\">" + string + "</div>");
	if (this->Buffer->size() > 500) { this->Buffer->pop_front(); }
	this->chatBuffer->setText(this->Buffer->join("\n"));

	QScrollBar *sb = this->chatBuffer->verticalScrollBar();
	sb->setValue(sb->maximum() + 1);
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
