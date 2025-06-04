#include "AdminGui.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <QMessageBox>
#include "AddDogWindow.h"
#include "DeleteDogWindow.h"
#include "UpdateDogWindow.h"
#include "DisplayWindow.h"
#include <QKeySequence>
GUI::GUI(Service& s) : service(s)
{
	initGUI();
}

void GUI::initGUI()
{
	QAction* undo_action = new QAction("Undo", this);
	undo_action->setShortcut(QKeySequence::Undo);
	connect(undo_action, &QAction::triggered, this, &GUI::undo_handler);
	QAction* redo_action = new QAction("Redo", this);
	redo_action->setShortcut(QKeySequence::Redo);
	connect(redo_action, &QAction::triggered, this, &GUI::redo_handler);
	dog_list = new QListWidget();
	add_button = new QPushButton("Add new dog");
	remove_button = new QPushButton("Remove a dog");
	update_button = new QPushButton("Update a dog");
	exit_button = new QPushButton("Exit");
	display_all_button = new QPushButton("Display all dogs");
	undo = new QPushButton("Undo");
	redo = new QPushButton("Redo");
	QVBoxLayout* main_layout = new QVBoxLayout();
	main_layout->addWidget(add_button);
	main_layout->addWidget(remove_button);
	main_layout->addWidget(update_button);
	main_layout->addWidget(display_all_button);
	main_layout->addWidget(undo);
	main_layout->addWidget(redo);
	main_layout->addWidget(exit_button);
	populate_list();
	connect(add_button, &QPushButton::clicked, this, &GUI::add_button_handler);
	connect(remove_button, &QPushButton::clicked, this, &GUI::delete_button_handler);
	connect(update_button, &QPushButton::clicked, this, &GUI::update_button_handler);
	connect(display_all_button, &QPushButton::clicked, this, &GUI::display_button_handler);
	connect(undo, &QPushButton::clicked, this, &GUI::undo_handler);
	connect(redo, &QPushButton::clicked, this, &GUI::redo_handler);
	connect(exit_button, &QPushButton::clicked, this, &QWidget::close);
	addAction(undo_action);
	addAction(redo_action);
	setLayout(main_layout);
}

void GUI::populate_list()
{
	dog_list->clear();
	for (const auto& dog : service.get_all_dogs()) {
		dog_list->addItem(QString::fromStdString(dog.to_string()));
	}
}

void GUI::add_button_handler()
{
	AddDogWindow* add_window = new AddDogWindow(service);
	connect(add_window, &AddDogWindow::dog_added, this, &GUI::populate_list);
	add_window->show();
	populate_list();
}

void GUI::delete_button_handler()
{
	DeleteDogWindow* delete_window = new DeleteDogWindow(service);
	connect(delete_window, &DeleteDogWindow::dog_deleted, this, &GUI::populate_list);
	delete_window->show();
	populate_list();
}

void GUI::update_button_handler()
{
	UpdateDogWindow* update_window = new UpdateDogWindow(service);
	connect(update_window, &UpdateDogWindow::dog_updated, this, &GUI::populate_list);
	update_window->show();
	populate_list();
}

void GUI::display_button_handler()
{
	DisplayWindow* display_window = new DisplayWindow(service);
	display_window->setWindowTitle("Display Dogs");
	display_window->show();
}

void GUI::undo_handler()
{
	try {
		service.undo();
		QMessageBox::information(this, "Undo", "Last action undone successfully.");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Undo error", e.what());
	}
}

void GUI::redo_handler()
{
	try {
		service.redo();
		QMessageBox::information(this, "Redo", "Last action redone successfully.");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Redo error", e.what());
	}
}
