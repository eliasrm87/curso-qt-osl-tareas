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
    void loadCategorias();
    void loadTareas();
    void loadEtiquetas();

    // Tareas
    void setFilaTareas(int fila);
    int getFilaTareas();
    void setColTareas(int col);
    int getColTareas();

private slots:

    void onAddTarea();
    void onTareaTxtChanged(); // Si cambias el texto de la descripción de una tarea, se actualiza en la base de datos

    void onAddCateg(); // Añade una fila para rellenar una nueva categoria
    void onSaveCateg(int fila, int col); // Guarda en la base de datos los cambios realizados en las categorias

    void onAddEtiq();

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

    // Filas y columnas (globales)
    int filaTareas_, colTareas_;
};

#endif // MAINWINDOW_H
