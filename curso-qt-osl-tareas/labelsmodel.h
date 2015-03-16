#ifndef LABELSMODEL_H
#define LABELSMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class LabelsModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit LabelsModel(QObject *parent = 0);

  QStringList stringList() const;
  void setStringList(const QStringList& strings);

  bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex & index) const;

  void addLabel(const QString& labelName, Qt::CheckState checked, QVariant id);

private:
  QStringList strings_;
  QVector<Qt::CheckState> checked_;

};

#endif // LABELSMODEL_H
