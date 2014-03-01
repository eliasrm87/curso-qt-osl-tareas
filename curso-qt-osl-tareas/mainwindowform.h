#ifndef MAINWINDOWFORM_H
#define MAINWINDOWFORM_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "dbconnection.h"

namespace Ui {
class MainWindowForm;
}

class MainWindowForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForm(QWidget *parent = 0);
    ~MainWindowForm();

private:
    Ui::MainWindowForm *ui;
    QSqlDatabase db_;
};

#endif // MAINWINDOWFORM_H
