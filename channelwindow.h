#ifndef OPENIRC_CHANNELWINDOW_H
#define OPENIRC_CHANNELWINDOW_H

#include <QtCore>
#include <QtGui>

#include "mdiwindow.h"
#include "ircclient.h"

class ChannelWindow : public MdiWindow
{
	Q_OBJECT

  public:
  	ChannelWindow(QWidget *parent = 0);

	void append(int color, const QString &string);
	MdiWindow::WindowType windowType();
	void scrollToBottom();

	QString channel();
	void setChannel(const QString &channel);

	void closeEvent(QCloseEvent *event);

	void addNick(const QString &nick);
	void removeNick(const QString &nick);
	void setPrefixes(const QString &prefixes);
	void setNickList(const QStringList &list, const QString &prefixes = "@+-");

  public slots:
	void inputBufferReturnPressed();
	
  private:
	QHBoxLayout *chatLayout;
  	QVBoxLayout *mainLayout;

	QStringList nickStringList;
	QStringListModel *nickListModel;

	QWidget *chatContainer;

	QStringList *Buffer;
  	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;
	QListView *nickList;
	QSplitter *chatSplitter;

	QAction *channelInfoAction;
	QAction *channelStatsAction;
	QAction *cycleChannelAction;

	QString prefixes;
	QString Channel;

	static bool nickListSort(const QString &a, const QString &b);
};

#endif
