#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnection.h"
#include <QDebug>

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
    void onAddTarea();
    void onAddCategoria();
    void clicked(const QModelIndex & index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
};

#endif // MAINWINDOW_H
