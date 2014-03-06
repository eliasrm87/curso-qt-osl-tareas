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
#include <QHeaderView>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QSignalMapper>
#include <QAction>


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

    QSqlQuery q_cat;
    QSqlQuery q_tar;
    QSqlQuery q_etiq;


    QWidget* wgtMain_;
    QGridLayout* lytMain_;

    bool catModif_;
    bool editar_;
    bool desc_tarea_;

    int row_act_;
    int col_act_;

    int id_cat_act_;

private slots:
    void verDescripcion(int row, int col);
    void guardarContenido(int row, int col);
    void cambiaCategoria (QString cat);
    void mostrarCategorias();
    void mostrarEtiquetas();
    void mostrarTareas();
    void inicializaBD();
    void guardarDescripcion();
};

#endif // MAINWINDOW_H
