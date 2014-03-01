#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "dbconnection.h"

#include <QDebug>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calendar__selectionChanged();
    void onCurrentDay();
    void onUpdate();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
};

#endif // MAINWINDOW_
