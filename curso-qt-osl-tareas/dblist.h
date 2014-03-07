#ifndef DBLIST_H
#define DBLIST_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QCheckBox>
#include <QList>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>
#include "dbconnection.h"

class dblist : public QWidget
{
    Q_OBJECT

private:
    QTableView* tableView_;
    QStandardItemModel* model_;
    QGridLayout* layout_;

    QLabel* nameTarea_;
    QLabel* dateTarea_;
    QLabel* categoryTarea_;
    QLabel* categoryDescrTarea_;
    QLabel* tagTitle_;
    QCheckBox* checkTarea_;
    QListView* tagsView_;

    QSqlDatabase db_;

public:
    explicit dblist(QSqlDatabase db, QWidget *parent = 0);

signals:
private slots:
    void clicked(const QModelIndex & index);
public slots:
    void onLoad();
};

#endif // DBLIST_H
