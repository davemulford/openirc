#ifndef OPENIRC_QUERYWINDOW_H
#define OPENIRC_QUERYWINDOW_H

#include <QtGui>

class QueryWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	QueryWindow(QWidget *parent = 0);
	void setTitle(const QString &title);

  public slots:
  	void inputBufferReturnPressed();

  private:
	QWidget *internalWidget;
	QVBoxLayout *layout;
	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;

  	QToolBar *toolbar;
	QAction *whoisAction;
	QAction *ctcpPingAction;
	QAction *ctcpVersionAction;
	QAction *dccChatAction;
	QAction *dccSendAction;
	QAction *addNotifyAction;
};

#endif
