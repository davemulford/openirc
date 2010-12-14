#ifndef OPENIRC_STATUSWINDOW_H
#define OPENIRC_STATUSWINDOW_H

#include <QtGui>

class StatusWindow : public QMdiSubWindow
{
	Q_OBJECT

  public:
  	StatusWindow(QWidget *parent = 0);
	void setTitle(const QString &title);

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
};

#endif
