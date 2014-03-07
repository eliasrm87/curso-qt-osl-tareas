#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup database
    if (!ConecToDb(db_, "tareas")) {
        exit(0);
    } else {
        // Crea las tablas
        createTables();

        // Llena los datos mediante script (no implementado)
        populateTables();

        // Tareas
        connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
        connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int,int)));
        connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));

        // Etiquetas
        connect(ui->actionNuevaEtiq, SIGNAL(triggered()), this, SLOT(onAddEtiqueta()));
        connect(ui->tblEtiq, SIGNAL(cellChanged(int,int)), this, SLOT(onEtiquetasCellChanged(int,int)));

        // Categorías
        connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
        connect(ui->tblCateg, SIGNAL(cellChanged(int,int)), this, SLOT(onCategoriasCellChanged(int,int)));

        addingTarea_ = false;
        addingEtiqueta_ = false;
        addingCategoria_ = false;

        obtenerCategorias();
        obtenerEtiquetas();
        obtenerTareas();
    }
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

void MainWindow::onTareasCellChanged(int row, int column)
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
        db_.commit();
    } else {
        query = db_.exec("UPDATE tareas "
                         "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                         .arg(ui->tblTareas->item(row, 0)->text())\
                         .arg(ui->txtTareaDescr->toPlainText())\
                         .arg(ui->tblTareas->item(row, 1)->text())\
                         .arg(checked)\
                         .arg(ui->comboCategoria->currentData().toInt()) +
                         "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
        db_.commit();
    }

    addingTarea_ = false;
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

void MainWindow::obtenerTareas()
{
    // Obtenemos las tareas
    QSqlQuery r = db_.exec("SELECT * "
                           "FROM tareas;");
    while (r.next()) {

        //Añadimos la tarea a la tabla de tareas
        int rowNumber = ui->tblTareas->rowCount();
        ui->tblTareas->insertRow(rowNumber);

        QTableWidgetItem* item0 = new QTableWidgetItem(GetField(r, "name").toString());
        ui->tblTareas->setItem(rowNumber, 0, item0);

        QTableWidgetItem* item1 = new QTableWidgetItem(GetField(r, "date").toString());
        ui->tblTareas->setItem(rowNumber, 1, item1);

        QTableWidgetItem* item2 = new QTableWidgetItem(GetField(r, "done").toString());
        ui->tblTareas->setItem(rowNumber, 2, item2);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tblTareas->setSortingEnabled(true);
}

void MainWindow::onAddEtiqueta()
{
    addingEtiqueta_ = true;

    ui->tblEtiq->insertRow(ui->tblEtiq->rowCount());
    ui->tblEtiq->setItem(ui->tblCateg->rowCount()-1, 0, new QTableWidgetItem(""));

    addingEtiqueta_ = false;
}

void MainWindow::onEtiquetasCellChanged(int row, int column)
{
    if (addingEtiqueta_)
        return;

    addingEtiqueta_ = true;

    QSqlQuery query;

    if (ui->tblEtiq->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO etiquetas (id, name) "
                         "VALUES ("+QString("'%1','%2');" )\
                         .arg(ui->tblEtiq->item(row, 0)->text())\
                         .arg(ui->tblEtiq->item(row, 1)->text())\
                         .arg(ui->comboEtiqueta->currentData().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE etiquetas "
                         "SET "+QString("id='%1', name='%2' " )\
                         .arg(ui->tblEtiq->item(row, 0)->text())\
                         .arg(ui->tblEtiq->item(row, 1)->text())\
                         .arg(ui->comboEtiqueta->currentData().toInt()) +
                         "WHERE id = " + ui->tblEtiq->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingEtiqueta_ = false;
}

void MainWindow::obtenerEtiquetas()
{
    // Obtenemos las etiquetas
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM etiquetas;");

    while (q.next()) {
        //Añadimos la etiqueta al combo y como userData su ID
        ui->comboEtiqueta->addItem(GetField(q,"name").toString(), GetField(q,"id").toInt());

        //Añadimos la etiqueta a la tabla de etiquetas
        int rowNumber = ui->tblEtiq->rowCount();
        ui->tblEtiq->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        ui->tblEtiq->setItem(rowNumber, 0, item);
    }
    //Activamos el sorting en la tabla de etiquetas
    ui->tblEtiq->setSortingEnabled(true);

    ui->comboEtiqueta->setCurrentIndex(0);
}

void MainWindow::onAddCategoria()
{
    addingCategoria_ = true;

    ui->tblCateg->insertRow(ui->tblCateg->rowCount());
    ui->tblCateg->setItem(ui->tblCateg->rowCount()-1, 0, new QTableWidgetItem(""));

    addingCategoria_ = false;
}

void MainWindow::onCategoriasCellChanged(int row, int column)
{
    if (addingCategoria_)
        return;

    addingCategoria_ = true;

    QSqlQuery query;

    if (ui->tblCateg->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO categorias (id, name, description) "
                         "VALUES ("+QString("'%1','%2','%3');" )\
                         .arg(ui->tblCateg->item(row, 0)->text().toInt())\
                         .arg(ui->tblCateg->item(row, 1)->text())\
                         .arg(ui->txtCategDescr->toPlainText()));

        ui->tblCateg->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
        db_.commit();
    } else {
        query = db_.exec("UPDATE categorias "
                         "SET "+QString("id='%1', name='%2', description='%3' " )\
                         .arg(ui->tblCateg->item(row, 0)->text().toInt())\
                         .arg(ui->tblCateg->item(row, 1)->text())\
                         .arg(ui->txtCategDescr->toPlainText()) +
                         "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
        db_.commit();
    }

    addingCategoria_ = false;
}

void MainWindow::obtenerCategorias()
{
    // Obtenemos las categorias
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

void MainWindow::createTables()
{
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
}

void MainWindow::populateTables()
{
    // Inserta datos en la tabla
}
