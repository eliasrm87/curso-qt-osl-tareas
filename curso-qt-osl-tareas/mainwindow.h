#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <dbconnection.h>
#include <QCheckBox>

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
    bool  addingTarea_;
    bool addingCategoria_;

private slots:
    void onAddTarea();
    void onAddCategoria();
    void onGuardaTarea();
    void onGuardaCategoria(int row,int col);


};

#endif // MAINWINDOW_H
