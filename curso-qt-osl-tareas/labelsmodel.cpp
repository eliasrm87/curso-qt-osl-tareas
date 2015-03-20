#include "labelsmodel.h"
#include <QDebug>

LabelsModel::LabelsModel(QObject *parent): QAbstractTableModel(parent) {

}

QStringList LabelsModel::stringList() const {
  return strings_;
}

void LabelsModel::setStringList(const QStringList& strings) {
  removeRows(0, rowCount());
  insertRows(0, strings.length());
  for (int i = 0; i < strings.length(); ++i) {
    QModelIndex idx = index(i, 0);
    setData(idx, strings[i]);
    setData(idx, Qt::Unchecked, Qt::CheckStateRole);
  }
}

bool LabelsModel::insertRows(int row, int count, const QModelIndex& parent) {
  beginInsertRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i) {
    strings_.insert(row, "");
    checked_.insert(row, Qt::Unchecked);
    ids_.insert(row, 0);
  }

  endInsertRows();
  return true;
}

bool LabelsModel::removeRows(int row, int count, const QModelIndex& parent) {
  beginRemoveRows(parent, row, row + count - 1);

  bool success = false;
  if (row >= 0 && row + count < rowCount(parent)) {
    for (int i = 0; i < count; ++i) {
      strings_.removeAt(row);
      checked_.removeAt(row);
      ids_.removeAt(row);
    }

    success = true;
  }

  endRemoveRows();
  return success;
}

int LabelsModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid())
    return 0;
  else
    return strings_.length();
}

int LabelsModel::columnCount(const QModelIndex& /*parent*/) const {
  return 1;
}

QVariant LabelsModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount())
    return QVariant();

  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    return strings_.at(index.row());
  case Qt::CheckStateRole:
    return checked_.at(index.row());
  case Qt::UserRole:
    return ids_.at(index.row());
  }

  return QVariant();
}

QVariant LabelsModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role == Qt::DisplayRole) {
    if (section == 0 && orientation == Qt::Horizontal)
      return tr("Etiqueta");
    else if (orientation == Qt::Vertical)
      return section + 1;
  }

  return QVariant();
}

bool LabelsModel::setData(const QModelIndex& index, const QVariant& value, int role) {
  if (index.row() < 0 || index.row() >= rowCount())
    return false;

  switch (role) {
  case Qt::DisplayRole:
  case Qt::EditRole:
    strings_.replace(index.row(), value.toString());
    emit(dataChanged(index, index));
    break;
  case Qt::CheckStateRole:
    checked_[index.row()] = static_cast<Qt::CheckState>(value.toUInt());
    emit(dataChanged(index, index));
    emit(checkChanged(index.row()));
    break;
  case Qt::UserRole:
    ids_[index.row()] = value.toInt();
    emit(dataChanged(index, index));
    break;
  }

  return true;
}

Qt::ItemFlags LabelsModel::flags(const QModelIndex& index) const {
  if (index.row() < 0 || index.row() >= rowCount())
    return Qt::NoItemFlags;

  return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable;
}

void LabelsModel::addLabel(const QString& labelName, Qt::CheckState checked, QVariant id) {
  int rows = rowCount();
  insertRow(rows);

  QModelIndex idx = index(rows, 0);

  setData(idx, labelName);
  setData(idx, checked, Qt::CheckStateRole);
  setData(idx, id, Qt::UserRole);
}
