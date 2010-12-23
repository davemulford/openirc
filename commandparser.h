#ifndef OPENIRC_COMMANDPARSER_H
#define OPENIRC_COMMANDPARSER_H

class QString;
class Container;
class IRCClient;
class MdiWindow;

class CommandParser
{
  public:
  	CommandParser(Container *container);
	void parse(IRCClient *client, MdiWindow *window, const QString &command);

  private:
	Container *container;
};

#endif
