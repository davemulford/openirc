#include "optionswindow.h"

/*OptionsWindow::OptionsWindow(IniFile *optionsFile, QWidget *parent, Qt::WindowFlags flags)
  : QDialog(parent, flags)
{
	this->setFixedSize(500, 350);

	// Setup the tab widgets
	this->tabContainer = new QTabWidget();
	this->tabLayout = new QVBoxLayout(this);

	this->setupTab = new QWidget();
	this->setupLayout = new QVBoxLayout(this->setupTab);

	// User info section
	this->userInfoGroup = new QGroupBox(tr("User Information"), this->setupTab);

	this->userInfoLayout = new QHBoxLayout(this->userInfoGroup);
	this->userInfoLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	this->userInfoImage = new QLabel();
	this->userInfoImage->setPixmap(QPixmap(tr(":/images/config-userinfo.png")));
	this->userInfoLayout->addWidget(this->userInfoImage);
	this->userInfoLayout->addSpacing(20);

	this->userInfoFormContainer = new QWidget();
	this->userInfoFormLayout = new QFormLayout(this->userInfoFormContainer);

	this->nickLabel = new QLabel(tr("Nickname:"));
	this->nick = new QLineEdit();
	this->userInfoFormLayout->addRow(this->nickLabel, this->nick);

	this->alternateLabel = new QLabel(tr("Alternate:"));
	this->alternate = new QLineEdit();
	this->userInfoFormLayout->addRow(this->alternateLabel, this->alternate);

	this->emailLabel = new QLabel(tr("Email:"));
	this->email = new QLineEdit();
	this->userInfoFormLayout->addRow(this->emailLabel, this->email);

	this->realNameLabel = new QLabel(tr("IRC Name:"));
	this->realName = new QLineEdit();
	this->userInfoFormLayout->addRow(this->realNameLabel, this->realName);

	this->userInfoLayout->addWidget(this->userInfoFormContainer);

	// IRC Server section
	this->ircServerGroup = new QGroupBox(tr("IRC Server"), this->setupTab);

	this->ircServerLayout = new QHBoxLayout(this->ircServerGroup);
	this->ircServerLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	this->ircServerImage = new QLabel();
	this->ircServerImage->setPixmap(QPixmap(tr(":/images/connect.png")));
	this->ircServerLayout->addWidget(this->ircServerImage);
	this->ircServerLayout->addSpacing(20);

	this->ircServerFormContainer = new QWidget();
	this->ircServerFormLayout = new QFormLayout(this->ircServerFormContainer);

	this->serverLabel = new QLabel(tr("Server:"));
	this->server = new QLineEdit();
	this->ircServerFormLayout->addRow(this->serverLabel, this->server);

	this->portLabel = new QLabel(tr("Port:"));
	this->port = new QLineEdit();
	this->ircServerFormLayout->addRow(this->portLabel, this->port);

	this->ircServerLayout->addWidget(this->ircServerFormContainer);

	this->setupLayout->addWidget(this->userInfoGroup);
	this->setupLayout->addWidget(this->ircServerGroup);

	this->tabContainer->addTab(this->setupTab, QString());
	this->tabContainer->setTabText(0, tr("Setup"));
	//this->tabContainer->setTabText(1, tr("General"));

	this->tabLayout->addWidget(this->tabContainer);
	this->loadOptionsFromFile(optionsFile);

}*/

OptionsWindow::OptionsWindow(QWidget *parent, Qt::WindowFlags flags)
  : QDialog(parent, flags)
{
	this->setFixedSize(391, 356);
	this->setSizeGripEnabled(false);
        this->tabWidget = new QTabWidget(this);
        this->tabWidget->setGeometry(QRect(6, 6, 379, 313));
        this->tab = new QWidget();
        this->groupBox = new QGroupBox(tab);
        this->groupBox->setGeometry(QRect(6, 6, 361, 151));
        this->label = new QLabel(groupBox);
        this->label->setGeometry(QRect(12, 24, 49, 61));
        this->label->setPixmap(QPixmap(QString::fromUtf8(":/images/config-userinfo.png")));
        this->label_2 = new QLabel(groupBox);
        this->label_2->setGeometry(QRect(72, 30, 73, 17));
        this->label_3 = new QLabel(groupBox);
        this->label_3->setGeometry(QRect(78, 60, 67, 17));
        this->label_4 = new QLabel(groupBox);
        this->label_4->setGeometry(QRect(96, 90, 43, 17));
        this->label_5 = new QLabel(groupBox);
        this->label_5->setGeometry(QRect(72, 120, 67, 17));
        this->lineEdit = new QLineEdit(groupBox);
        this->lineEdit->setGeometry(QRect(150, 24, 199, 23));
        this->lineEdit_2 = new QLineEdit(groupBox);
        this->lineEdit_2->setGeometry(QRect(150, 54, 199, 23));
        this->lineEdit_3 = new QLineEdit(groupBox);
        this->lineEdit_3->setGeometry(QRect(150, 84, 199, 23));
        this->lineEdit_4 = new QLineEdit(groupBox);
        this->lineEdit_4->setGeometry(QRect(150, 114, 199, 23));
        this->groupBox_5 = new QGroupBox(tab);
        this->groupBox_5->setGeometry(QRect(6, 162, 361, 109));
        this->label_12 = new QLabel(groupBox_5);
        this->label_12->setGeometry(QRect(18, 24, 43, 37));
        this->label_12->setPixmap(QPixmap(QString::fromUtf8(":/images/connect.png")));
        this->label_13 = new QLabel(groupBox_5);
        this->label_13->setGeometry(QRect(90, 30, 49, 17));
        this->label_14 = new QLabel(groupBox_5);
        this->label_14->setGeometry(QRect(108, 60, 31, 17));
        this->lineEdit_5 = new QLineEdit(groupBox_5);
        this->lineEdit_5->setGeometry(QRect(150, 24, 199, 23));
        this->lineEdit_6 = new QLineEdit(groupBox_5);
        this->lineEdit_6->setGeometry(QRect(150, 54, 199, 23));
        this->checkBox = new QCheckBox(groupBox_5);
        this->checkBox->setGeometry(QRect(150, 78, 115, 22));
        this->tabWidget->addTab(tab, QString());
        this->tab_2 = new QWidget();
        this->groupBox_2 = new QGroupBox(tab_2);
        this->groupBox_2->setGeometry(QRect(6, 6, 361, 85));
        this->label_6 = new QLabel(groupBox_2);
        this->label_6->setGeometry(QRect(12, 24, 49, 43));
        this->label_6->setPixmap(QPixmap(QString::fromUtf8(":/images/config-home.png")));
        this->pushButton = new QPushButton(groupBox_2);
        this->pushButton->setGeometry(QRect(234, 48, 115, 27));
        this->label_9 = new QLabel(groupBox_2);
        this->label_9->setGeometry(QRect(66, 24, 247, 17));
        this->groupBox_3 = new QGroupBox(tab_2);
        this->groupBox_3->setGeometry(QRect(6, 96, 361, 85));
        this->label_7 = new QLabel(groupBox_3);
        this->label_7->setGeometry(QRect(12, 18, 49, 49));
        this->label_7->setPixmap(QPixmap(QString::fromUtf8(":/images/config-ctcps.png")));
        this->pushButton_2 = new QPushButton(groupBox_3);
        this->pushButton_2->setGeometry(QRect(234, 48, 115, 27));
        this->label_10 = new QLabel(groupBox_3);
        this->label_10->setGeometry(QRect(66, 24, 235, 17));
        this->groupBox_4 = new QGroupBox(tab_2);
        this->groupBox_4->setGeometry(QRect(6, 186, 361, 85));
        this->label_8 = new QLabel(groupBox_4);
        this->label_8->setGeometry(QRect(12, 24, 49, 49));
        this->label_8->setPixmap(QPixmap(QString::fromUtf8(":/images/config-customize.png")));
        this->pushButton_3 = new QPushButton(groupBox_4);
        this->pushButton_3->setGeometry(QRect(234, 48, 115, 27));
        this->label_11 = new QLabel(groupBox_4);
        this->label_11->setGeometry(QRect(66, 24, 175, 17));
        this->tabWidget->addTab(tab_2, QString());
        this->pushButton_4 = new QPushButton(this);
        this->pushButton_4->setGeometry(QRect(300, 324, 84, 27));
        this->pushButton_5 = new QPushButton(this);
        this->pushButton_5->setGeometry(QRect(210, 324, 84, 27));

        this->tabWidget->setCurrentIndex(0);

	this->setWindowTitle(QApplication::translate("Dialog", "Configuration Dialog", 0, QApplication::UnicodeUTF8));
        this->groupBox->setTitle(QApplication::translate("Dialog", "Setup Information", 0, QApplication::UnicodeUTF8));
        this->label->setText(QString());
        this->label_2->setText(QApplication::translate("Dialog", "Nickname:", 0, QApplication::UnicodeUTF8));
        this->label_3->setText(QApplication::translate("Dialog", "Alternate:", 0, QApplication::UnicodeUTF8));
        this->label_4->setText(QApplication::translate("Dialog", "E-Mail:", 0, QApplication::UnicodeUTF8));
        this->label_5->setText(QApplication::translate("Dialog", "IRC Name:", 0, QApplication::UnicodeUTF8));
        this->groupBox_5->setTitle(QApplication::translate("Dialog", "Server Information", 0, QApplication::UnicodeUTF8));
        this->label_12->setText(QString());
        this->label_13->setText(QApplication::translate("Dialog", "Server:", 0, QApplication::UnicodeUTF8));
        this->label_14->setText(QApplication::translate("Dialog", "Port:", 0, QApplication::UnicodeUTF8));
        this->checkBox->setText(QApplication::translate("Dialog", "Invisible Mode", 0, QApplication::UnicodeUTF8));
        this->tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "Setup", 0, QApplication::UnicodeUTF8));
        this->groupBox_2->setTitle(QApplication::translate("Dialog", "Away Options", 0, QApplication::UnicodeUTF8));
        this->label_6->setText(QString());
        this->pushButton->setText(QApplication::translate("Dialog", "Away Options...", 0, QApplication::UnicodeUTF8));
        this->label_9->setText(QApplication::translate("Dialog", "Configure the away systems behavior", 0, QApplication::UnicodeUTF8));
        this->groupBox_3->setTitle(QApplication::translate("Dialog", "CTCP", 0, QApplication::UnicodeUTF8));
        this->label_7->setText(QString());
        this->pushButton_2->setText(QApplication::translate("Dialog", "CTCP Options...", 0, QApplication::UnicodeUTF8));
        this->label_10->setText(QApplication::translate("Dialog", "Configure CTCP message responses", 0, QApplication::UnicodeUTF8));
        this->groupBox_4->setTitle(QApplication::translate("Dialog", "Other", 0, QApplication::UnicodeUTF8));
        this->label_8->setText(QString());
        this->pushButton_3->setText(QApplication::translate("Dialog", "Messages...", 0, QApplication::UnicodeUTF8));
        this->label_11->setText(QApplication::translate("Dialog", "Configure basic messages", 0, QApplication::UnicodeUTF8));
        this->tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Dialog", "General", 0, QApplication::UnicodeUTF8));
        this->pushButton_4->setText(QApplication::translate("Dialog", "Ok", 0, QApplication::UnicodeUTF8));
        this->pushButton_5->setText(QApplication::translate("Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
}

OptionsWindow::~OptionsWindow()
{
/*
	this->optionsFile->setValue("UserInfo", "nick", this->nick->text());
	this->optionsFile->setValue("UserInfo", "alternate", this->alternate->text());
	this->optionsFile->setValue("UserInfo", "email", this->email->text());
	this->optionsFile->setValue("UserInfo", "realName", this->realName->text());

	this->optionsFile->setValue("IrcServer", "server", this->server->text());
	this->optionsFile->setValue("IrcServer", "port", this->port->text());

	this->optionsFile->save("openirc.ini");
*/
}

/*void OptionsWindow::loadOptionsFromFile(IniFile *optionsFile)
{
	if (optionsFile != 0) {

		this->optionsFile = optionsFile;

		// User info
		this->nick->setText(optionsFile->value("UserInfo", "nick"));
		this->alternate->setText(optionsFile->value("UserInfo", "alternate"));
		this->email->setText(optionsFile->value("UserInfo", "email"));
		this->realName->setText(optionsFile->value("UserInfo", "realName"));

		// Server info
		this->server->setText(optionsFile->value("IrcServer", "server"));
		this->port->setText(optionsFile->value("IrcServer", "port"));

	}
}*/
