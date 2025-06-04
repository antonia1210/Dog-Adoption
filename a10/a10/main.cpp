#include "StartWindow.h"
#include "Service.h"
#include "TextFileRepository.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	auto* repo = new TextFileRepository("dogs.txt");
	Service service(repo);
	StartWindow start_window(service);
	start_window.setWindowTitle("Dog Adoption");
	start_window.setFixedSize(600, 400);
	start_window.show();
    return app.exec();
}
