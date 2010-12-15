#include "contextbar.h"

ContextBar::ContextBar(QWidget *parent, Qt::WindowFlags flags)
  : QDockWidget(parent, flags)
{
        //not sure if we wanna keep this but it makes the docked widget expandable with a slider
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
        this->setSizePolicy(sizePolicy);

        this->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetVerticalTitleBar);
        //make a blank qwidget for the dockwidget titlebar so the size is 0 instead of the nasty default
        QWidget* titleWidget = new QWidget(this);
        this->setTitleBarWidget(titleWidget);

	//this->setFixedHeight(50);

	// Create the horizontal layout
	this->internalWidget = new QWidget(this);
	this->layout = new QHBoxLayout(this->internalWidget);

	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	// Create the toolbar
	this->toolbar = new QToolBar(this);

	this->optionsAction = new QAction(QIcon(":/images/configure.png"), tr(""), this->toolbar);
	this->optionsAction->setToolTip(tr("Options"));
	this->toolbar->addAction(this->optionsAction);

	this->toolbar->addSeparator();

	this->tileHorizontalAction = new QAction(QIcon(":/images/tile_horizontal.png"), tr(""), this->toolbar);
	this->tileHorizontalAction->setToolTip(tr("Tile Horizontal"));
	this->toolbar->addAction(this->tileHorizontalAction);

	this->tileVerticalAction = new QAction(QIcon(":/images/tile_vertical.png"), tr(""), this->toolbar);
	this->tileVerticalAction->setToolTip(tr("Tile Vertical"));
	this->toolbar->addAction(this->tileVerticalAction);

	this->tileCascadeAction = new QAction(QIcon(":/images/tile_cascade.png"), tr(""), this->toolbar);
	this->tileCascadeAction->setToolTip(tr("Tile Cascade"));
	this->toolbar->addAction(this->tileCascadeAction);

	this->toolbar->addSeparator();

	this->previousWindowAction = new QAction(QIcon(":/images/leftarrow.png"), tr(""), this->toolbar);
	this->previousWindowAction->setToolTip(tr("Previous Window"));
	this->toolbar->addAction(this->previousWindowAction);

	this->nextWindowAction = new QAction(QIcon(":/images/rightarrow.png"), tr(""), this->toolbar);
	this->nextWindowAction->setToolTip(tr("Next Window"));
	this->toolbar->addAction(this->nextWindowAction);

	this->homeAction = new QAction(QIcon(":/images/home.png"), tr(""), this->toolbar);
	this->homeAction->setToolTip(tr("Show Home"));
	this->toolbar->addAction(this->homeAction);

	// Create the search button
	this->btnSearch = new QPushButton(QIcon(":/images/search.png"), tr(""), this);
	this->btnSearch->setFlat(true);
	this->btnSearch->setFixedWidth(32);

	// Create the line edit button
	this->searchBuffer = new QLineEdit(this);
	this->searchBuffer->setFixedWidth(180);

	this->layout->addWidget(this->toolbar);
	this->layout->addStretch(100);
	this->layout->addWidget(this->searchBuffer);
	this->layout->addWidget(this->btnSearch);

	this->setWidget(this->internalWidget);

	// Connect the toolbar actions
	connect(this->optionsAction, SIGNAL(triggered(bool)), this, SLOT(optionsActionTriggered(bool)));
	connect(this->tileHorizontalAction, SIGNAL(triggered(bool)), this, SLOT(tileHorizontalActionTriggered(bool)));
	connect(this->tileVerticalAction, SIGNAL(triggered(bool)), this, SLOT(tileVerticalActionTriggered(bool)));
	connect(this->tileCascadeAction, SIGNAL(triggered(bool)), this, SLOT(tileCascadeActionTriggered(bool)));
	connect(this->previousWindowAction, SIGNAL(triggered(bool)), this, SLOT(previousWindowActionTriggered(bool)));
	connect(this->nextWindowAction, SIGNAL(triggered(bool)), this, SLOT(nextWindowActionTriggered(bool)));
	connect(this->homeAction, SIGNAL(triggered(bool)), this, SLOT(homeActionTriggered(bool)));
}

void ContextBar::optionsActionTriggered(bool checked)
{
	emit optionsClicked();
}

void ContextBar::tileHorizontalActionTriggered(bool checked)
{
	emit tileHorizontalClicked();
}

void ContextBar::tileVerticalActionTriggered(bool checked)
{
	emit tileVerticalClicked();
}

void ContextBar::tileCascadeActionTriggered(bool checked)
{
	emit tileCascadeClicked();
}

void ContextBar::previousWindowActionTriggered(bool checked)
{
	emit previousWindowClicked();
}

void ContextBar::nextWindowActionTriggered(bool checked)
{
	emit nextWindowClicked();
}

void ContextBar::homeActionTriggered(bool checked)
{
	emit homeClicked();
}
