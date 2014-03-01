#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbconnection.h>

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

//Añadido por Elias en clase
    private slots:
    void onAddTarea();
    void onTareasCellChanged(int row, int column);
    void onLoadTareas();
// Fin - Añadido por Elias en clase -

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;

};

#endif // MAINWINDOW_H
