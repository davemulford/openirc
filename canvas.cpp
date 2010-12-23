#include <QtGui>
#include "canvas.h"

QColor Canvas::Palette[16] = {
	QColor("#FFFFFF"),
	QColor("#000000"),
	QColor("#00007F"),
	QColor("#009300"),
	QColor("#FF0000"),
	QColor("#7F0000"),
	QColor("#9C009C"),
	QColor("#FC7F00"),
	QColor("#FFFF00"),
	QColor("#00FC00"),
	QColor("#009393"),
	QColor("#00FFFF"),
	QColor("#0000FC"),
	QColor("#FF00FF"),
	QColor("#7F7F7F"),
	QColor("#D2D2D2")
};

Canvas::Canvas(QWidget *parent)
  : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);

	image = QImage(width(), height(), QImage::Format_RGB32);
	image.fill(qRgb(255,255,255));
}

void Canvas::drawLines(const int color, const int lineWidth, const QVector<QPoint> &points)
{
	QColor penColor = Canvas::Palette[color % 16];
	QPen pen = QPen(penColor, lineWidth);

	QPainter brush(&image);
	
	brush.setPen(pen);
	brush.drawLines(points);

	update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QPainter brush(this);
	QRect myrect = event->rect();
	brush.drawImage(myrect, image, myrect);
}

void Canvas::resizeEvent(QResizeEvent *event)                                                                                                                                                                                          
{                                                                                                                                                                                                                                            
    if (width() > image.width() || height() > image.height()) {                                                                                                                                                                              
        int newWidth = qMax(width() + 128, image.width());                                                                                                                                                                                   
        int newHeight = qMax(height() + 128, image.height());                                                                                                                                                                                
        resizeImage(&image, QSize(newWidth, newHeight));                                                                                                                                                                                     
        update();                                                                                                                                                                                                                            
    }                                                                                                                                                                                                                                        
    QWidget::resizeEvent(event);                                                                                                                                                                                                             
}   

void Canvas::resizeImage(QImage *image, const QSize &newSize)
{
	if (image->size() == newSize) {
		return;
	}

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0,0), *image);
	*image = newImage;
}
