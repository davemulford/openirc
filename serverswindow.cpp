#include "serverswindow.h"

ServersWindow::ServersWindow(IniFile *serversFile, QWidget *parent, Qt::WindowFlags flags)
  : QDialog(parent, flags)
{
	QVBoxLayout *layout; 

	this->setMinimumSize(550,650);

	// Setup the model
	this->model = new QStandardItemModel(8, 3, this);
	this->model->setHeaderData(0, Qt::Horizontal, tr("Network"));
	this->model->setHeaderData(1, Qt::Horizontal, tr("Server"));
	this->model->setHeaderData(2, Qt::Horizontal, tr("Port"));

	layout = new QVBoxLayout(this);

	this->filterBox = new QLineEdit();

	this->serverList = new QTableView();
	this->serverList->setModel(this->model);
	this->serverList->verticalHeader()->hide();
	this->serverList->horizontalHeader()->setStretchLastSection(true);

	this->serverList->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->serverList->setSelectionMode(QAbstractItemView::SingleSelection);

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

				QStringList hostAndPort = value.split("/");

				this->model->insertRow(rowId);
				this->model->setData(model->index(rowId, 0, QModelIndex()), groupName);
				this->model->setData(model->index(rowId, 1, QModelIndex()), hostAndPort[0]);
				this->model->setData(model->index(rowId, 2, QModelIndex()), (hostAndPort.count() > 1 ? hostAndPort[1] : "6667"));

				rowId++;
			}
		}
		this->serverList->resizeColumnsToContents();
	}

	this->serversFile = serversFile;

	connect(this->filterBox, SIGNAL(textEdited(const QString &)), this, SLOT(filterBoxTextChanged(const QString &)));
	connect(this->connectButton, SIGNAL(clicked()), this, SLOT(connectButtonClicked()));
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

			QStringList hostAndPort = value.split("/");

			this->model->insertRow(rowId);
			this->model->setData(model->index(rowId, 0, QModelIndex()), networkName);
			this->model->setData(model->index(rowId, 1, QModelIndex()), hostAndPort[0]);
			this->model->setData(model->index(rowId, 2, QModelIndex()), (hostAndPort.count() > 1 ? hostAndPort[1] : "6667"));

			rowId++;
		}
	}
}

void ServersWindow::connectButtonClicked()
{
	QModelIndexList selectedIndexes = this->serverList->selectionModel()->selectedIndexes();

	if (selectedIndexes.count() > 0) {
		// We only care about the first selected item
		// (user should only be allowed single-select anyway)

		// This was a bit of a pain to work with.
		//
		// In order to get the selected "row" you have to use the model,
		// not the QTableView. And then, you don't get it back on a per-row
		// basis. You get the data on a per-cell basis.
		//
		// So, we take selectedIndexes as an array (knowing there are only 3 elements)
		// and get the data, convert it to a string, and trim it.

		QString server = selectedIndexes[1].data().toString().trimmed();
		int port = selectedIndexes[2].data().toString().trimmed().toInt();

		emit clicked(server, port);
		this->close();
	}
}
