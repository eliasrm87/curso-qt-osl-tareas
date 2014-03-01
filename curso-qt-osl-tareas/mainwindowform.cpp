#include "mainwindowform.h"
#include "ui_mainwindowform.h"

MainWindowForm::MainWindowForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowForm)
{
    ui->setupUi(this);

    //Setup database
    ConecToDb(db_, "tareas");

    db_.exec("CREATE TABLE IF NOT EXISTS categorias("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS etiquetas("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT"
              ");");


    db_.exec("CREATE TABLE IF NOT EXISTS tareas("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "descripcion TEXT,"
              "date TEXT,"
              "realizada NUMERIC,"
              "id_categoria INTEGER,"
              "FOREIGN KEY(id_categoria) REFERENCES categorias(id)"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS tarea_etiqueta("
                      "id_tarea INTEGER NOT NULL,"
                      "id_etiqueta INTEGER NOT NULL,"
                      "PRIMARY KEY (id_tarea, id_etiqueta),"
                      "FOREIGN KEY(id_tarea) REFERENCES tareas(id),"
                      "FOREIGN KEY(id_etiqueta) REFERENCES etiquetas(id)"
             ");");



    QSqlRelation relation("categorias", "id", "name");
    QSqlRelationalDelegate delegate(this);

    QSqlRelationalTableModel* modelTareas = new QSqlRelationalTableModel(this, db_)    ;
    modelTareas->setTable("tareas");
    modelTareas->setEditStrategy(QSqlTableModel::OnFieldChange);

    modelTareas->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    modelTareas->setRelation(5, relation);

    modelTareas->select();
    //modelTareas->submitAll();


    modelTareas->removeColumn(0); //# don't show the ID
    modelTareas->setHeaderData(0,Qt::Horizontal, "Nombre");
    modelTareas->setHeaderData(4,Qt::Horizontal, "Categoría");



    ui->tblTareas->setModel(modelTareas);

    //ui->tblTareas->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tblTareas->setItemDelegateForColumn(4,new QSqlRelationalDelegate(this));



    QSqlRecord record =  modelTareas->record();

    QVariant dato = "prueba";

    //record.value(2).setValue(dato);


    //modelTareas->insertRecord(-1, record);

    //modelTareas->select();



    QHeaderView* header =  ui->tblTareas->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindowForm::~MainWindowForm()
{
    delete ui;
}
