#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>

class AddDogWindow : public QWidget {
    Q_OBJECT
private:
    Service& service;
    QLineEdit* name_input;
    QLineEdit* breed_input;
    QLineEdit* age_input;
    QLineEdit* photograph_input;
    QPushButton* add_button;

public:
    AddDogWindow(Service& s) : service(s) {
        name_input = new QLineEdit;
        breed_input = new QLineEdit;
        age_input = new QLineEdit;
        photograph_input = new QLineEdit;
        add_button = new QPushButton("Add Dog");
        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("Name:", name_input);
        formLayout->addRow("Breed:", breed_input);
        formLayout->addRow("Age:", age_input);
        formLayout->addRow("Photograph URL:", photograph_input);
        formLayout->addWidget(add_button);
        setLayout(formLayout);
        setWindowTitle("Add New Dog");
        connect(add_button, &QPushButton::clicked, this, &AddDogWindow::add_dog);
    }

private slots:
    void add_dog() {
        QString name = name_input->text();
        QString breed = breed_input->text();
        int age = age_input->text().toInt();
        QString photograph = photograph_input->text();
        if (name.isEmpty() || breed.isEmpty() || age <= 0 || photograph.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill in all fields correctly.");
            return;
        }
        try {
            Dog dog(breed.toStdString(), name.toStdString(), age, photograph.toStdString());
            service.add_dog(dog);
            emit dog_added();
            QMessageBox::information(this, "Success", "Dog added successfully!");
            close();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
signals:
    void dog_added();

};
