#include "windowtree.h"

WindowTree::WindowTree(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
	this->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* titleWidget = new QWidget(this);
	this->setTitleBarWidget(titleWidget);

	this->containerWidget = new QWidget(this);
	QStringList labels;
	labels << "IRC Servers";
	this->tree = new QTreeWidget();
	this->tree->setHeaderLabels(labels);
	this->tree->setColumnCount(1);

	connect(this->tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemClicked(QTreeWidgetItem *, int)));

	this->layout = new QVBoxLayout(this->containerWidget);

	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	this->layout->addWidget(this->tree);
	this->setWidget(this->containerWidget);
}

WindowTreeItem *WindowTree::findItem(const int cid, const QString &hashName)
{
	//qDebug() << "WindowTree::findItem() called on cid=" << cid << " hashName=" << hashName << endl;

	if (this->rootItems.contains(cid)) {
		WindowTreeItem *topLevelItem = this->rootItems[cid];

		// Are we looking for the top-level window?
		if (topLevelItem->window()->hashName() == hashName) {
			return(topLevelItem);
		} else {
			int i, childCount = topLevelItem->childCount();
			
			for (i = 0; i < childCount; i++) {
				WindowTreeItem *child = (WindowTreeItem *)topLevelItem->child(i);

				if (child->window()->hashName() == hashName) {
					return(child);
				}
			}
		}
	}
	return(0);
}

void WindowTree::addStatusWindow(const unsigned int cid, const QString &name, MdiWindow *window)
{
	// Add status window gets added as a root-level item,
	// so its parent MUST be set to the tree
	WindowTreeItem *item = new WindowTreeItem(this->tree, cid, window);

	item->setIcon(0, QIcon(":images/servers.png"));
	this->rootItems.insert(cid, item);

	if (name.isEmpty() || name.isNull()) {
		item->setText(0, tr("Unnamed Network"));
	} else {
		item->setText(0, name);
	}
	item->setExpanded(true);
}

void WindowTree::addChannelWindow(const unsigned int cid, const QString &name, MdiWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *channelItem = new WindowTreeItem(networkItem, cid, window);

		qDebug() << "ChannelWindow(" << window << ") has parent(" << window->parent() << ")" << endl;

		channelItem->setIcon(0, QIcon(":images/channel.png"));
		channelItem->setText(0, name);
		networkItem->sortChildren(0,Qt::AscendingOrder);
	}
}

void WindowTree::addQueryWindow(const unsigned int cid, const QString &name, MdiWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *queryItem = new WindowTreeItem(networkItem, cid, window);

		queryItem->setIcon(0, QIcon(":images/query.png"));
		queryItem->setText(0, name);
		networkItem->sortChildren(0,Qt::AscendingOrder);
	}
}

void WindowTree::removeItem(const unsigned int cid, const QString &hashName)
{
	if (this->rootItems.contains(cid)) {

		// Get the root item, we'll go after its children then ;)
		WindowTreeItem *root = this->rootItems[cid];
		int childCount = root->childCount();

		// Are we removing a status window?
		if (root->window()->hashName() == hashName) {
			int rootIndex = this->tree->indexOfTopLevelItem(root);
			WindowTreeItem *removedRoot = (WindowTreeItem *)this->tree->takeTopLevelItem(rootIndex);

			// TODO: Go through and attempt to close all child windows

			this->rootItems.remove(cid);
			delete removedRoot;


		} else {
			for (int i = 0; i < childCount; i++) {
				WindowTreeItem *child = (WindowTreeItem *)root->child(i);

				if (child->window()->hashName() == hashName) {
					root->removeChild(child);

					delete child;
					break;
				}
			}
		}
	}
}

void WindowTree::renameItem(const unsigned int cid, const QString &hashName, const QString &newName)
{
	if (this->rootItems.contains(cid)) {

		// Get the root item, then find all child items
		WindowTreeItem *root = this->rootItems[cid];
		
		// Are we changing the name of the root item?
		if (root->window()->hashName() == hashName) {
			root->setText(0, newName);
		} else {
			int i, childCount = root->childCount();

			for (i = 0; i < childCount; i++) {
				WindowTreeItem *child = (WindowTreeItem *)root->child(i);

				if (child->window()->hashName() == hashName) {
					child->setText(0, newName);
				}
			}
		}
	}
}

void WindowTree::maybeHighlightItem(const unsigned int cid, const QString &hashName, QMdiSubWindow *activeSubWindow, QString const &color)
{
	WindowTreeItem *itemToHighlight = 0;

	if ((itemToHighlight = this->findItem(cid, hashName)) != 0) {

		/* If the application doesn't have focus, activeSubWindow will be 0x0.
			If it has focus, we'll get a proper window pointer. */
		if (activeSubWindow != itemToHighlight->window()) {
			itemToHighlight->setForeground(0, QBrush(QColor(color)));
		}
	}
}

void WindowTree::itemClicked(QTreeWidgetItem *item, int column)
{
	WindowTreeItem *treeItem = (WindowTreeItem *)item;

	// Unhighlight the item (just in case it was highlighted)
	treeItem->setForeground(0, QBrush(QColor("#000000")));

	treeItem->window()->show();
	//((QMdiArea *)treeItem->window()->parent())->setActiveSubWindow(treeItem->window());
	emit windowItemClicked(treeItem->window());
}
