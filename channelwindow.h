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
	QHBoxLayout *chatLayout;
  	QVBoxLayout *mainLayout;
	QHBoxLayout *toolbarLayout;

	QWidget *chatContainer;
	QWidget *internalWidget;
	QWidget *toolbarContainer;

  	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;
	QListView *nickList;
};

#endif
