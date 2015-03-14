#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dbconnection.h"

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
    void onTareasCellChanged(int row, int column);
    void onLoadTareas();

    void onAddCategoria();
    void onAddComboCategorias();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;

    bool addingCateg_;
};

#endif // MAINWINDOW_H
