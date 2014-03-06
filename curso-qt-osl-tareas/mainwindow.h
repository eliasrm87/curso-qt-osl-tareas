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
    void loadTareas();

private slots:

    void onAddTarea();
    void onTareasCellChanged(int row, int column);
    void onLoadTareas();
    void showDescriptionCat(int fila, int col); // Muestra descripción de las categorías
    void showDescriptionTarea(int fila, int col); // Muestra descripción de las tareas

private:

    Ui::MainWindow *ui;
    QSqlDatabase db_;

    // Semáforos
    bool addingTarea_;
    bool addingCategoria_;
    bool addingEtiqueta_;
};

#endif // MAINWINDOW_H
