#include "window.h"

Window::Window(QWidget *parent)
  : QMdiSubWindow(parent, 0) 
{
	this->mainBuffer = new QTextEdit(this);
}
