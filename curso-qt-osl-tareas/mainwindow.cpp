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
    connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int)));
    connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadCategorias()));
    connect(ui->comboEtiqueta, SIGNAL(currentIndexChanged(int)), this,SLOT(onLoadEtiquetas()));


    //cagetorias
    connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
   // connect(ui->tblCateg, SIGNAL(cellChanged(int,int)), this, SLOT(on)

    addingTarea_ = false;

    //Obtenemos las categorias
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM categorias;");

    while (q.next()) {
        //Añadimos la categoria al combo y como userData su ID
        ui->comboCategoria->addItem(GetField(q,"name").toString(), GetField(q,"id").toInt());

        //Añadimos la categoria a la tabla de categorias
        int rowNumber = ui->tblCateg->rowCount();
        ui->tblCateg->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        ui->tblCateg->setItem(rowNumber, 0, item);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tblCateg->setSortingEnabled(true);

    ui->comboCategoria->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddTarea()
{
    addingTarea_ = true;

    ui->tblTareas->insertRow(ui->tblTareas->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 2, item);

    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblTareas->setItem(ui->tblTareas->rowCount()-1, 1, new QTableWidgetItem(""));


    addingTarea_ = false;
}


//añado categorias
void MainWindow::onAddCategoria(){

    addingCategoria_ = true;

    ui->tblCateg->insertRow(ui->tblCateg->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 2, item);

    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblTareas->setItem(ui->tblCateg->rowCount()-1, 1, new QTableWidgetItem(""));


    addingCategoria_ = false;

}


void MainWindow::onTareasCellChanged(int row)
{
    if (addingTarea_)
        return;

    addingTarea_ = true;

    int checked = (ui->tblTareas->item(row, 2)->checkState() == Qt::Checked);

    QSqlQuery query;

    if (ui->tblTareas->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, id_categ) "
                 "VALUES ("+QString("'%1','%2','%3','%4','%5');" )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()) +
                 "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingTarea_ = false;
}


// ESTAMOS AKI MODIFICAR Y ADAPTAR A CATEGORIA

void MainWindow::onCategoriasCellChanged(int row)
{
    if (addingCategoria_)
        return;

    addingCategoria_ = true;

    int checked = (ui->tblCateg->item(row, 2)->checkState() == Qt::Checked);


    QSqlQuery query;

    if (ui->tblCateg->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO categorias (name, descripcion, date, done, id_categ) "
                 "VALUES ("+QString("\"%1\",\"%2\",\"%3\",\"%4\",\"%5\");" )\
                 .arg(ui->tblCateg->item(row, 0)->text())\
                 .arg(ui->tblCateg->item(row, 1)->text())\
                 .arg(ui->tblCateg->item(row, 2)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()));
        ui->tblCateg->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name=\"%1\",descripcion=\"%2\",date=\"%3\",done=\"%4\",id_categ=\"%5\" " )\
                 .arg(ui->tblCateg->item(row, 0)->text())\
                 .arg(ui->tblCateg->item(row, 1)->text())\
                 .arg(ui->tblCateg->item(row, 2)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()) +
                 "WHERE id = " + ui->tblCateg->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingCategoria_ = false;
}




void MainWindow::onLoadTareas()
{
    addingTarea_ = true;

    while (ui->tblTareas->rowCount())
        ui->tblTareas->removeRow(0);

    //Obtenemos las tareas
    QSqlQuery q = db_.exec("SELECT * "
                 "FROM tareas "
                 "WHERE id_categ = " + ui->comboCategoria->currentData().toString());

    while (q.next()) {
        //Añadimos la tarea a la tabla de categorias
        int rowNumber = ui->tblTareas->rowCount();
        int id = GetField(q, "id").toInt();
        ui->tblTareas->insertRow(rowNumber);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        item->setData(Qt::UserRole, id);
        ui->tblTareas->setItem(rowNumber, 0, item);

        ui->tblTareas->setItem(rowNumber, 1, new QTableWidgetItem(GetField(q, "date").toString()));

        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done").toInt())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tblTareas->setItem(rowNumber, 2, item);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tblTareas->setSortingEnabled(true);
    addingTarea_ = false;
}


void MainWindow::onLoadCategorias()
{
    addingCategoria_ = true;

    while (ui->tblCateg->rowCount())
        ui->tblCateg->removeRow(0);

    //Obtenemos las tareas
    QSqlQuery q = db_.exec("SELECT * "
                 "FROM categorias ");

    while (q.next()) {
//        //Añadimos la tarea a la tabla de categorias
       int rowNumber = ui->tblCateg->rowCount();
        int id = GetField(q, "id").toInt();
//        ui->tblCateg->insertRow(rowNumber);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        item->setData(Qt::UserRole, id);
        ui->tblCateg->setItem(rowNumber, 0, item);

        ui->tblCateg->setItem(rowNumber, 1, new QTableWidgetItem(GetField(q, "descripcion").toString()));

        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done").toInt())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tblCateg->setItem(rowNumber, 2, item);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tblCateg->setSortingEnabled(true);
    addingCategoria_ = false;
}


void MainWindow::onAddEtiquetas(){

    addingEtiqueta_ = true;

    ui->tblEtiq->insertRow(ui->tblEtiq->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 2, item);

    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tblEtiq->setItem(ui->tblEtiq->rowCount()-1, 1, new QTableWidgetItem(""));


    addingEtiqueta_ = false;

}
