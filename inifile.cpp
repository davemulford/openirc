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

	for (groupIterator = this->configItems.constBegin(); groupIterator!= this->configItems.constEnd(); groupIterator++) {
		qDebug() << groupIterator.key();
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
