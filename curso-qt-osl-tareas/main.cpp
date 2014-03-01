#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setOrganizationName("CursoQT");
    QCoreApplication::setApplicationName("curso-qt-osl-tareas");

    w.show();

    return a.exec();
}
