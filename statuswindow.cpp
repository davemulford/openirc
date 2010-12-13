#include "statuswindow.h"

Window::Window(QWidget *parent)
  : QMdiSubWindow(parent, 0) 
{
	this->setMinimumSize(250, 250);

	this->mainBuffer = new QTextEdit(this);
	this->inputBuffer = new QLineEdit(this);

	this->internalWidget = new QWidget(this);
	this->layout = new QVBoxLayout(this->internalWidget);

	layout->addWidget(this->mainBuffer);
	layout->addWidget(this->inputBuffer);

	this->setWidget(this->internalWidget);

	connect(this->inputBuffer, SIGNAL(returnPressed()), this, SLOT(inputBufferReturnPressed()));
}

void Window::setTitle(const QString &title)
{
	this->setWindowTitle(title);
}

void Window::inputBufferReturnPressed()
{
	this->mainBuffer->append(this->inputBuffer->text());
	this->inputBuffer->clear();
}
