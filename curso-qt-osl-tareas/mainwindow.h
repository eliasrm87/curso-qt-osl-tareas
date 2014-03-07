#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <dbconnection.h>
#include <QCheckBox>
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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;
    bool addingCategoria_;
    bool addingEtiqueta_;
    bool cambiaTarea_;
    void loadCategoria();
    void loadTareas();
    void loadEtiqueta();

private slots:
    void onAddCategoria();
    void onAddEtiqueta();
    void onAddTarea();
    void onGuardaCategoria(int row,int col);
    void onGuardaEtiqueta(int row,int col);
    void onGuardaTarea(int row, int col);
    void cambiaCombo(int);
    void mostrarDesc(int row,int col);


};

#endif // MAINWINDOW_H
