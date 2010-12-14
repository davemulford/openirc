#ifndef OPENIRC_STATUSWINDOW_H
#define OPENIRC_STATUSWINDOW_H

#include <QtGui>
#include "ircclient.h"

class StatusWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	StatusWindow(QWidget *parent = 0);
	void setTitle(const QString &title);

	IRCClient *client();
	void setClient(IRCClient *);

	void appendToMainBuffer(const QString &);

  public slots:
	void inputBufferReturnPressed();
	void newButtonClicked();
	void connectDisconnectButtonClicked();

  private:
	QWidget *internalWidget;
	QVBoxLayout *layout;

	QTextEdit *mainBuffer;
	QLineEdit *inputBuffer;

	QToolBar *toolbar;
	QAction *newConnectionAction;
	QAction *connectDisconnectAction;

	IRCClient *_client;
};

#endif
