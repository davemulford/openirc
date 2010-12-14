#ifndef OPENIRC_CONTEXTBAR_H
#define OPENIRC_CONTEXTBAR_H

#include <QtGui>

class ContextBar : public QDockWidget
{
	Q_OBJECT

  public:
  	ContextBar(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  Q_SIGNALS:
	void previousWindowClicked();
	void nextWindowClicked();
	void homeClicked();

  private:
  	QHBoxLayout *layout;

  	QToolBar *toolbar;
	QAction *previousWindowAction;
	QAction *nextWindowAction;
	QAction *homeAction;

	QLineEdit *buffer;
};

#endif
