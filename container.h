#pragma once
#ifndef OPENIRC_CONTAINER_H
#define OPENIRC_CONTAINER_H

#include <QtGui>

class Container : public QMainWindow
{
	Q_OBJECT
  
  public:
  	Container();

	void newWindow(void);

	/*newQueryWindow();
	newStatusWindow();
	newChannelWindow();*/

  /*protected:
     void closeEvent(QCloseEvent *event);*/

  private:
  	QMdiArea *mdiArea;
};

#endif
