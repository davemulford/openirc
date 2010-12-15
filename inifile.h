#ifndef OPENIRC_INIFILE_H
#define OPENIRC_INIFILE_H

#include <QtCore>

class IniFile
{
  public:
  	IniFile(const QString &filename);

	QStringList groups();
	QStringList keys(const QString &groupName);
	QString value(const QString &groupName, const QString &keyName);

  private:
  	QHash<QString, QHash<QString, QString> > configItems;

  	void parseFile(const QString &filename);
};

#endif
