#include <QtCore>
#include "irccommandparser.h"

IRCCommandParser::IRCCommandParser(const QString &commandString)
{
	this->offlineCommands = QStringList() << "SERVER";

	if (commandString != 0) {
		this->_commandString = commandString;
		this->parse();
	}
}

void IRCCommandParser::parse()
{
	this->_command = QString("");
	this->_args = QString("");
	this->_type = IRCCommandParser::UnknownCommand;

	if (this->_commandString.isNull() || this->_commandString.isEmpty()) {
		return;
	}

	QString commandString = this->_commandString;

	// Is it a command?
	if (commandString.startsWith("/")) {
		QStringList splitString = commandString.split(" ");

		this->_command = splitString.at(0).right(splitString.at(0).length() - 1).toUpper();
		
		QStringList::const_iterator iterator;
		for (iterator = splitString.constBegin(); iterator != splitString.constEnd(); ++iterator) {
			if (iterator != splitString.constBegin()) {
				this->_args.append(*iterator);
				
				if (iterator != splitString.constEnd()) {
					this->_args.append(" ");
				}
			}
		}

		if (this->offlineCommands.indexOf(this->_command) != -1) {
			this->_type = IRCCommandParser::OfflineCommand;
		}

	} else {
		this->_type = IRCCommandParser::IRCMessage;
		this->_command = commandString;
	}
}

void IRCCommandParser::setCommandString(const QString &commandString)
{
	if (!commandString.isNull()) {
		this->_commandString = commandString;
	}
}

IRCCommandParser::CommandType IRCCommandParser::type()
{
	return(this->_type);
}

QString IRCCommandParser::commandString()
{
	return(this->_commandString);
}

QString IRCCommandParser::command()
{
	return(this->_command);
}

QString IRCCommandParser::args()
{
	return(this->_args);
}

QStringList IRCCommandParser::argList()
{
	return(this->_args.split(" ", QString::SkipEmptyParts));
}

