#ifndef OPENIRC_CHANNELWINDOW_H
#define OPENIRC_CHANNELWINDOW_H

#include <QtGui>
#include "ircclient.h"

class ChannelWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	ChannelWindow(IRCClient *client, const QString &channel, QWidget *parent = 0);
	void setTitle(const QString &title);
	void appendBuffer(const QString &string);

  public slots:
	void inputBufferReturnPressed();
	
  private:
	QHBoxLayout *chatLayout;
  	QVBoxLayout *mainLayout;

	QWidget *chatContainer;
	QWidget *internalWidget;

  	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;
	QListView *nickList;
	QSplitter *chatSplitter;

	QToolBar *toolbar;
	QAction *channelInfoAction;
	QAction *channelStatsAction;
	QAction *cycleChannelAction;

	IRCClient *client;
	QString channel;
};

#endif
