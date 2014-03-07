#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dbconnection.h"

#include <QSqlDatabase>

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>

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
    void set_central_win();
    void Cargar();
    void Guardar();
    void Cerrar();
    void Documentacion();
    void abrirURL();
    void AcercaDe();

    void onAddTarea();
    void onTareasCellChanged(int row, int column);
    void onLoadTareas();

private:
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QMenu* mnuAyuda_;
    QMenu* mnuAyudaDoc_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoCerrar_;
    QAction* actAyudaDocumentacion_;
    QAction* actAyudaAcercaDe_;

    Ui::MainWindow *ui;
    QSqlDatabase db_;
    bool addingTarea_;
};

#endif // MAINWINDOW_H
