#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "service.h"

class AdoptedDogWindow : public QWidget {
	Q_OBJECT
private:
	QListWidget* dog_list;
	Service& service;
public:
	AdoptedDogWindow(Service& s) : service(s) {
		setWindowTitle("Adopted Dogs");
		dog_list = new QListWidget(this);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(dog_list);
		setLayout(layout);
		populate_list();
	}
	void populate_list() {
		dog_list->clear();
		for (const auto& dog : service.get_adoption_list()) {
			dog_list->addItem(QString::fromStdString(dog.to_string()));
		}
	}
};