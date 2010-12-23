#include <QtCore>
#include <pcrecpp.h>

#include "container.h"
#include "ircclient.h"

#include "commandparser.h"

CommandParser::CommandParser(Container *container)
{
	this->container = container;
}

void CommandParser::parse(IRCClient *client, MdiWindow *window, const QString &input)
{
	string command, args;
	pcrecpp::RE commandRegex("^[/]+([^ ]+) ?(.*)?$");

	// Perform the match
	if (commandRegex.FullMatch(input.toLocal8Bit().constData(), &command, &args) == true) {
		QString parsedCommand = QString::fromStdString(command).toLower();

		////////////////////
		// SERVER COMMAND //
		////////////////////

		if (parsedCommand == "server") {
			QString server;
			int port = 6667;
			QStringList splitArgs = QString::fromStdString(args).split(" ");

			// Get the arguments into something we understand
			for (int i = 0; i < splitArgs.count(); i++) {
				if (i == 0) {
					server = splitArgs[i];
				} else if (i == 1) {
					port = splitArgs[i].toInt();
				}
			}

			if (client != 0) {
				window->append(1, QString("--- Connecting to server..."));
				qDebug() << "Connecting to server" << server << "(" << port << ")" << endl;
				client->connectToHost(server, port);
			}

		////////////////////
		// PICWIN COMMAND //
		////////////////////

		} else if (parsedCommand == "picwin") {
			QString picwinName = QString::fromStdString(args);

			if (container != 0) {
				container->newPictureWindow(picwinName);
			}

		//////////////////////
		// DRAWLINE COMMAND //
		//////////////////////

		} else if (parsedCommand == "drawline") {
			string winName;
			int color, lineWidth;
			int x1, y1, x2, y2;
			string extra;

			pcrecpp::RE drawLineRegex("^([@][^ ]+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)$");

			if (drawLineRegex.FullMatch(args, &winName, &color, &lineWidth, &x1, &y1, &x2, &y2)) {
				QVector<QPoint> pointPairs;

				// Put the required coords into the pointPairs vector
				pointPairs << QPoint(x1, y1) << QPoint(x2, y2);

				// TODO: Get the rest of the point pairs
				/*QStringList extraList(QString::fromStdString(extra));

				if (extraList.count() >= 4) {
					for (int i = 0; i < extraList.count(); i++) {
					}
				}*/

				if (container != 0) {
					container->picWinDrawLine(QString::fromStdString(winName), color, lineWidth, pointPairs);
				}
			} else {
				window->append(12, QString("* /drawline: invalid parameters: " + QString::fromStdString(args)));
			}
		} else {
			if (client != 0) {
				QString inputCopy;

				if (input.startsWith("/") == true) {
					inputCopy = input.midRef(1).toString();
				} else {
					inputCopy = input;
				}
				
				client->sendRawMessage(inputCopy);
			}
		}
	}
}

