#ifndef OPENIRC_STATUSWINDOW_H
#define OPENIRC_STATUSWINDOW_H

#include <QtGui>

// StatusWindow Class Definition {{{

class Window : public QMdiSubWindow
{
	Q_OBJECT
  public:
  	Window(QWidget *parent = 0);
	void setTitle(const QString &title);

  public slots:
	void inputBufferReturnPressed();

  private:
	QWidget *internalWidget;
	QVBoxLayout *layout;
	QTextEdit *mainBuffer;
	QLineEdit *inputBuffer;
};

// StatusWindow Class Definition }}}

// StatusWindow Implementation {{{

Window::Window(QWidget *parent)
  : QMdiSubWindow(parent, 0) 
{
	// Set the minimum size of the status window
	this->setMinimumSize(250, 250);

	// Create the controls that the window will hold.
	this->mainBuffer = new QTextEdit(this);
	this->inputBuffer = new QLineEdit(this);

	// The internalWidget is the 'container' for all the controls in the window.
	// That's just how a QMdiSubWindow works.
	this->internalWidget = new QWidget(this);

	// We create a vertical layout, cause it's easier and
	// requires no specific code for the resizing of windows.
	//
	// A subtle thing here is that the generic internalWidget is
	// the parent of the vertical layout.
	this->layout = new QVBoxLayout(this->internalWidget);

	// We add the controls to the vertical layout
	layout->addWidget(this->mainBuffer);
	layout->addWidget(this->inputBuffer);

	// The QMdiSubWindow class has this setWidget() function
	// which allows us to simply set the main widget for the window.
	// Basically, we can add anything we want to the generic widget,
	// and the QMdiSubWindow won't care.
	this->setWidget(this->internalWidget);

	// Connect any signals/slots we want
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

// StatusWindow Implementation }}}

#endif
