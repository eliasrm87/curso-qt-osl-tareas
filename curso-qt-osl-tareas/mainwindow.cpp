#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
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
              "date TEXT,"
              "done INTEGER,"
              "descripcion TEXT,"
              "Id_cat INTEGER,"
              "Id_et INTEGER"
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
                 "id_et INTEGER"
                 ");");




    connect(ui->actionNuevaCategoria,SIGNAL(triggered()),this,SLOT(onAddCategoria()));
    connect(ui->TablaCategorias,SIGNAL(cellChanged(int,int)),this,SLOT(onGuardaCategoria(int,int)));

    connect(ui->actionNuevaEtiqueta,SIGNAL(triggered()),this,SLOT(onAddEtiqueta()));
    connect(ui->TablaEtiquetas,SIGNAL(cellChanged(int,int)),this,SLOT(onGuardaEtiqueta(int,int)));

    connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->TablaTareas, SIGNAL(cellChanged(int,int)),this,SLOT (onGuardaTarea(int,int)));
    connect(ui->TablaTareas,SIGNAL(cellClicked(int,int)),this,SLOT (mostrarDesc(int,int)));

    connect(ui->comboBoxCategorias,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiaCombo(int)));

    //Señales para que no pete
    addingTarea_ = false;
    addingCategoria_=false;
    addingEtiqueta_=false;
    cambiaTarea_=false;

    loadEtiqueta();
    loadCategoria();
    loadTareas();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCategoria(){
    addingCategoria_=true;
    //Obtenemos las categorias
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM categorias;");
    while (q.next()) {
        ui->comboBoxCategorias->addItem(GetField(q,"name").toString());
        int rowNumber = ui->TablaCategorias->rowCount();
        ui->TablaCategorias->insertRow(rowNumber);
        QTableWidgetItem* itemnombre = new QTableWidgetItem(GetField(q, "name").toString());
        ui->TablaCategorias->setItem(rowNumber, 0, itemnombre);

        QTableWidgetItem* itemdesc = new QTableWidgetItem(GetField(q, "descripcion").toString());
        ui->TablaCategorias->setItem(rowNumber, 1, itemdesc);


    }
     ui->TablaCategorias->setSortingEnabled(true);
    addingCategoria_=false;
}

void MainWindow::loadEtiqueta(){
    addingEtiqueta_=true;
    //Obtenemos las etiquetas
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM etiquetas;");
    while (q.next()) {
        ui->comboBoxEtiqueta->addItem(GetField(q,"name").toString());
        int rowNumber = ui->TablaEtiquetas->rowCount();
        ui->TablaEtiquetas->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        ui->TablaEtiquetas->setItem(rowNumber, 0, item);
    }
     ui->TablaEtiquetas->setSortingEnabled(true);
     addingEtiqueta_=false;

}

void MainWindow::loadTareas(){

    addingTarea_=true;
    QString cadena = ui->comboBoxCategorias->currentText();
    QSqlQuery qC = db_.exec("SELECT * FROM categorias WHERE name=\""+cadena+"\";");
    QSqlQuery qE = db_.exec("SELECT * FROM etiquetas WHERE name='"+ui->comboBoxEtiqueta->currentText()+"';");

    qDebug() << GetField(qC,"id").toString() << " combo: " << ui->comboBoxCategorias->currentText();
    qDebug() << GetField(qE,"id").toString() << " combo: " << ui->comboBoxEtiqueta->currentText();


    QSqlQuery q = db_.exec("SELECT * FROM tareas;"); // WHERE Id_cat="+ GetField(qC,"id").toString()+" AND Id_et="+GetField(qE,"id").toString());

    while (q.next()) {
        int rowNumber = ui->TablaTareas->rowCount();
        ui->TablaTareas->insertRow(rowNumber);

        QTableWidgetItem* itemnombre = new QTableWidgetItem(GetField(q,"name").toString());
        ui->TablaTareas->setItem(rowNumber, 0, itemnombre);

        QTableWidgetItem* itemfecha = new QTableWidgetItem(GetField(q,"date").toString());
        ui->TablaTareas->setItem(rowNumber, 1, itemfecha);
        QTableWidgetItem* itemdone = new QTableWidgetItem("");
        itemdone->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        if (GetField(q,"done") == "0"){
            itemdone->setCheckState(Qt::Unchecked);
        }else{
            itemdone->setCheckState(Qt::Checked);
        }
        ui->TablaTareas->setItem(rowNumber,2,itemdone);
    }
     addingTarea_=false;

}

void MainWindow::onAddCategoria(){
    addingCategoria_ = true;
    ui->TablaCategorias->insertRow(ui->TablaCategorias->rowCount());
    ui->TablaCategorias->setItem(ui->TablaCategorias->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->TablaCategorias->setItem(ui->TablaCategorias->rowCount()-1, 1, new QTableWidgetItem(""));
    addingCategoria_= false;
}

void MainWindow::onAddEtiqueta(){
    addingEtiqueta_ = true;
    ui->TablaEtiquetas->insertRow(ui->TablaEtiquetas->rowCount());
    ui->TablaEtiquetas->setItem(ui->TablaEtiquetas->rowCount()-1, 0, new QTableWidgetItem(""));
    addingEtiqueta_= false;

}

void MainWindow::onAddTarea()
{
    addingTarea_ = true;
    //estructura con las celdas
    ui->TablaTareas->insertRow(ui->TablaTareas->rowCount());
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->TablaTareas->setItem(ui->TablaTareas->rowCount()-1, 2, item);
    ui->TablaTareas->setItem(ui->TablaTareas->rowCount()-1, 1, new QTableWidgetItem(""));
    ui->TablaTareas->setItem(ui->TablaTareas->rowCount()-1, 0, new QTableWidgetItem(""));
    addingTarea_ = false;

}

void MainWindow::onGuardaCategoria(int row,int col)
{
    if (addingCategoria_)
           return;
    addingCategoria_= true;
    //Obtenemos los campos
    QString nombre = ui->TablaCategorias->item(row,0)->text();
    QString desc =ui->TablaCategorias->item(row,1)->text();
    //Insertamos en la base de datos

    if (ui->TablaCategorias->item(row,col)->data(Qt::UserRole).isNull()){
        QString query("INSERT INTO categorias (name, descripcion) VALUES (" +
        QString("'%1','%2'")\
        .arg(nombre)\
        .arg(desc) + ");");
        //Inserta en las Categorias
        db_.exec(query);

    }else{
        QString query("UPDATE categorias SET (name='%1', descripcion='%2') WHERE Id= "+ui->TablaCategorias->item(row,col)->data(Qt::UserRole).toString());
        //Actualiza las Categorias
        db_.exec(query);
    }



    addingCategoria_= false;
}

void MainWindow::onGuardaEtiqueta(int row,int col){
    if (addingEtiqueta_)
               return;
    addingEtiqueta_= true;
    //Obtenemos los campos
    QString nombre = ui->TablaEtiquetas->item(row,0)->text();
    //Insertamos en la base de datos

    QString query("INSERT INTO etiquetas (name) VALUES (" +
                  QString("'%1'")\
                  .arg(nombre)+ ");");
   //Inserta en las Etiquetas
    db_.exec(query);
    addingEtiqueta_= false;
}

void MainWindow::onGuardaTarea(int row,int col){
   if (addingTarea_)
           return;
     addingTarea_ = true;
     int checked = (ui->TablaTareas->item(row,2)->checkState()==Qt::Checked);

    //Insertar la tarea en la base de datos
     QSqlQuery query;
     if(ui->TablaTareas->item(row,col)->data(Qt::UserRole).isNull()){

         query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, Id_cat,Id_et) "
                         "VALUES ("+QString("'%1','%2','%3','%4','%5','%6');" )\
                         .arg(ui->TablaTareas->item(row, 0)->text())\
                         .arg(ui->TextDescripcion->toPlainText())\
                         .arg(ui->TablaTareas->item(row, 1)->text())\
                         .arg(checked)\
                         .arg(ui->comboBoxCategorias->currentData().toInt())\
                         .arg(ui->comboBoxEtiqueta->currentData().toInt()));

                ui->TablaTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
            } else {
                query = db_.exec("UPDATE tareas "
                         "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5',Id_et'%6'" )\
                         .arg(ui->TablaTareas->item(row, 0)->text())\
                         .arg(ui->TextDescripcion->toPlainText())\
                         .arg(ui->TablaTareas->item(row, 1)->text())\
                         .arg(checked)\
                         .arg(ui->comboBoxCategorias->currentData().toInt())\
                         .arg(ui->comboBoxEtiqueta->currentData().toInt()) +
                         "WHERE id = " + ui->TablaTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
            }

            addingTarea_ = false;
}

void MainWindow::cambiaCombo(int) //Si cambiamos la opcion nos muestra las elegidas
{
    if (cambiaTarea_)
               return;

    cambiaTarea_=true;

    //ui->TablaTareas->clear();//borra pero mantiene la estructura y hace run load de tareas repite
    //ui->TablaTareas->destroyed();
    //loadTareas();
    cambiaTarea_=false;

}

void MainWindow::mostrarDesc(int row,int col)
{
    QSqlQuery q=db_.exec("SELECT * FROM tareas;");
    q.seek(row);
    ui->TextDescripcion->setText(GetField(q,"descripcion").toString());

}


