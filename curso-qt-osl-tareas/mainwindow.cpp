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


    db_.exec("DELETE FROM tareas;");
    db_.exec("DELETE FROM categorias;");
    db_.exec("INSERT INTO tareas(name, date, done) VALUES ('Hacer la compra', '20/12/2010', 0), ('Entregar trabajo', '20/12/2010', 1);");
    db_.exec("INSERT INTO categorias(name) VALUES ('Universidad'), ('Personal');");


    ui->tableWidget->setColumnWidth(0, 600);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 300);
     ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Conect
    connect(ui->actionNueva,        SIGNAL(triggered()),                this, SLOT(addTarea()));
    connect(ui->tableWidget,        SIGNAL(cellChanged(int,int)),       this, SLOT(onTareasCellChanged(int,int)));
    connect(ui->comboCategorias,    SIGNAL(currentIndexChanged(int)),   this, SLOT(onLoadTareas()));

    addingTarea_ = false;



    // Consulta
    QSqlQuery qTareas = db_.exec("SELECT * FROM tareas;");
    QSqlQuery qCategorias = db_.exec("SELECT * FROM categorias;");

    // Recorro la lista de tareas
    while (qTareas.next()) {
        int rowNumber = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowNumber);

        QTableWidgetItem* name = new QTableWidgetItem(GetField(qTareas, "name").toString());
        ui->tableWidget->setItem(rowNumber, 0, name);

        QTableWidgetItem* date = new QTableWidgetItem(GetField(qTareas, "date").toString());
        ui->tableWidget->setItem(rowNumber, 1, date);

        QTableWidgetItem* done = new QTableWidgetItem();
        done->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        int doneState = GetField(qTareas, "done").toInt();
        if (doneState == 0)
            done->setCheckState(Qt::Unchecked);
        else
            done->setCheckState(Qt::Checked);

        ui->tableWidget->setItem(rowNumber, 3, done);
    }
    ui->tableWidget->setSortingEnabled(true);

    // Recorro la lista de categorias
    while (qCategorias.next()) {
        ui->comboCategorias->addItem(GetField(qCategorias,"name").toString(), GetField(qCategorias,"id").toInt());

        int rowNumber = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowNumber);
        QTableWidgetItem* item = new QTableWidgetItem(GetField(qCategorias, "name").toString());
        ui->tableWidget_2->setItem(rowNumber, 0, item);
    }
    ui->tableWidget_2->setSortingEnabled(true);
    ui->comboCategorias->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTarea() {
    addingTarea_ = true;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, item);

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(""));

    addingTarea_ = false;
}

void MainWindow::saveTarea(int row, int col) {
    //db_.exec("INSERT INTO tareas(name, date) VALUES ('%1', '%2');").arg(ui->tableWidget->item(row,0)->text()).arg();
}
