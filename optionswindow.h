#ifndef OPENIRC_OPTIONSWINDOW_H
#define OPENIRC_OPTIONSWINDOW_H

#include <QtGui>

class OptionsWindow : public QDialog
{
  Q_OBJECT

  public:
  	OptionsWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  private:
	QTabWidget *tabWidget;
	QWidget *tab;
	QGroupBox *groupBox;
	QLabel *label;
	QLabel *label_2;
	QLabel *label_3;
	QLabel *label_4;
	QLabel *label_5;
	QLineEdit *lineEdit;
	QLineEdit *lineEdit_2;
	QLineEdit *lineEdit_3;
	QLineEdit *lineEdit_4;
	QGroupBox *groupBox_5;
	QLabel *label_12;
	QLabel *label_13;
	QLabel *label_14;
	QLineEdit *lineEdit_5;
	QLineEdit *lineEdit_6;
	QCheckBox *checkBox;
	QWidget *tab_2;
	QGroupBox *groupBox_2;
	QLabel *label_6;
	QPushButton *pushButton;
	QLabel *label_9;
	QGroupBox *groupBox_3;
	QLabel *label_7;
	QPushButton *pushButton_2;
	QLabel *label_10;
	QGroupBox *groupBox_4;
	QLabel *label_8;
	QPushButton *pushButton_3;
	QLabel *label_11;
	QPushButton *pushButton_4;
	QPushButton *pushButton_5;
};

#endif
