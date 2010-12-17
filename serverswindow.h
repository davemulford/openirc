#ifndef OPENIRC_SERVERSWINDOW_H
#define OPENIRC_SERVERSWINDOW_H

#include <QtGui>
#include "inifile.h"

class ServersWindow : public QDialog
{
  Q_OBJECT

  public:
  	ServersWindow(IniFile *serversFile, QWidget *parent = 0, Qt::WindowFlags flags = 0);

  public slots:
  	void filterBoxTextChanged(const QString &text);
	void connectButtonClicked();

  Q_SIGNALS:
  	void clicked(const QString &server, const int port);

  private:
  	QLineEdit *filterBox;
	QTableView *serverList;

	QPushButton *connectButton;
	QPushButton *closeButton;

	QStandardItemModel *model;

	IniFile *serversFile;
};

#endif
