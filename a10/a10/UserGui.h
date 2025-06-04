#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class UserGUI : public QWidget {
	Q_OBJECT
private:
	Service& service;
	std::vector<Dog> adopted_dogs;
	QListWidget* adopted_dog_list;
	QPushButton* adopt_button;
	QPushButton* show_adopted_button;
	QPushButton* show_of_breed;
	QPushButton* show_in_csv_file;
	QPushButton* show_in_html_file;
	QPushButton* show_in_table;
	QPushButton* exit_button;

public:
	UserGUI(Service& s);
	void initUserGUI();
	void populate_list();
	void adopt_button_handler();
	void show_adopted_button_handler();
	void show_of_breed_handler();
	void show_in_csv_file_handler();
	void show_in_html_file_handler();
	void show_in_table_handler();
};