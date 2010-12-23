#ifndef OPENIRC_STATUSWINDOW_H
#define OPENIRC_STATUSWINDOW_H

#include <QtGui>

#include "mdiwindow.h"
#include "ircclient.h"

class StatusWindow : public MdiWindow
{
	Q_OBJECT

  public:
  	StatusWindow(QWidget *parent = 0, CommandParser *parser = 0);

	void append(int color, const QString &string);
	void appendInput(const QString &text);
	MdiWindow::WindowType windowType();
	void scrollToBottom();

	void closeEvent(QCloseEvent *event);

  Q_SIGNALS:
	void newStatusWin();

  public slots:
	void inputBufferReturnPressed();
	void newButtonClicked(bool checked);
	void connectDisconnectButtonClicked(bool checked);

  private:
	QStringList *Buffer;
	QTextEdit *chatBuffer;
	QLineEdit *inputBuffer;

	// Action which will be added to the toolbar
	QAction *newConnectionAction;
	QAction *connectDisconnectAction;
};

#endif
