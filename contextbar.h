#ifndef OPENIRC_CONTEXTBAR_H
#define OPENIRC_CONTEXTBAR_H

#include <QtGui>

class ContextBar : public QDockWidget
{
	Q_OBJECT

  public:
  	ContextBar(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  Q_SIGNALS:
  	void optionsClicked();

	void tileHorizontalClicked();
	void tileVerticalClicked();
	void tileCascadeClicked();

	void previousWindowClicked();
	void nextWindowClicked();
	void homeClicked();

	void btnSearchClicked();

  public slots:
  	void optionsActionTriggered(bool checked = false);

	void tileHorizontalActionTriggered(bool checked = false);
	void tileVerticalActionTriggered(bool checked = false);
	void tileCascadeActionTriggered(bool checked = false);

	void previousWindowActionTriggered(bool checked = false);
	void nextWindowActionTriggered(bool checked = false);
	void homeActionTriggered(bool checked = false);

  private:
  	QHBoxLayout *layout;
	QWidget *internalWidget;

  	QToolBar *toolbar;
	QAction *optionsAction;
	QAction *tileHorizontalAction;
	QAction *tileVerticalAction;
	QAction *tileCascadeAction;
	QAction *previousWindowAction;
	QAction *nextWindowAction;
	QAction *homeAction;

	QPushButton *btnSearch;
	QLineEdit *searchBuffer;
};

#endif
