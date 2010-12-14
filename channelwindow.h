#ifndef OPENIRC_CHANNELWINDOW_H
#define OPENIRC_CHANNELWINDOW_H

#include <QtGui>

class ChannelWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	ChannelWindow(QWidget *parent);
	void setTitle(const QString &title);

  public slots:
	void inputBufferReturnPressed();
	
  private:
  	QTextEdit *mainBuffer;
	QLineEdit *inputBuffer;
	QListView *nickList;
};

#endif
