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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;
    bool addingCategoria_;
    bool addingEtiqueta_;

private slots:
    void addTarea();
    void addCategoria();
    void addEtiqueta();
    void onTareasCellChanged(int row, int column);
    void onCategoriasCellChanged(int row, int column);

    void onLoadTareas();
    void onLoadCategorias();
    void onLoadEtiquetas();
};

#endif // MAINWINDOW_H
