#include <glib.h>
#include "inifile.h"

IniFile::IniFile(const QString &filename)
{
	this->parseFile(filename);
}

QStringList IniFile::groups()
{
	QStringList groups;
	QHash<QString, QHash<QString, QString> >::const_iterator groupIterator = this->configItems.constBegin();

	for (groupIterator = this->configItems.constBegin(); groupIterator!= this->configItems.constEnd(); ++groupIterator) {
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

		for (keyIterator = groupHash.constBegin(); keyIterator != groupHash.constEnd(); ++keyIterator) {
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
	GKeyFile *keyFile = g_key_file_new();

	if (g_key_file_load_from_file(keyFile, filename.toLocal8Bit().constData(), G_KEY_FILE_NONE, 0 /* no error handling */) == FALSE) {
		g_key_file_free(keyFile);
		return;
	}

	// Take all the values from the IniFile and put it into
	// the GKeyFile structure.
	QStringList groups = this->groups();

	QStringList::const_iterator groupIter;
	for (groupIter = groups.constBegin(); groupIter != groups.constEnd(); ++groupIter) {
		QString groupName = *groupIter;
		QStringList keys = this->keys(groupName);

		QStringList::const_iterator keyIter;
		for (keyIter = keys.constBegin(); keyIter != keys.constEnd(); ++keyIter) {
			QString keyName = *keyIter;
			QString value = this->value(groupName, keyName);

			g_key_file_set_value(keyFile, groupName.toLocal8Bit().constData(), keyName.toLocal8Bit().constData(), value.toLocal8Bit().constData());
		}
	}

	// Save our GKeyFile to a file
	gsize keyFileDataLength;
	gchar *keyFileData = g_key_file_to_data(keyFile, &keyFileDataLength, 0 /* no error handler */);

	QFile file(filename);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << keyFileData;
	}

	g_free(keyFileData);
	g_key_file_free(keyFile);
}

void IniFile::parseFile(const QString &filename)
{
	gchar **groups;
	gsize g, groupCount;

	GKeyFile *keyFile = g_key_file_new();

	if (g_key_file_load_from_file(keyFile, filename.toLocal8Bit().constData(), G_KEY_FILE_NONE, 0 /* no error handling */) == FALSE) {
		g_key_file_free(keyFile);
		return;
	}

	// Now we get the groups from the keyFile.
	// For each group, we get they keys, and the value for each key.
	//
	// The groupName is the top-level hashkey.
	// The keyName is bottom-level hashkey.
	// The value is the bottom-level hashvalue.
	if ((groups = g_key_file_get_groups(keyFile, &groupCount)) != 0) {
		for (g = 0; g < groupCount; g++) {
			gchar **keys;
			gsize k, keyCount;

			if ((keys = g_key_file_get_keys(keyFile, groups[g], &keyCount, 0 /* no error handler */)) != 0) {
				QHash<QString, QString> groupItems;

				for (k = 0; k < keyCount; k++) {
					gchar *value;

					if ((value = g_key_file_get_value(keyFile, groups[g], keys[k], 0)) != 0) {
						groupItems.insert(QString(keys[k]), QString(value));
						g_free(value);
					}
				}

				g_strfreev(keys);
				this->configItems.insert(QString(groups[g]), groupItems);
			}
		}
	}

	g_strfreev(groups);
	g_key_file_free(keyFile);
}
