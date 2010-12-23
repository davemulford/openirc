#include <QtGui>

#include "canvas.h"
#include "picturewindow.h"

PictureWindow::PictureWindow(QWidget *parent)
  : QMdiSubWindow(parent, 0)
{
	this->setGeometry(0,0,280,280);
	canvas = new Canvas;

	this->setWidget(canvas);
}

void PictureWindow::drawLines(const int color, const int lineWidth, const QVector<QPoint> &points)
{
	if (canvas != 0) {
		canvas->drawLines(color, lineWidth, points);
	}
}
