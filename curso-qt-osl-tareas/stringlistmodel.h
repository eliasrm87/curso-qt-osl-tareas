#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVariant>
#include <QVector>

class StringListModel: public QAbstractListModel {
  Q_OBJECT

public:
  explicit StringListModel(QObject *parent = 0);

  QStringList stringList() const;

  bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QVariant data(const QModelIndex& index, int role) const;
  bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

private:
  QStringList stringList_;
  QVector<QVariant> userData_;

};

#endif // STRINGLISTMODEL_H
