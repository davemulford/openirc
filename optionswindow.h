#ifndef OPENIRC_OPTIONSWINDOW_H
#define OPENIRC_OPTIONSWINDOW_H

#include <QtGui>

class OptionsWindow : public QDialog
{
  Q_OBJECT

  public:
  	OptionsWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  private:
  	QVBoxLayout *layout;

  	QGroupBox *userInfoBox;
	QFormLayout *userInfoLayout;
	QLabel *fullNameLabel;
	QLineEdit *fullNameEditBox;
	QLabel *emailLabel;
	QLineEdit *emailEditBox;

	QLabel *primaryNickLabel;
	QLineEdit *primaryNickEditBox;
	QLabel *secondaryNickLabel;
	QLineEdit *secondaryNickEditBox;
};

#endif
