#include "windowtreeitem.h"

WindowTreeItem::WindowTreeItem(QTreeWidget *parent, const unsigned int cid, QMdiSubWindow *window)
  : QTreeWidgetItem(parent, 0)
{
	this->cid = cid;
	this->_window = window;
}

WindowTreeItem::WindowTreeItem(WindowTreeItem *parent, const unsigned int cid, QMdiSubWindow *window)
  : QTreeWidgetItem(parent, 0)
{
	this->cid = cid;
	this->_window = window;
}

QMdiSubWindow *WindowTreeItem::window()
{
	return(this->_window);
}
