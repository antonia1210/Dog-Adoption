#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include "Service.h"
class UpdateDogWindow : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QLineEdit* name_input;
	QLineEdit* breed_input;
	QLineEdit* new_age_input;
	QLineEdit* new_photograph_input;
	QLineEdit* new_name_input;
	QLineEdit* new_breed_input;
	QPushButton* update_button;
public:
	UpdateDogWindow(Service& s) :service(s) {
		name_input = new QLineEdit;
		breed_input = new QLineEdit;
		new_age_input = new QLineEdit;
		new_photograph_input = new QLineEdit;
		new_name_input = new QLineEdit;
		new_breed_input = new QLineEdit;
		update_button = new QPushButton("Update Dog");
		QFormLayout* formLayout = new QFormLayout;
		formLayout->addRow("Name:", name_input);
		formLayout->addRow("Breed:", breed_input);
		formLayout->addRow("New Name:", new_name_input);
		formLayout->addRow("New Breed:", new_breed_input);
		formLayout->addRow("New Age:", new_age_input);
		formLayout->addRow("New Photograph URL:", new_photograph_input);
		formLayout->addWidget(update_button);
		setLayout(formLayout);
		setWindowTitle("Update Dog");
		connect(update_button, &QPushButton::clicked, this, &UpdateDogWindow::update_dog);
	}
private slots:
	void update_dog() {
		QString name = name_input->text();
		QString breed = breed_input->text();
		int new_age = new_age_input->text().toInt();
		QString new_photograph = new_photograph_input->text();
		QString new_name = new_name_input->text();
		QString new_breed = new_breed_input->text();
		if (name.isEmpty() || breed.isEmpty()) {
			QMessageBox::warning(this, "Error", "Please fill in the name and the breed fields correctly.");
			return;
		}
		try {
			service.update_dog(name.toStdString(), breed.toStdString(), new_age, new_photograph.toStdString(), new_name.toStdString(), new_breed.toStdString());
			emit dog_updated();
			QMessageBox::information(this, "Success", "Dog updated successfully!");
			close();
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
	}
signals:
	void dog_updated();
};