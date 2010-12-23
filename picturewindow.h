#ifndef OPENIRC_PICTUREWINDOW_H
#define OPENIRC_PICTUREWINDOW_H

#include <QMdiSubWindow>

class Canvas;

class PictureWindow : public QMdiSubWindow
{
  Q_OBJECT

  public:
  	PictureWindow(QWidget *parent = 0);

	void drawLines(const int color, const int lineWidth, const QVector<QPoint> &points);

  private:
  	Canvas *canvas;
};

#endif
