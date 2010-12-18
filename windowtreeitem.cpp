#include "windowtreeitem.h"

WindowTreeItem::WindowTreeItem(QTreeWidget *parent, const unsigned int cid, MdiWindow *window)
  : QTreeWidgetItem(parent, 0)
{
	this->Cid = cid;
	this->Window = window;
}

WindowTreeItem::WindowTreeItem(WindowTreeItem *parent, const unsigned int cid, MdiWindow *window)
  : QTreeWidgetItem(parent, 0)
{
	this->Cid = cid;
	this->Window = window;
}

int WindowTreeItem::cid()
{
	return(this->Cid);
}

MdiWindow *WindowTreeItem::window()
{
	return(this->Window);
}
