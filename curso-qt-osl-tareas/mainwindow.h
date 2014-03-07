#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnection.h"
#include <QRect>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db_;
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QMenu* mnuAyuda_;
    QMenu* mnuAyudaDoc_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoCerrar_;
    QAction* actAyudaDocumentacion_;
    QAction* actAyudaAcercaDe_;
    bool addingTarea_;
    bool addingCategoria_;
    bool addingEtiqueta_;

private slots:
    void set_central_win();
    void Cargar();
    void Guardar();
    void Cerrar();
    void Documentacion();
    void abrirURL();
    void AcercaDe();
    void onAddTarea();
    void onAddCategoria();
    void onAddEtiqueta();
    void onTareasCellChanged(int row);
    void onCategoriasCellChanged(int row);
    void onEtiquetasCellChanged(int row);
    void onLoadTareas();
    void onLoadCategorias();
    void onLoadEtiquetas();
    void onDescriptionTask(int row, int col);
    void onEtiquetasTask(int row, int col);
    void initTableEtiquetas();
};

#endif // MAINWINDOW_H
