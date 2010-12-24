#ifndef SINGLETON_CONFIG_H
#define SINGLETON_CONFIG_H

class QString;
class IniFile;

using namespace std;

class Config
{
  public:
  	static QString nick();
	static QString alternate();
	static QString email();
	static QString realName();

	static QString defaultServer();
	static int defaultPort();
	static int Theme(const QString &section);

  private:
	Config();
  	static Config *Instance();

	IniFile *iniFile;
  	static Config *instance;
};

#endif
