#include <QtCore/QCoreApplication>
#include <QApplication>
#include "Gui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Gui win(700, 600);

	win.show();

	return a.exec();
}
