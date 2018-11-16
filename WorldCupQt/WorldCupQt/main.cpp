#include "WorldCupQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WorldCupQt w;
	w.show();
	return a.exec();
}
