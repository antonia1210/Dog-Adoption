#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>
class DeleteDogWindow : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QLineEdit* name_input;
	QLineEdit* breed_input;
	QPushButton* delete_button;
public:
	DeleteDogWindow(Service& s) :service(s) {
		name_input = new QLineEdit;
		breed_input = new QLineEdit;
		delete_button = new QPushButton("Delete Dog");
		QFormLayout* formLayout = new QFormLayout;
		formLayout->addRow("Name:", name_input);
		formLayout->addRow("Breed:", breed_input);
		formLayout->addWidget(delete_button);
		setLayout(formLayout);
		setWindowTitle("Delete Dog");
		connect(delete_button, &QPushButton::clicked, this, &DeleteDogWindow::delete_dog);
	}
private slots:
	void delete_dog() {
		QString name = name_input->text();
		QString breed = breed_input->text();
		if (name.isEmpty() || breed.isEmpty()) {
			QMessageBox::warning(this, "Error", "Please fill in all fields.");
			return;
		}
		try {
			service.remove_dog(name.toStdString(), breed.toStdString());
			emit dog_deleted();
			QMessageBox::information(this, "Success", "Dog deleted successfully!");
			close();
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
	}
signals:
	void dog_deleted();
};