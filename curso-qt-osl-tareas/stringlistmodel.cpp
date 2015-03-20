#include "stringlistmodel.h"

StringListModel::StringListModel(QObject *parent): QAbstractListModel(parent) {
}

QStringList StringListModel::stringList() const {
  return stringList_;
}

bool StringListModel::insertRows(int row, int count, const QModelIndex& parent) {
  beginInsertRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i)
    stringList_.insert(row, QString());

  userData_.insert(row, count, QVariant());

  endInsertRows();
  return true;
}

bool StringListModel::removeRows(int row, int count, const QModelIndex& parent) {
  beginRemoveRows(parent, row, row + count - 1);

  bool ok = false;
  if (row >= 0 && row < rowCount()) {
    for (int i = 0; i < count; ++i)
      stringList_.removeAt(row);

    userData_.remove(row, count);
    ok = true;
  }

  endRemoveRows();
  return ok;
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role == Qt::DisplayRole) {
    if (section == 0 && orientation == Qt::Horizontal)
      return tr("Categorías");
    else if (orientation == Qt::Vertical)
      return section + 1;
  }

  return QVariant();
}

QVariant StringListModel::data(const QModelIndex& index, int role) const {
  int row = index.row();
  if (row < 0 || row >= rowCount())
    return QVariant();

  switch (role) {
  case Qt::EditRole:
  case Qt::DisplayRole:
    return stringList_.at(row);
  case Qt::UserRole:
    return userData_.at(row);
  }

  return QVariant();
}

bool StringListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
  int row = index.row();
  if (row < 0 || row >= rowCount())
    return false;

  switch (role) {
  case Qt::EditRole:
  case Qt::DisplayRole:
    stringList_[row] = value.toString();
    emit(dataChanged(index, index));
    break;
  case Qt::UserRole:
    userData_[row] = value;
    emit(dataChanged(index, index));
    break;
  }

  return true;
}

int StringListModel::rowCount(const QModelIndex& parent) const {
  return stringList_.length();
}

Qt::ItemFlags StringListModel::flags(const QModelIndex& index) const {
  if (index.row() < 0 || index.row() >= rowCount())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren |
         Qt::ItemIsEditable;
}
