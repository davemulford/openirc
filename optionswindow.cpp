#include "optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent, Qt::WindowFlags flags)
  : QDialog(parent, flags)
{
	// Set the min width
	this->setMinimumWidth(400);

	// Create the top-level layout
	this->layout = new QVBoxLayout(this);

	// Create the user info section
	this->userInfoBox = new QGroupBox(tr("User Info"), this);
	this->userInfoLayout = new QFormLayout(this->userInfoBox);

	this->fullNameLabel = new QLabel(tr("Full name:"), this);
	this->fullNameEditBox = new QLineEdit(this);
	this->userInfoLayout->addRow(this->fullNameLabel, this->fullNameEditBox);

	this->emailLabel = new QLabel(tr("Email:"), this);
	this->emailEditBox = new QLineEdit(this);
	this->userInfoLayout->addRow(this->emailLabel, this->emailEditBox);

	this->primaryNickLabel = new QLabel(tr("Primary Nick:"), this);
	this->primaryNickEditBox = new QLineEdit(this);
	this->userInfoLayout->addRow(this->primaryNickLabel, this->primaryNickEditBox);

	this->secondaryNickLabel = new QLabel(tr("Secondary Nick:"), this);
	this->secondaryNickEditBox = new QLineEdit(this);
	this->userInfoLayout->addRow(this->secondaryNickLabel, this->secondaryNickEditBox);

	// Add all top-level widgets to layout
	this->layout->addWidget(this->userInfoBox);
}
