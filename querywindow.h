#ifndef OPENIRC_QUERYWINDOW_H
#define OPENIRC_QUERYWINDOW_H

#include <QtGui>

#include "mdiwindow.h"
#include "ircclient.h"

class QueryWindow : public MdiWindow
{
	Q_OBJECT

  public:
  	QueryWindow(QWidget *parent = 0);

	void append(int color, const QString &string);
	void appendInput(const QString &text);
	MdiWindow::WindowType windowType();
	void scrollToBottom();

	QString otherNick();
	void setOtherNick(const QString &otherNick);

  public slots:
  	void inputBufferReturnPressed();

  private:
	QStringList *Buffer;
	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;

	QAction *whoisAction;
	QAction *ctcpPingAction;
	QAction *ctcpVersionAction;
	QAction *dccChatAction;
	QAction *dccSendAction;
	QAction *addNotifyAction;

	QString them;
};

#endif
