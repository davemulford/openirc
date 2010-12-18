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
}

void WindowTree::addChannelWindow(const unsigned int cid, const QString &name, MdiWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *channelItem = new WindowTreeItem(networkItem, cid, window);

		channelItem->setIcon(0, QIcon(":images/channel.png"));
		channelItem->setText(0, name);
	}
}

void WindowTree::addQueryWindow(const unsigned int cid, const QString &name, MdiWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *queryItem = new WindowTreeItem(networkItem, cid, window);

		queryItem->setIcon(0, QIcon(":images/query.png"));
		queryItem->setText(0, name);
	}
}

void WindowTree::removeItem(const unsigned int cid, const QString hashName)
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

void WindowTree::itemClicked(QTreeWidgetItem *item, int column)
{
	WindowTreeItem *treeItem = (WindowTreeItem *)item;

	treeItem->window()->show();
	emit windowItemClicked(treeItem->window());
}
