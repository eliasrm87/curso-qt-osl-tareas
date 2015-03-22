/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Gestor de Tareas - Curso de QT
 *
 * */


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCoreApplication::setOrganizationName("ARB");
    QCoreApplication::setOrganizationDomain("ARB.es");
    QCoreApplication::setApplicationName("curso-qt-osl-tareas");

    w.showMaximized();

    return a.exec();
}
