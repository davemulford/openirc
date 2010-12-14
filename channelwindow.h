#ifndef OPENIRC_CHANNELWINDOW_H
#define OPENIRC_CHANNELWINDOW_H

#include <QtGui>

class ChannelWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	ChannelWindow(QWidget *parent = 0);
	void setTitle(const QString &title);

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
};

#endif
