#include "windowtree.h"

WindowTree::WindowTree(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
	this->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* titleWidget = new QWidget(this);
	this->setTitleBarWidget(titleWidget);

	this->containerWidget = new QWidget(this);

	this->tree = new QTreeWidget();
	this->tree->setColumnCount(1);

	connect(this->tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemClicked(QTreeWidgetItem *, int)));

	this->layout = new QVBoxLayout(this->containerWidget);

	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	this->layout->addWidget(this->tree);
	this->setWidget(this->containerWidget);
}

void WindowTree::addStatusWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window)
{
	// Add status window gets added as a root-level item,
	// so its parent MUST be set to the tree
	WindowTreeItem *item = new WindowTreeItem(this->tree, cid, window);
	this->rootItems.insert(cid, item);

	if (name.isEmpty() || name.isNull()) {
		item->setText(0, tr("Unnamed Network"));
	} else {
		item->setText(0, name);
	}
}

void WindowTree::addChannelWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *channelItem = new WindowTreeItem(networkItem, cid, window);

		channelItem->setText(0, name);
	}
}

void WindowTree::addQueryWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window)
{
	if (this->rootItems.contains(cid)) {
		WindowTreeItem *networkItem = this->rootItems[cid];
		WindowTreeItem *queryItem = new WindowTreeItem(networkItem, cid, window);

		queryItem->setText(0, name);
	}
}

void WindowTree::createMockItems(void)
{
	QTreeWidgetItem *cities = new QTreeWidgetItem(this->tree);
	cities->setText(0, tr("Cities"));

	QTreeWidgetItem *planets = new QTreeWidgetItem(this->tree, cities);
	planets->setText(0, tr("Planets"));

	QTreeWidgetItem *osloItem = new QTreeWidgetItem(cities);
	osloItem->setText(0, tr("Oslo"));
}

void WindowTree::itemClicked(QTreeWidgetItem *item, int column)
{
	WindowTreeItem *treeItem = (WindowTreeItem *)item;

	//qDebug() << "Attempting to activate and raise a subwindow" << endl;

	emit windowItemClicked(treeItem->window());

	//treeItem->window()->activateWindow();
	//treeItem->window()->raise();
	treeItem->window()->show();
}
