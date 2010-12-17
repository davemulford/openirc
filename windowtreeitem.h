#ifndef OPENIRC_WINDOWTREEITEM_H
#define OPENIRC_WINDOWTREEITEM_H

#include <QtGui>

class WindowTreeItem : public QTreeWidgetItem
{
  public:
	WindowTreeItem(QTreeWidget *parent = 0, const unsigned int cid = 0, QMdiSubWindow *window = 0);
  	WindowTreeItem(WindowTreeItem *parent = 0, const unsigned int cid = 0, QMdiSubWindow *window = 0);

	QMdiSubWindow *window();

  private:
  	unsigned int cid;
	QMdiSubWindow *_window;
};

#endif
