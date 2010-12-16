#include "serverswindow.h"

ServersWindow::ServersWindow(IniFile *serversFile, QWidget *parent, Qt::WindowFlags flags)
  : QDialog(parent, flags)
{
	QVBoxLayout *layout; 

	// Setup the model
	this->model = new QStandardItemModel(8, 2, this);
	this->model->setHeaderData(0, Qt::Horizontal, tr("Network"));
	this->model->setHeaderData(1, Qt::Horizontal, tr("Server"));

	layout = new QVBoxLayout(this);

	this->filterBox = new QLineEdit();

	this->serverList = new QTableView();
	this->serverList->setModel(this->model);

	// Setup the push buttons
	this->connect = new QPushButton(tr("Connect"));

	layout->addWidget(this->filterBox);
	layout->addWidget(this->serverList);
	layout->addWidget(this->connect);

	if (serversFile != 0) {
		int rowId = 0;
		QStringList groups = serversFile->groups();

		QStringList::const_iterator groupIter;
		for (groupIter = groups.constBegin(); groupIter != groups.constEnd(); groupIter++) {
			QString groupName = *groupIter;
			QStringList keys = serversFile->keys(groupName);

			QStringList::const_iterator keyIter;
			for (keyIter = keys.constBegin(); keyIter != keys.constEnd(); keyIter++) {
				QString keyName = *keyIter;
				QString value = serversFile->value(groupName, keyName);

				this->model->insertRow(rowId);
				this->model->setData(model->index(rowId, 0, QModelIndex()), groupName);
				this->model->setData(model->index(rowId, 1, QModelIndex()), value);

				rowId++;
			}
		}

	}
}
