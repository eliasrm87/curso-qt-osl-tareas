#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dbconnection.h"
#include "addcategorydialog.h"

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
    void onAddEtiqueta();

    void onLoadTareas();
    void onLoadCategorias();
    void onLoadEtiquetas();

    void onTareasCellChanged(int row, int column);
    void onSelectCell(int row, int column);
    void onTareaDescrChanged();

    void onCreateCategoria(QString cat);
    void onCreateEtiqueta(QString etq);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;

    AddCategoryDialog* cat_dialog_;
    AddCategoryDialog* label_dialog_;
};

#endif // MAINWINDOW_H
