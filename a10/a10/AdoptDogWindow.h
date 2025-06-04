#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "Domain.h"
#include "Service.h"
#include <QMessageBox>
#include <QBuffer>
#include <QDesktopServices>
#include <QUrl>


class AdoptDogWindow : public QWidget {
	Q_OBJECT
private:
	Service& service;
	std::vector<Dog> dogs;
	int current_index;
	QLabel* dog_info_label;
	QPushButton* adopt_button;
	QPushButton* next_button;
	QPushButton* exit_button;
public:
	AdoptDogWindow(Service& s) :service(s) {
		dogs = service.get_all_dogs();
		dog_info_label = new QLabel(this);
		adopt_button = new QPushButton("Adopt", this);
		next_button = new QPushButton("Next", this);
		exit_button = new QPushButton("Exit", this);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(dog_info_label);
		layout->addWidget(adopt_button);
		layout->addWidget(next_button);
		layout->addWidget(exit_button);
		connect(adopt_button, &QPushButton::clicked, this, &AdoptDogWindow::adopt_dog);
		connect(next_button, &QPushButton::clicked, this, &AdoptDogWindow::next_dog);
		connect(exit_button, &QPushButton::clicked, this, &QWidget::close);
		display_dog();
	}
	void display_dog() {
		if (dogs.empty()) {
			dog_info_label->setText("No more dogs available for adoption.");
			return;
		}
		const Dog& dog = dogs[current_index];
		std::string photo = dog.get_photograph();
		QUrl url(QString::fromStdString(photo));
		QDesktopServices::openUrl(url);
		dog_info_label->setText(QString::fromStdString(dog.get_name() + ", " + dog.get_breed() + " ,age " + std::to_string(dog.get_age())));

	}
	void adopt_dog() {
		if (dogs.empty()) return;
		service.add_dog_to_adoption_list(dogs[current_index]);
		QMessageBox::information(this, "Adopted", "You adopted this dog!");
		dogs.erase(dogs.begin() + current_index);
		if (current_index >= dogs.size()) {
			current_index = 0;
		}
		display_dog();
	}
	void next_dog() {
		if (dogs.empty()) return;
		current_index = (current_index + 1) % dogs.size();
		display_dog();
	}

};
