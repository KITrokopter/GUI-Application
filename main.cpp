#include "mainwindow.hpp"
#include <QApplication>

#include "API.hpp"

int main(int argc, char *argv[])
{
	kitrokopter::API api(argc, argv);

	QApplication a(argc, argv);
	MainWindow w(NULL, &api);
	w.show();
	w.initializeIrrlicht();

	return a.exec();
}

