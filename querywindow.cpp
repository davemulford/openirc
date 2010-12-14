#include "querywindow.h"

QueryWindow::QueryWindow(QWidget *parent)
  : QMdiSubWindow(parent)
{
	// Set the minimum size of the query window
	this->setMinimumSize(250, 250);

	// Create internalWidget
	this->internalWidget = new QWidget(this);

	// Create the layout
	this->layout = new QVBoxLayout(this->internalWidget);
	this->layout->setSpacing(0);
	this->layout->setContentsMargins(0,0,0,0);

	// Create the toolbar
	this->toolbar = new QToolBar(this->internalWidget);
	this->toolbar->addAction(new QAction(QIcon(":/images/whois.png"), tr(""), this->toolbar));
	this->toolbar->addSeparator();
	this->toolbar->addAction(new QAction(QIcon(":/images/ctcp_ping.png"), tr(""), this->toolbar));
	this->toolbar->addAction(new QAction(QIcon(":/images/ctcp_version.png"), tr(""), this->toolbar));
	this->toolbar->addSeparator();
	this->toolbar->addAction(new QAction(QIcon(":/images/add_notify.png"), tr(""), this->toolbar));

	// Create the text and line edit controls
	this->chatBuffer = new QTextEdit(this->internalWidget);
	this->inputBuffer = new QLineEdit(this->internalWidget);

	// Add the controls to the layout
	this->layout->addWidget(this->toolbar);
	this->layout->addWidget(this->chatBuffer);
	this->layout->addWidget(this->inputBuffer);

	// Set the widget of the window to internalWidget
	this->setWidget(this->internalWidget);
}

void QueryWindow::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void QueryWindow::inputBufferReturnPressed()
{
}
