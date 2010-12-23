#ifndef OPENIRC_CANVAS_H
#define OPENIRC_CANVAS_H

#include <QWidget>
#include <QImage>
#include <QColor>

class Canvas : public QWidget
{
  Q_OBJECT

  public:
  	Canvas(QWidget *parent = 0);
	void drawLines(const int color, const int lineWidth, const QVector<QPoint> &points);

  protected:
  	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

  private:
	void resizeImage(QImage *image, const QSize &newSize);

	QImage image;
	static QColor Palette[16];
};

#endif
