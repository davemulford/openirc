#include "contextbar.h"


ContextBar::ContextBar(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
	this->setFeatures(QDockWidget::NoDockWidgetFeatures);

	// Create the horizontal layout
	this->internalWidget = new QWidget(this);
	this->layout = new QHBoxLayout(this->internalWidget);

	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	// Create the toolbar
	this->toolbar = new QToolBar(this);

	this->previousWindowAction = new QAction(QIcon(":/images/leftarrow.png"), tr(""), this->toolbar);
	this->toolbar->addAction(this->previousWindowAction);

	this->nextWindowAction = new QAction(QIcon(":/images/rightarrow.png"), tr(""), this->toolbar);
	this->toolbar->addAction(this->nextWindowAction);

	this->homeAction = new QAction(QIcon(":/images/home.png"), tr(""), this->toolbar);
	this->toolbar->addAction(this->homeAction);

	// Create the line edit button
	this->buffer = new QLineEdit(this);

	this->layout->addWidget(this->toolbar);
	this->layout->addWidget(this->buffer);

	this->setWidget(this->internalWidget);
}
