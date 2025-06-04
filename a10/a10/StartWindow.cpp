#include "StartWindow.h"
#include "AdminGui.h"
#include "UserGui.h"
#include <QVBoxLayout>
#include <QMessageBox>

StartWindow::StartWindow(Service& s) : service(s) {
	this->init();
}

void StartWindow::init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	admin_mode = new QPushButton("Administrator Mode");
	admin_mode->setFixedSize(200, 50);
	user_mode = new QPushButton("User Mode");
	user_mode->setFixedSize(200, 50);
	exit_button = new QPushButton("Exit");
	exit_button->setFixedSize(200, 30);
	chart_button = new QPushButton("Show Breed Chart");
	chart_button->setFixedSize(200, 30);
	QHBoxLayout* button_layout = new QHBoxLayout();
	button_layout->addWidget(admin_mode);
	button_layout->setAlignment(Qt::AlignCenter);
	layout->addLayout(button_layout);
	button_layout = new QHBoxLayout();
	button_layout->addWidget(user_mode);
	button_layout->setAlignment(Qt::AlignCenter);
	layout->addLayout(button_layout);
	button_layout = new QHBoxLayout();
	button_layout->addWidget(exit_button);
	button_layout->setAlignment(Qt::AlignCenter);
	layout->addLayout(button_layout);
	button_layout = new QHBoxLayout();
	button_layout->addWidget(chart_button);
	button_layout->setAlignment(Qt::AlignCenter);
	layout->addLayout(button_layout);
	connect(admin_mode, &QPushButton::clicked, this, &StartWindow::launch_admin_mode);
	connect(user_mode, &QPushButton::clicked, this, &StartWindow::launch_user_mode);
	connect(chart_button, &QPushButton::clicked, this, &StartWindow::launch_chart);
	connect(exit_button, &QPushButton::clicked, this, &StartWindow::close);
	this->setLayout(layout);
}
void StartWindow::launch_admin_mode()
{
	auto* admin_window = new GUI(this->service);
	admin_window->setWindowTitle("Administrator Mode");
	admin_window->setFixedSize(600, 400);
	admin_window->show();
}
void StartWindow::launch_user_mode()
{
	auto* user_window = new UserGUI(this->service);
	user_window->setWindowTitle("User Mode");
	user_window->setFixedSize(600, 400);
	user_window->show();
}

void StartWindow::launch_chart()
{
	QMap<QString, int> breedCounts;
	for (const Dog& dog : service.get_all_dogs()) {
		QString breed = QString::fromStdString(dog.get_breed());
		breedCounts[breed]++;
	}
	BarChartWidget* chart = new BarChartWidget(breedCounts);
	chart->setWindowTitle("Dogs per Breed");
	chart->resize(600, 400);
	chart->show();
}


