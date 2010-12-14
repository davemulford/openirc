#pragma once
#ifndef OPENIRC_CONTAINER_H
#define OPENIRC_CONTAINER_H

#include <QtGui>
#include "contextbar.h"

class Container : public QMainWindow
{
	Q_OBJECT

	public:
		Container(QWidget *parent = 0, Qt::WindowFlags flags = 0);

		void newWindow(void);

		/*newQueryWindow();
		  newStatusWindow();
		  newChannelWindow();*/

		/*protected:
		  void closeEvent(QCloseEvent *event);*/

	private:
		QMdiArea *mdiArea;
		ContextBar *contextBar;
		QStatusBar *statusbar;
		QToolBar *toolbar;

		QAction *MainAction;

};

#endif
