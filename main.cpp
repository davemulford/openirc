#include <QApplication>
#include "container.h"

int main(int argc, char *argv[])
{
	//Q_INIT_RESOURCE(mdi);

	QApplication app(argc, argv);
	Container container;
	container.show();
	return app.exec();
}
