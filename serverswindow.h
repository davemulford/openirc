#ifndef OPENIRC_SERVERSWINDOW_H
#define OPENIRC_SERVERSWINDOW_H

#include <QtGui>
#include "inifile.h"

class ServersWindow : public QDialog
{
  Q_OBJECT

  public:
  	ServersWindow(IniFile *serversFile, QWidget *parent = 0, Qt::WindowFlags flags = 0);

  private:
  	QLineEdit *filterBox;
	QTableView *serverList;

	QPushButton *connect;
	QPushButton *close;

	QStandardItemModel *model;
};

#endif
