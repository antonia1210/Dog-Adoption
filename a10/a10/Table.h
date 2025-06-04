#pragma once
#include <QWidget>
#include <QTableView>
#include "AdoptionListView.h"
#include "Service.h"
#include <QHeaderView>
#include <QVBoxLayout>

class Table : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QTableView* table;
	AdoptionListView* adoption_list_view;
public:
	Table(Service& service): service(service) {
		setWindowTitle("Table adoption list");
		adoption_list_view = new AdoptionListView(this);
		adoption_list_view->set_dogs(service.get_adoption_list());
		table = new QTableView(this);
		table->setModel(adoption_list_view);
		table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(table);
		setLayout(layout);
	}

};