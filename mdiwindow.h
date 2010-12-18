#ifndef OPENIRC_MDIWINDOW_H
#define OPENIRC_MDIWINDOW_H

#include <QtGui>
#include "ircclient.h"

class MdiWindow : public QMdiSubWindow
{
  Q_OBJECT

  public:
  	enum WindowType {
		StatusWindow,
		ChannelWindow,
		QueryWindow
	};

  	MdiWindow(QWidget *parent = 0);

	QString hashName();

	IRCClient *client();
	void setClient(IRCClient *client);

	// Pure virtual functions
	// They MUST be defined ONLY by descendant classes
	virtual void append(const QString &) = 0;
	virtual MdiWindow::WindowType windowType() = 0;

  protected:
	QVBoxLayout *layout;
	QToolBar 	*toolbar;
	QWidget 	*internalWidget;

  private:
	QString uuid;
  	IRCClient *Client;
};

#endif
