#ifndef OPENIRC_INIFILE_H
#define OPENIRC_INIFILE_H

#include <QtCore>

class IniFile
{
  public:
  	IniFile(const QString &filename);

	void save(const QString &filename);
	void setValue(QString groupName, QString keyName, QString value);

	QStringList groups();
	QStringList keys(const QString &groupName);
	QString value(const QString &groupName, const QString &keyName);

  private:
  	void parseFile(const QString &filename);
  	QHash<QString, QHash<QString, QString> > configItems;
};

#endif
