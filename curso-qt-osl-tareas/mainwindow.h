#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QStringList>
#include <jdialog.h>
#include "dbconnection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSqlDatabase db_;
    QTableWidget* tabla_;
    QToolBar* barHerramientas_;
    QAction* actBuscar_;
    QAction* actAnadir_;

signals:


private slots:
    void alBuscar();
    void alAnadir();
    void anadir(QString nombre, QString fecha, QString descripcion, QString hecha);

};

#endif // MAINWINDOW_H
