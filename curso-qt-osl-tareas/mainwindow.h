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

    // Tareas
    void onAddTarea();
    void onTareasCellChanged(int row, int column);
    void onLoadTareas();

    // Etiquetas
    void onAddEtiqueta();
    void onEtiquetasCellChanged(int row, int column);

    // Categorias
    void onAddCategoria();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;
    bool addingEtiqueta_;
    bool addingCategoria_;

    // Construye la base de datos
    void createTables();
    void populateTables();
};

#endif // MAINWINDOW_H
