#pragma once
#include <QAbstractTableModel>
#include "Domain.h"

class AdoptionListView : public QAbstractTableModel {
	Q_OBJECT
private:
	std::vector<Dog> adopted_dogs;
public:
	AdoptionListView(QObject* parent) : QAbstractTableModel(parent) {}
	void set_dogs(const std::vector<Dog>& dogs);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

