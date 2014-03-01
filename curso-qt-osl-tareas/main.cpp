#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCoreApplication::setOrganizationName("Igeko");
    QCoreApplication::setOrganizationDomain("igeko.es");
    QCoreApplication::setApplicationName("curso-qt-osl-tareas");

    w.showMaximized();

    return a.exec();
}
