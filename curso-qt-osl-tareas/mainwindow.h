#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "dbconnection.h"

#include <QGridLayout>
#include <QTextEdit>
#include <QListWidget>
#include <QStringList>
#include <QCheckBox>
#include <QTableWidget>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QDebug>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSqlDatabase db_;
    QTextEdit* txtEditor_;
    QTableWidget* tareas_;
    QTableWidget* categorias_;
    QTableWidget* etiquetas_;

private slots:
    void verDescripcion(int row, int col);
    void guardarContenido(int row, int col);
};

#endif // MAINWINDOW_H
