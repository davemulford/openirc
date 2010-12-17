#ifndef OPENIRC_WINDOWTREE_H
#define OPENIRC_WINDOWTREE_H

#include <QtGui>

class WindowTree : public QDockWidget
{
  Q_OBJECT

  public:
  	WindowTree(QWidget *parent = 0, Qt::WindowFlags flags = 0);

  public slots:
  	//void itemClicked(const QModelIndex &index);

  private:
  	QVBoxLayout *layout;
  	QWidget *containerWidget;

	QTreeView *tree;
	QStandardItemModel *model;

	void createMockItems(void);
};

#endif
