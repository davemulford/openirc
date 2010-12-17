#ifndef OPENIRC_WINDOWTREE_H
#define OPENIRC_WINDOWTREE_H

#include <QtGui>
#include "windowtreeitem.h"

class WindowTree : public QDockWidget
{
  Q_OBJECT

  public:
  	WindowTree(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	void addStatusWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window);
	void addChannelWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window);
	void addQueryWindow(const unsigned int cid, const QString &name, QMdiSubWindow *window);

  public slots:
  	void itemClicked(QTreeWidgetItem *item, int column);

  Q_SIGNALS:
  	void windowItemClicked(QMdiSubWindow *subWindow);

  private:
  	QVBoxLayout *layout;
  	QWidget *containerWidget;

	QTreeWidget *tree;
	QStandardItemModel *model;

	QHash<int, WindowTreeItem *> rootItems;

	void createMockItems(void);
};

#endif
