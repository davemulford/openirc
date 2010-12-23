#include <QString>
#include "inifile.h"

#include "config.h"

/////////////////////////////////
// PRIVATE SINGLETON FUNCTIONS //
/////////////////////////////////

/* This is the static instance from which all
	references are made. It's just hidden from sight ;) */
Config *Config::instance;

/* Returns a pointer to the static instance, after
	creating it, if necessary. */
Config *Config::Instance() {
	if (!instance) {
		instance = new Config();
	}

	return(instance);
}

/* The constructor which is called the first
	time Config is accessed. Loads the configuration file. */
Config::Config() {
	iniFile = new IniFile(QString("openirc.ini"));
}



////////////////////////////////
// PUBLIC SINGLETON FUNCTIONS //
////////////////////////////////

/* Returns the configured nickname */
QString Config::nick() {
	return(Instance()->iniFile->value("UserInfo", "nick"));
}

/* Returns the configured alternate nickname */
QString Config::alternate() {
	return(Instance()->iniFile->value("UserInfo", "alternate"));
}

/* Returns the configured email address */
QString Config::email() {
	return(Instance()->iniFile->value("UserInfo", "email"));
}

/* Returns the configured real name */
QString Config::realName() {
	return(Instance()->iniFile->value("UserInfo", "realName"));
}

/* Returns the default IRC server to connect to */
QString Config::defaultServer() {
	return(Instance()->iniFile->value("IrcServer", "server"));
}

/* Returns the default IRC port to connect on, or
	6667 if none or an invalid port is specified */
int Config::defaultPort() {
	bool ok = false;
	int port = Instance()->iniFile->value("IrcServer", "port").toInt(&ok);

	if (ok == true) {
		return(port);
	} else {
		return(6667);
	}
}

