#ifndef OPENIRC_WINDOWTREEITEM_H
#define OPENIRC_WINDOWTREEITEM_H

#include <QtGui>

class WindowTreeItem : public QStandardItem
{
  public:
  	WindowTreeItem(QWidget *parent = 0);

  private:
  	unsigned int cid;
	QMdiSubWindow *window;
};

#endif
