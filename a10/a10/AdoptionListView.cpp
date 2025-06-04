#include "AdoptionListView.h"

void AdoptionListView::set_dogs(const std::vector<Dog>& dogs)
{
	beginResetModel();
	adopted_dogs = dogs;
	endResetModel();
}

int AdoptionListView::rowCount(const QModelIndex& parent) const
{
	return adopted_dogs.size();
}

int AdoptionListView::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant AdoptionListView::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return {};
	const Dog& dog = adopted_dogs[index.row()];
	switch (index.column()) {
	case 0: return QString::fromStdString(dog.get_name());
	case 1: return QString::fromStdString(dog.get_breed());
	case 2: return dog.get_age();
	case 3: return QString::fromStdString(dog.get_photograph());
	}
	return {};
}

QVariant AdoptionListView::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return {};
	switch (section) {
	case 0: return "Name";
	case 1: return "Breed";
	case 2: return "Age";
	case 3: return "Photograph URL";
	}
	return {};
}

