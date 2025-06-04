#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>
#include "Service.h"
#include <QVBoxLayout>

class DisplayWindow : public QWidget {
    Q_OBJECT

private:
    Service& service;
    QListWidget* dog_list;
    QPushButton* close_button;
    QComboBox* display_mode;

    void populate_list(bool detailed) {
        dog_list->clear();
        for (const auto& dog : service.get_all_dogs()) {
            if (detailed)
                dog_list->addItem(QString::fromStdString(dog.to_string()));
            else
                dog_list->addItem(QString::fromStdString(dog.get_name() + " " + dog.get_breed()));
        }
    }

public:
    DisplayWindow(Service& service) : service(service) {
        dog_list = new QListWidget(this);
        close_button = new QPushButton("Close", this);
        display_mode = new QComboBox(this);
        display_mode->addItem("Detailed");
        display_mode->addItem("Short");
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(display_mode);
        layout->addWidget(dog_list);
        layout->addWidget(close_button);
        setLayout(layout);
        populate_list(true);
        connect(display_mode, &QComboBox::currentTextChanged, this, [=](const QString& mode) {
            populate_list(mode == "Detailed");
            });

        connect(close_button, &QPushButton::clicked, this, &QWidget::close);
    }
};

