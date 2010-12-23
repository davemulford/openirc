#ifndef OPENIRC_MDIWINDOW_H
#define OPENIRC_MDIWINDOW_H

#include <QtGui>
#include "ircclient.h"

class CommandParser;

class MdiWindow : public QMdiSubWindow
{
  Q_OBJECT

  public:
  	enum WindowType {
		StatusWindow,
		ChannelWindow,
		QueryWindow,
		PictureWindow
	};

  	MdiWindow(QWidget *parent = 0, CommandParser *parser = 0);

	QString hashName();

	IRCClient *client();
	void setClient(IRCClient *client);

	// Pure virtual functions
	// They MUST be defined ONLY by descendant classes
	virtual void append(int color, const QString &) = 0;
	virtual void appendInput(const QString &text) = 0;
	virtual MdiWindow::WindowType windowType() = 0;
	virtual void scrollToBottom() = 0;

	/////////////////////////////////////
	/// Implemented virtual functions ///
	/////////////////////////////////////

	// QWidget::closeEvent() implementation. From the doc...
	// This function is called when a close event for a top-level widget is received. 
	virtual void closeEvent(QCloseEvent *event);

  Q_SIGNALS:

  	// Emitted when a close event is received
	void closeEventTriggered(const int cid, const QString &hashName);

  protected:
	QVBoxLayout *layout;
	QToolBar 	*toolbar;
	QWidget 	*internalWidget;
	CommandParser *parser;

  private:
	QString uuid;
  	IRCClient *Client;
};

#endif
