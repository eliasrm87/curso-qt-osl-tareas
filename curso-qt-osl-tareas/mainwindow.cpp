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
    connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int,int)));
    connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));

    // Cuando haces click en una celda de una categoría, muestra su descripcion
    connect(ui->tblCateg, SIGNAL(cellClicked(int,int)), this, SLOT(showDescriptionCat(int, int)));

    // Cuando haces click en una celda de una tarea, muestra su descripcion
    connect(ui->tblTareas, SIGNAL(cellClicked(int,int)), this, SLOT(showDescriptionTarea(int,int)));

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

    loadTareas(); // Carga las tareas guardadas en la base de datas


    //Activamos el sorting en las tablas
    ui->tblTareas->setSortingEnabled(true);
    ui->tblCateg->setSortingEnabled(true);
    ui->comboCategoria->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTareas()
{
    addingTarea_ = true;

    QSqlQuery q = db_.exec("SELECT * "
                           "FROM tareas;");

    int contFilas = 0;

    while(q.next()) {

        int rowNumber = ui->tblTareas->rowCount();
        ui->tblTareas->insertRow(ui->tblTareas->rowCount());// Inserta una fila

        // Checkbox
        QTableWidgetItem* item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done") == 0){
            item->setCheckState(Qt::Unchecked);
        }else{
            item->setCheckState(Qt::Checked);
        }

        ui->tblTareas->setItem(rowNumber, 2, item);

        QTableWidgetItem *nombre = new QTableWidgetItem(GetField(q, "name").toString());
        ui->tblTareas->setItem(rowNumber, 0, nombre);
        QTableWidgetItem *fecha = new QTableWidgetItem(GetField(q, "date").toString());
        ui->tblTareas->setItem(rowNumber, 1, fecha);

        //qDebug() << "Nombre tarea: " << GetField(q, "name").toString() << " Fecha tarea: " << GetField(q, "date").toString();
        //qDebug() << "Row cont: " << ui->tblTareas->rowCount();

        contFilas = contFilas + 1;

    }

    addingTarea_ = false;

}

void MainWindow::onAddTarea()
{
    addingTarea_ = true;

    ui->tblTareas->insertRow(ui->tblTareas->rowCount());// Inserta una fila
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
                 .arg(ui->comboCategoria->currentText().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentText().toInt()) +
                 "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
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
                 "WHERE id_categ = " + ui->comboCategoria->currentText());

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

// Muestra la descripción de una tarea cuando seleccionas el nombre de una categoria
void MainWindow::showDescriptionCat(int fila, int col)
{

    col = col + 0; // no se usa

    QSqlQuery q = db_.exec("SELECT * "
                           "FROM categorias");
    q.seek(fila);
    QString cadena = (GetField(q, "descripcion").toString());
    ui->txtCategDescr->setText(cadena);

}

// Muestra la descripción de una tarea cuando seleccionas una tarea
void MainWindow::showDescriptionTarea(int fila, int col)
{

    col = col + 0; // no se usa

    QSqlQuery q = db_.exec("SELECT * "
                           "FROM tareas");
    q.seek(fila);
    QString cadena = (GetField(q, "descripcion").toString());
    ui->txtCategDescr->setText(cadena);

}
