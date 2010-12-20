#ifndef OPENIRC_CHANNELWINDOW_H
#define OPENIRC_CHANNELWINDOW_H

#include <QtGui>

#include "mdiwindow.h"
#include "ircclient.h"

class ChannelWindow : public MdiWindow
{
	Q_OBJECT

  public:
  	ChannelWindow(QWidget *parent = 0);

	void append(const QString &string);
	MdiWindow::WindowType windowType();

	QString channel();
	void setChannel(const QString &channel);

	void closeEvent(QCloseEvent *event);

  public slots:
	void inputBufferReturnPressed();
	
  private:
	QHBoxLayout *chatLayout;
  	QVBoxLayout *mainLayout;

	QWidget *chatContainer;

	QStringList *Buffer;
  	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;
	QListView *nickList;
	QSplitter *chatSplitter;

	QAction *channelInfoAction;
	QAction *channelStatsAction;
	QAction *cycleChannelAction;

	QString Channel;
};

#endif
