#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup database
    ConecToDb(db_, "tareas");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT,"
              "date TEXT,"
              "done INTEGER,"
              "id_categ INTEGER"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS categorias ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS etiquetas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas_etiq ("
              "id_tarea INTEGER,"
              "id_etiq INTEGER"
              ");");

    connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));

    //OBTENEMOS LAS CATEGORIAS
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM categorias;");

    while (q.next()) {
        //Se añade una categoria al ComboBox

        ui->comboCategoria->addItem(GetField(q,"name").toString());

        int rowNumb = ui->tblCateg->rowCount();
        ui->tblCateg->insertRow(rowNumb);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        ui->tblCateg->setItem(rowNumb, 0, item);
    }
    ui->tblCateg->setSortingEnabled(true);

    //OBTENEMOS LAS ETIQUETAS
    QSqlQuery p = db_.exec("SELECT * "
                           "FROM etiquetas;");

    qDebug()<< GetField(p,"name").toString();
    while (p.next()) {
        //Se añade una etiquetas al ComboBox
        ui->comboEtiqueta->addItem(GetField(p,"name").toString());

        int rowNumb = ui->tblEtiq->rowCount();
        ui->tblEtiq->insertRow(rowNumb);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(p, "name").toString());
        ui->tblEtiq->setItem(rowNumb, 0, item);
    }
    ui->tblEtiq->setSortingEnabled(true);

    //OBTENEMOS LAS TAREAS
    QSqlQuery t = db_.exec("SELECT * "
                           "FROM tareas;");

    qDebug()<< GetField(t,"name").toString();
    while (t.next()) {
        //Se añade una etiquetas a la tabla Tareas
        // ui->tblTareas->addItem(GetField(t,"name").toString());

        int rowNumb = ui->tblTareas->rowCount();
        ui->tblTareas->insertRow(rowNumb);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(t, "name").toString());
        ui->tblTareas->setItem(rowNumb, 0, item);
        item = new QTableWidgetItem(GetField(t, "date").toString());
        ui->tblTareas->setItem(rowNumb, 1, item);

        item = new QTableWidgetItem("Realizado");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);
        ui->tblTareas->setItem(rowNumb, 2, item);
        item = new QTableWidgetItem(GetField(t, "id").toString());
        ui->tblTareas->setItem(rowNumb, 3, item);
        ui->tblTareas->hideColumn(3); //Oculta la columna
    }
    ui->tblTareas->setSortingEnabled(true);

    connect (ui->tblTareas, SIGNAL(clicked(QModelIndex)),this, SLOT(clicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddTarea()
{
    ui->tblTareas->insertRow(ui->tblTareas->rowCount());
}

void MainWindow::onAddCategoria()
{
    /*ui->tblCateg->insertRow(ui->tblCateg->rowCount());
    db_.exec() "INSERT"*/
}

void MainWindow::clicked(const QModelIndex &index)
{
    //qDebug() << ui->tblTareas->item(index.row(),3)->text();
    QString cono = ui->tblTareas->item(index.row(),3)->text();
    QSqlQuery query = db_.exec(QString("SELECT * FROM categorias WHERE id = %1").arg(cono,3));
    //QUE LEA DE LA DESCRIPCCION
}
