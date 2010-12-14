#ifndef OPENIRC_IRCCOMMANDPARSER_H
#define OPENIRC_IRCCOMMANDPARSER_H

class IRCCommandParser
{
  public:
	enum CommandType {
		OfflineCommand,
		IRCCommand,
		IRCMessage,
		UnknownCommand
	};

  	IRCCommandParser(const QString &commandString = 0);
	void parse();
	void setCommandString(const QString &commandString);

	CommandType type();

	QString commandString();
	QString command();
	QString args();
	QStringList argList();

  private:
  	QString _commandString;
	QString _command;
	QString _args;

	CommandType _type;
	QStringList offlineCommands;
};

#endif
