#ifndef OPENIRC_IALITEM_H
#define OPENIRC_IALITEM_H

#include <QtCore>

class IALItem
{
  public:
	int idle;
	QString address;
	QHash<QString, QString> channels;
};

#endif
