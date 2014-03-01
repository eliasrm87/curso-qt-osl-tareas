#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Setup database
    ConecToDb(db_, "otra");

    db_.exec("CREATE TABLE IF NOT EXISTS TAREAS ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "name TEXT,"
                  "date TEXT,"
                  "descripcion TEXT,"
                  "done INT"
                  ");");

    //Parte de la tabla, para poder mostrar de manera rápida
    tabla_ = new QTableWidget(this);
    tabla_->setColumnCount(4);
    QStringList labels;
    labels << tr("Nombre") << tr("Fecha") << tr("Descripción") << tr("Hecha");
    tabla_->setHorizontalHeaderLabels(labels);
    setCentralWidget(tabla_);

    //Barra de herramientas
    barHerramientas_ = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, barHerramientas_);

    //Boton de buscar
    QIcon icoBuscar (":/new/prefix1/img/buscar.png");
    actBuscar_ = new QAction(icoBuscar, "&Buscar", this);
    barHerramientas_->addAction(actBuscar_);
    connect(actBuscar_, SIGNAL(triggered()), this, SLOT(alBuscar()));

    //Boton de añadir
    QIcon icoAnadir (":/new/prefix1/img/add.png");
    actAnadir_ = new QAction(icoAnadir, "&Añadir", this);
    barHerramientas_->addAction(actAnadir_);
    connect(actAnadir_, SIGNAL(triggered()), this, SLOT(alAnadir()));
    alBuscar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::alBuscar() {
    while (tabla_->rowCount() > 0) {
        tabla_->removeRow(0);
    }

    QSqlQuery query(db_);
    if (query.exec("SELECT * FROM TAREAS")) {
        int cont = 0;
        while (query.next()) {
          tabla_->insertRow(cont);
          tabla_->setItem(cont, 0, new QTableWidgetItem(query.value(1).toString()));
          tabla_->setItem(cont, 1, new QTableWidgetItem(query.value(2).toString()));
          tabla_->setItem(cont, 2, new QTableWidgetItem(query.value(3).toString()));
          tabla_->setItem(cont, 3, new QTableWidgetItem(query.value(4).toString()));
          cont++;
        }
    }

}

void MainWindow::alAnadir() {
    JDialog* dialogo = new JDialog();
    connect(dialogo, SIGNAL(anadido(QString, QString, QString, QString)), this, SLOT(anadir(QString,QString,QString,QString)));
    dialogo->exec();
}

void MainWindow::anadir(QString nombre, QString fecha, QString descripcion, QString hecha) {
    QString instruccion("INSERT INTO TAREAS VALUES (null,");
    instruccion += "'" + nombre + "',";
    instruccion += "'" + fecha + "',";
    instruccion += "'" + descripcion + "',";
    instruccion += hecha + ")";
    db_.exec(instruccion);
    alBuscar();
}
