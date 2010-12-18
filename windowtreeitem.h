#ifndef OPENIRC_WINDOWTREEITEM_H
#define OPENIRC_WINDOWTREEITEM_H

#include <QtGui>

#include "mdiwindow.h"

class WindowTreeItem : public QTreeWidgetItem
{
  public:
	WindowTreeItem(QTreeWidget *parent = 0, const unsigned int cid = 0, MdiWindow *window = 0);
  	WindowTreeItem(WindowTreeItem *parent = 0, const unsigned int cid = 0, MdiWindow *window = 0);

	int cid();
	MdiWindow *window();

  private:
  	unsigned int Cid;
	MdiWindow *Window;
};

#endif
