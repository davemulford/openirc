#ifndef OPENIRC_QUERYWINDOW_H
#define OPENIRC_QUERYWINDOW_H

#include <QtGui>
#include "ircclient.h"

class QueryWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	QueryWindow(IRCClient *client, const QString &otherNick, QWidget *parent = 0);
	void setTitle(const QString &title);
	void appendBuffer(const QString &string);

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

	IRCClient *client;
	QString otherNick;
};

#endif
