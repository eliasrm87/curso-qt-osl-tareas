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




    connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->TablaTareas, SIGNAL(cellChanged(int,int)),this,SLOT (onGuardaTarea()));
    connect(ui->actionNuevaCategoria,SIGNAL(triggered()),this,SLOT(onAddCategoria()));
    connect(ui->TablaCategorias,SIGNAL(cellChanged(int,int)),this,SLOT(onGuardaCategoria(int,int)));
    addingTarea_ = false;
    addingCategoria_=false;
    addingEtiqueta_=false;

    loadCategoria();
    loadEtiqueta();
    loadTareas();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCategoria(){
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

}

void MainWindow::loadEtiqueta()
{
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

}

void MainWindow::loadTareas(){

    addingTarea_=true;
    QSqlQuery q = db_.exec("SELECT * "
                           "FROM tareas;");
                            /* WHERE Id_cat = " +ui->comboBoxCategorias->currentText()+ " AND Id_et=" +ui->comboBoxEtiqueta->currentText());*/
   do  {
        int rowNumber = ui->TablaTareas->rowCount();
        ui->TablaTareas->insertRow(rowNumber);
        QTableWidgetItem* itemnombre = new QTableWidgetItem(GetField(q,"name").toString());
        ui->TablaTareas->setItem(rowNumber-1, 0, itemnombre);
        QTableWidgetItem* itemfecha = new QTableWidgetItem(GetField(q,"date").toString());
        ui->TablaTareas->setItem(rowNumber-1, 1, itemfecha);
        QTableWidgetItem* itemdone = new QTableWidgetItem("");
        itemdone->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        if (GetField(q,"done")==0){
            itemdone->setCheckState(Qt::Unchecked);
        }else{
            itemdone->setCheckState(Qt::Checked);
        }
        ui->TablaTareas->setItem(rowNumber-1,2,itemdone);

    }while (q.next());
     ui->TablaTareas->setSortingEnabled(true);

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
 /*   addingEtiqueta_ = true;
    ui->TablaEtiquetas->insertRow(ui->TablaEtiquetas->rowCount());
    ui->TablaEtiquetas->setItem(ui->TablaEtiquetas->rowCount()-1, 0, new QTableWidgetItem(""));
    addingEtiqueta_= false;*/

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
  /*  if (addingCategoria_)
           return;
     addingCategoria_= true;
    //Obtenemos los campos
    QString nombre = ui->TablaCategorias->item(row,0)->text();
    //QString desc =ui->TablaCategorias->item(row,1)->text();
    int done=0;
    QTableWidgetItem* item = new QTableWidgetItem("");
    if(ui->TablaCategorias->item(ui->TablaCategorias->rowCount()-1,2)->isSelected())
        done=1;
    //Insertamos en la base de datos

    QString query("INSERT INTO categorias (name, descripcion) VALUES (" +
                  QString("'%1','%2'")\
                  .arg(nombre+");");
                  //.arg(desc) + ");");
   //Inserta en las Categorias
    db_.exec(query);
    addingCategoria_= false;
*/
}

void MainWindow::onGuardaEtiqueta(int row,int col){

}

void MainWindow::onGuardaTarea(){
   /* if (addingTarea_)
           return;

     addingTarea_ = true;
    //Insertar la tarea en la base de datos
    //Obtenemos los campos
    QString nombre = ui->TablaTareas->item (ui->TablaTareas->rowCount()-1,0)->text();
    QString desc =ui->TablaTareas->item(ui->TablaTareas->rowCount()-1,1)->text();
    int done=0;
    QTableWidgetItem* item = new QTableWidgetItem("");
    if (ui->TablaTareas->item(ui->TablaTareas->rowCount()-1,2)->isSelected())
        done=1;

    int idCat;//Tenemos que consultar en la tabla categorias y guardar el ID
    QString nombreCat= ui->comboBoxCategorias->currentText();
    //Tenemos que consultar el cuadro descripción y guardarlo

    //QTextDocument descripcion =ui->TextDescripcion->actions(;
    //Insertamos en la base de datos
    addingTarea_ = false;
    */

}


