#include "windowtree.h"

WindowTree::WindowTree(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
	this->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* titleWidget = new QWidget(this);
	this->setTitleBarWidget(titleWidget);

	this->containerWidget = new QWidget(this);

	this->tree = new QTreeView();
	this->layout = new QVBoxLayout(this->containerWidget);

	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	this->layout->addWidget(this->tree);
	this->setWidget(this->containerWidget);
}

void WindowTree::createMockItems(void)
{
	// Create the model
	this->model = new QStandardItemModel(8, 1, this);
	this->model->setHeaderData(0, Qt::Horizontal, tr(""));
	//this->model->verticalHeader()->hide();
	//this->model->setHeaderData(1, Qt::Horizontal, tr(""));

	// Give the model to the tree
	this->tree->setModel(this->model);

	// Add some items to the tree
	int rowId = 0;
	this->model->insertRow(rowId);
	this->model->setData(this->model->index(rowId, 0, QModelIndex()), "ok1");

	rowId++;
	this->model->insertRow(1);
	this->model->setData(this->model->index(rowId, 0, QModelIndex()), "ok2");



}
