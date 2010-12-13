#ifndef OPENIRC_WINDOW_H
#define OPENIRC_WINDOW_H

#include <QtGui>

class Window : public QMdiSubWindow
{
  public:
  	Window(QWidget *parent = 0);

	void setTitle(const QString &title);

  private:
  	QString title;
	QTextEdit *mainBuffer;
};

#endif
