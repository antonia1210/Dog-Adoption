#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include "service.h"
class ShowFilteredDogs : public QWidget {
	Q_OBJECT
private:
	QLineEdit* breed_input;
	QSpinBox* age_input;
	QPushButton* filter_button;
	QListWidget* result_list;
	Service& service;
public:
	ShowFilteredDogs(Service& s) : service(s) {
		setWindowTitle("Show Filtered Dogs");
		breed_input = new QLineEdit(this);
		age_input = new QSpinBox(this);
		filter_button = new QPushButton("Filter", this);
		result_list = new QListWidget(this);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(breed_input);
		layout->addWidget(age_input);
		layout->addWidget(filter_button);
		layout->addWidget(result_list);
		setLayout(layout);
		connect(filter_button, &QPushButton::clicked, this, &ShowFilteredDogs::populate_filtered_dogs);
	}
	void populate_filtered_dogs() {
		std::vector<Dog> filtered_dogs = service.filter_dogs(breed_input->text().toStdString(), age_input->value());
		result_list->clear();
		for (const auto& dog : filtered_dogs) {
			result_list->addItem(QString::fromStdString(dog.to_string()));
		}
	}
};