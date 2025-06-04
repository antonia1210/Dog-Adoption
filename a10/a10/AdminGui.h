#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QListWidget* dog_list;
	QLineEdit* name_input;
	QLineEdit* breed_input;
	QLineEdit* age_input;
	QLineEdit* photograph_input;
	QPushButton* add_button;
	QPushButton* remove_button;
	QPushButton* update_button;
	QPushButton* display_all_button;
	QPushButton* exit_button;
	QPushButton* undo;
	QPushButton* redo;

public:
	GUI(Service& s);
	void initGUI();
	void populate_list();
	void add_button_handler();
	void delete_button_handler();
	void update_button_handler();
	void display_button_handler();
	void undo_handler();
	void redo_handler();
};