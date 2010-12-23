#include <iostream>
#include <string>
#include <fstream>
#include "pcrecpp.h"
#include "inifile.h"

using namespace std;

IniFile::IniFile(const QString &filename)
{
	this->parseFile(filename);
}

QStringList IniFile::groups()
{
	QStringList groups;
	QHash<QString, QHash<QString, QString> >::const_iterator groupIterator = this->configItems.constBegin();

	for (groupIterator = this->configItems.constBegin(); groupIterator!= this->configItems.constEnd(); groupIterator++) {
		groups.append(groupIterator.key());
	}

	return(groups);
}

QStringList IniFile::keys(const QString &groupName)
{
	QStringList keys;

	if (this->configItems.contains(groupName)) {
		QHash<QString, QString> groupHash = this->configItems.value(groupName);
		QHash<QString, QString>::const_iterator keyIterator = groupHash.constBegin();

		for (keyIterator = groupHash.constBegin(); keyIterator != groupHash.constEnd(); keyIterator++) {
			keys.append(keyIterator.key());
		}
	}
	return(keys);
}

QString IniFile::value(const QString &groupName, const QString &keyName)
{
	return(this->configItems.value(groupName).value(keyName));
}

void IniFile::setValue(QString groupName, QString keyName, QString value)
{
	this->configItems[groupName][keyName] = value;
}

void IniFile::save(const QString &filename)
{
    ofstream ini;
    ini.open(filename.toAscii());
	QStringList groups = this->groups();

	QStringList::const_iterator groupIter;
	for (groupIter = groups.constBegin(); groupIter != groups.constEnd(); groupIter++) {
		QString groupName = *groupIter;
		QStringList keys = this->keys(groupName);
        ini << "[" << groupName.toStdString() << "]\n";

		QStringList::const_iterator keyIter;
		for (keyIter = keys.constBegin(); keyIter != keys.constEnd(); keyIter++) {
			QString keyName = *keyIter;
			QString value = this->value(groupName, keyName);
            ini << keyName.toStdString() << "=" << value.toStdString() << "\n";
		}
	}
    ini.close();
}

void IniFile::parseFile(const QString &filename)
{
	pcrecpp::RE Group("^\\[(.*)\\]$");
	pcrecpp::RE ItemVal("^([^=]+)=(.*)$");

    ifstream ini(filename.toAscii());
    string temp,group,item,value;
    while (getline(ini,temp)) {
        if (Group.PartialMatch(temp,&group)) {
        }
        else if (ItemVal.PartialMatch(temp,&item,&value)) {
            if (this->configItems.contains(QString::fromStdString(group)) == false) {
                QHash<QString, QString> insertme;
                this->configItems.insert(QString::fromStdString(group),insertme);
            }
            this->configItems[QString::fromStdString(group)][QString::fromStdString(item)] = QString::fromStdString(value);
        }
    }
}

