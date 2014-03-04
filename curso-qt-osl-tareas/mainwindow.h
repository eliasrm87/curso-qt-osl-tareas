#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtDebug>
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
    void onTareasCellChanged(int row);
    void onCategoriasCellChanged(int row);
    void onEtiquetasCellChanged(int row);
    void onLoadTareas();
    void onLoadCategorias();
    void onLoadEtiquetas();
    void onDescriptionTask(int row, int col);
};

#endif // MAINWINDOW_H
