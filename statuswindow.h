#ifndef OPENIRC_STATUSWINDOW_H
#define OPENIRC_STATUSWINDOW_H

#include <QtGui>

class Window : public QMdiSubWindow
{
	Q_OBJECT
  public:
  	Window(QWidget *parent = 0);
	void setTitle(const QString &title);

  public slots:
	void inputBufferReturnPressed();

  private:
	QWidget *internalWidget;
	QVBoxLayout *layout;
	QTextEdit *mainBuffer;
	QLineEdit *inputBuffer;
};

#endif
