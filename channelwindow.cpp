#include "channelwindow.h"
#include "cctohtml.h"

ChannelWindow::ChannelWindow(QWidget *parent)
  : MdiWindow(parent)
{
	this->Buffer = new QStringList;
	this->setWindowIcon(QIcon(":/images/channel.png"));
	this->toolbar->setStyleSheet("QToolBar { border: 0px }");
	this->setGeometry(0,0,420,240);

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
	this->nickListModel = new QStringListModel(this->nickList);
	this->nickList->setModel(this->nickListModel);

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

bool ChannelWindow::nickListSort(const QString &a, const QString &b)
{
	// Remove this later when we figure out a way 
	// to get access to the IRCClient class
	string classPrefixes = "@+-";

	QString prefixes = QString::fromStdString(classPrefixes);
	int i, prefixesCount = prefixes.length();

	QString localA = a;
	QString localB = b;

	// We simply replace the prefixes with characters starting at character 33 and moving up
	// We only do this locally, though :)
	int chr = 33;
	for (i = 0; i < prefixesCount; i++) {
		localA.replace(prefixes[i], QChar(chr), Qt::CaseInsensitive);
		localB.replace(prefixes[i], QChar(chr++), Qt::CaseInsensitive);
	}
	
	return(localA.toLower() < localB.toLower());
}

void ChannelWindow::append(int color, const QString &string)
{
	CCtoHTML *str;
	str = new CCtoHTML;
	QString AddLine = str->TimeStamp() + " " + string;
	if (this->Buffer->size() >= 500) { 
		this->Buffer->pop_front();
		this->chatBuffer->setText(this->Buffer->join("\n"));
		QTextCursor tc = this->chatBuffer->textCursor();
		tc.movePosition(QTextCursor::Start);
		tc.movePosition(QTextCursor::NextBlock,QTextCursor::KeepAnchor);
		tc.removeSelectedText();
	}
	this->Buffer->push_back("<div style=\"color: " + QString::fromStdString(str->ColorChart[color]) + "; white-space: pre-wrap\">" + QString::fromStdString(str->translate(AddLine.toStdString())) + "</div>");
	this->chatBuffer->append(this->Buffer->last());
	delete str;
}

MdiWindow::WindowType ChannelWindow::windowType()
{
	return(MdiWindow::ChannelWindow);
}

void ChannelWindow::scrollToBottom()
{
	QScrollBar *sb = this->chatBuffer->verticalScrollBar();
	if (sb->value() != sb->maximum()) { sb->setValue(sb->maximum()); }
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
		this->append(1, Qt::escape("9<" + QString::fromStdString(this->client()->Me) + "9> " + msg));
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

void ChannelWindow::addNick(const QString &nick)
{
	this->removeNick(nick);
	this->nickStringList << nick;

	//qSort(this->nickStringList.begin(), this->nickStringList.end(), ChannelWindow::nickListSort);
	this->nickListModel->setStringList(this->nickStringList);
}

void ChannelWindow::removeNick(const QString &nick)
{
	int index = this->nickStringList.indexOf(nick);

	if (index >= 0) {
		this->nickStringList.removeAt(index);
		this->nickListModel->setStringList(this->nickStringList);
	}
}

void ChannelWindow::setNickList(const QStringList &list)
{
	this->nickStringList = list;

	//qSort(this->nickStringList.begin(), this->nickStringList.end(), ChannelWindow::nickListSort);
	this->nickListModel->setStringList(this->nickStringList);
}
