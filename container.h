#ifndef OPENIRC_CONTAINER_H
#define OPENIRC_CONTAINER_H

#include <QtGui>
#include "statuswindow.h"

// Container Class Definition {{{

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

// Container Class Definition }}}

// Container Implementation {{{

Container::Container()
{
	this->mdiArea = new QMdiArea(this);
	setCentralWidget(this->mdiArea);
	//this->mdiArea->setActivationOrder(WindowOrder::CreationOrder );

	this->newWindow();
}

void Container::newWindow()
{
	Window *window = new Window(this->mdiArea);
	window->setTitle("Not Connected");
}

// Container Implementation }}}

#endif
