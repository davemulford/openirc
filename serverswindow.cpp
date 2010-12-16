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
	this->connectButton = new QPushButton(tr("Connect"));

	layout->addWidget(this->filterBox);
	layout->addWidget(this->serverList);
	layout->addWidget(this->connectButton);

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

				/*QStandardItem *editableItem = new QStandardItem(true);
				editableItem->setText(value);
				editableItem->setEditable(true);
				this->model->setItem(model->index(rowId, 1, QModelIndex()).row(), 1, editableItem);*/

				rowId++;
			}
		}
	}

	this->serversFile = serversFile;

	connect(this->filterBox, SIGNAL(textEdited(const QString &)), this, SLOT(filterBoxTextChanged(const QString &)));
}

void ServersWindow::filterBoxTextChanged(const QString &text)
{
	QStringList networks = this->serversFile->groups().filter(text, Qt::CaseInsensitive);
	this->model->removeRows(0, this->model->rowCount(QModelIndex()), QModelIndex());

	int rowId = 0;
	QStringList::const_iterator networkIter;
	for (networkIter = networks.constBegin(); networkIter != networks.constEnd(); networkIter++) {
		QString networkName = *networkIter;
		QStringList keys = serversFile->keys(networkName);

		QStringList::const_iterator keyIter;
		for (keyIter = keys.constBegin(); keyIter != keys.constEnd(); keyIter++) {
			QString keyName = *keyIter;
			QString value = serversFile->value(networkName, keyName);

			this->model->insertRow(rowId);
			this->model->setData(model->index(rowId, 0, QModelIndex()), networkName);
			this->model->setData(model->index(rowId, 1, QModelIndex()), value);

			rowId++;
		}
	}
}
