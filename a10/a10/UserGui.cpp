#include "UserGui.h"
#include <qboxlayout.h>
#include "AdoptDogWindow.h"
#include "AdoptedDogWindow.h"
#include "ShowFilteredDogsWindow.h"
#include <QDesktopServices>
#include <QUrl>
#include "CSVFileRepository.h"
#include "HTMLFileRepository.h"
#include "Table.h"
UserGUI::UserGUI(Service& s) :service(s)
{
	initUserGUI();
}

void UserGUI::initUserGUI()
{
	adopted_dog_list = new QListWidget();
	adopt_button = new QPushButton("Adopt a dog");
	show_adopted_button = new QPushButton("Show adopted dogs");
	show_of_breed = new QPushButton("Show dogs of a breed, having an age less than a given number");
	show_in_csv_file = new QPushButton("Show adopted dogs in CSV file");
	show_in_html_file = new QPushButton("Show adopted dogs in HTML file");
	show_in_table = new QPushButton("Show adoption list in table model");
	exit_button = new QPushButton("Exit");
	QVBoxLayout* main_layout = new QVBoxLayout();
	main_layout->addWidget(adopt_button);
	main_layout->addWidget(show_adopted_button);
	main_layout->addWidget(show_in_csv_file);
	main_layout->addWidget(show_in_html_file);
	main_layout->addWidget(show_of_breed);
	main_layout->addWidget(show_in_table);
	main_layout->addWidget(exit_button);
	populate_list();
	connect(adopt_button, &QPushButton::clicked, this, &UserGUI::adopt_button_handler);
	connect(show_adopted_button, &QPushButton::clicked, this, &UserGUI::show_adopted_button_handler);
	connect(show_of_breed, &QPushButton::clicked, this, &UserGUI::show_of_breed_handler);
	connect(show_in_csv_file, &QPushButton::clicked, this, &UserGUI::show_in_csv_file_handler);
	connect(show_in_html_file, &QPushButton::clicked, this, &UserGUI::show_in_html_file_handler);
	connect(show_in_table, &QPushButton::clicked, this, &UserGUI::show_in_table_handler);
	connect(exit_button, &QPushButton::clicked, this, &QWidget::close);
	setLayout(main_layout);
}

void UserGUI::populate_list()
{
	adopted_dog_list->clear();
	for (const auto& dog : service.get_adoption_list()) {
		adopted_dog_list->addItem(QString::fromStdString(dog.to_string()));
	}
}

void UserGUI::adopt_button_handler()
{
	AdoptDogWindow* adopt_window = new AdoptDogWindow(service);
	adopt_window->setWindowTitle("Adopt a dog");
	adopt_window->setFixedSize(600, 400);
	adopt_window->show();
}

void UserGUI::show_adopted_button_handler()
{
	auto* show_window = new AdoptedDogWindow(service);
	show_window->setAttribute(Qt::WA_DeleteOnClose);
	show_window->show();
}

void UserGUI::show_of_breed_handler()
{
	auto* filtered_window = new ShowFilteredDogs(service);
	filtered_window->setAttribute(Qt::WA_DeleteOnClose);
	filtered_window->show();
}

void UserGUI::show_in_csv_file_handler()
{
	adopted_dogs = service.get_adoption_list();
	auto* repo = new CSVFileRepository("adopted_dogs.csv");
	Service csv_service(repo);
	for (const auto& dog : adopted_dogs) {
		csv_service.add_dog_to_adoption_list(dog);
	}
	csv_service.save_adoption_list();
	std::string filepath = "C:\\Users\\asus\\source\\repos\\a8-9-antonia1210\\a8-9\\a8-9\\adopted_dogs.csv";
	QString qFilepath = QString::fromStdString(filepath);
	QUrl file_url = QUrl::fromLocalFile(qFilepath);
	QDesktopServices::openUrl(file_url);
}

void UserGUI::show_in_html_file_handler()
{
	adopted_dogs = service.get_adoption_list();
	auto* repo = new HTMLFileRepository("adopted_dogs.html");
	Service html_service(repo);
	for (const auto& dog : adopted_dogs) {
		html_service.add_dog_to_adoption_list(dog);
	}
	html_service.save_adoption_list();
	std::string filepath = "C:\\Users\\asus\\source\\repos\\a8-9-antonia1210\\a8-9\\a8-9\\adopted_dogs.html";
	QString qFilepath = QString::fromStdString(filepath);
	QUrl file_url = QUrl::fromLocalFile(qFilepath);
	QDesktopServices::openUrl(file_url);

}

void UserGUI::show_in_table_handler()
{
	auto* table_window = new Table(service);
	table_window->setWindowTitle("Adoption List");
	table_window->setFixedSize(600, 400);
	table_window->show();
}

