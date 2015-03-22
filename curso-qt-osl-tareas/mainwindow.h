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
    void onCategoriasCellChanged(int row, int column);
    void onLoadCategorias();
    void onAddEtiqueta();
    void onEtiquetasCellChanged(int row, int column);
    void onLoadEtiquetas();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;
    bool addingCategoria_;
    bool addingEtiqueta_;
};

#endif // MAINWINDOW_H
