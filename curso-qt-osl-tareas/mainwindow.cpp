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


    ui->tableTareas->setColumnWidth(0, 400);
    ui->tableTareas->setColumnWidth(1, 200);
    ui->tableTareas->setColumnWidth(2, 200);
    ui->tableTareas->setColumnWidth(3, 350);
    ui->tableTareas->horizontalHeader()->setStretchLastSection(true);
    ui->tableCategorias->horizontalHeader()->setStretchLastSection(true);
    ui->tableEtiquetas->horizontalHeader()->setStretchLastSection(true);
    ui->tareaEtiquetas->horizontalHeader()->setStretchLastSection(true);

    // Conect
    connect(ui->actionNueva,        SIGNAL(triggered()),                this, SLOT(addTarea()));
    connect(ui->tableTareas,        SIGNAL(cellChanged(int,int)),       this, SLOT(onTareasCellChanged(int)));
    connect(ui->comboCategorias,    SIGNAL(currentIndexChanged(int)),   this, SLOT(onLoadTareas()));

    connect(ui->categoriaNueva,     SIGNAL(triggered()),                this, SLOT(addCategoria()));
    connect(ui->tableCategorias,    SIGNAL(cellChanged(int,int)),       this, SLOT(onCategoriasCellChanged(int)));

    connect(ui->etiquetaNueva,      SIGNAL(triggered()),                this, SLOT(addEtiqueta()));
    connect(ui->tableEtiquetas,     SIGNAL(cellChanged(int,int)),       this, SLOT(onEtiquetasCellChanged(int)));

    connect(ui->tableTareas,        SIGNAL(cellClicked(int,int)),       this, SLOT(onDescriptionTask(int, int)));
    connect(ui->tableTareas,        SIGNAL(cellClicked(int,int)),       this, SLOT(onEtiquetasTask(int, int)));

    addingTarea_ = false;
    addingCategoria_ = false;
    addingEtiqueta_ = false;

    onLoadCategorias();
    onLoadEtiquetas();
    initTableEtiquetas();

}

MainWindow::~MainWindow() {
    delete ui;
}


/***********************************    TAREAS   ********************************************/
void MainWindow::addTarea() {
    addingTarea_ = true;
    ui->tableTareas->insertRow(ui->tableTareas->rowCount());

    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
    ui->tableTareas->setItem(ui->tableTareas->rowCount()-1, 4, item);

    ui->tableTareas->setItem(ui->tableTareas->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tableTareas->setItem(ui->tableTareas->rowCount()-1, 1, new QTableWidgetItem(""));

    addingTarea_ = false;
}

void MainWindow::onTareasCellChanged(int row) {
    if (addingTarea_)
        return;

    addingTarea_ = true;

    int checked = (ui->tableTareas->item(row, 4)->checkState() == Qt::Checked);

    QSqlQuery query;

    if (ui->tableTareas->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, id_categ) "
                 "VALUES ("+QString("'%1','%2','%3','%4','%5');" )\
                 .arg(ui->tableTareas->item(row, 0)->text())\
                 .arg(ui->tareaDescription->toPlainText())\
                 .arg(ui->tableTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategorias->currentData().toInt()));
        ui->tableTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                 .arg(ui->tableTareas->item(row, 0)->text())\
                 .arg(ui->tareaDescription->toPlainText())\
                 .arg(ui->tableTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategorias->currentData().toInt()) +
                 "WHERE id = " + ui->tableTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingTarea_ = false;
}

void MainWindow::onLoadTareas()
{
    addingTarea_ = true;

    while (ui->tableTareas->rowCount())
        ui->tableTareas->removeRow(0);

    //Obtenemos las tareas
    QSqlQuery q = db_.exec("SELECT * "
                 "FROM tareas "
                 "WHERE id_categ = " + ui->comboCategorias->currentData().toString());

    QSqlQuery qCategoria = db_.exec("SELECT * "
                                    "FROM categorias "
                                    "WHERE id = " + ui->comboCategorias->currentData().toString());
    qCategoria.next();

    while (q.next()) {
        //Añadimos la tarea a la tabla de categorias
        int rowNumber = ui->tableTareas->rowCount();
        int id = GetField(q, "id").toInt();
        ui->tableTareas->insertRow(rowNumber);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        item->setData(Qt::UserRole, id);
        ui->tableTareas->setItem(rowNumber, 0, item);
        ui->tableTareas->setItem(rowNumber, 1, new QTableWidgetItem(GetField(q, "date").toString()));
        ui->tableTareas->setItem(rowNumber, 2, new QTableWidgetItem(GetField(qCategoria, "name").toString()));

        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done").toInt())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tableTareas->setItem(rowNumber, 4, item);
    }
    //Activamos el sorting en la tabla de categorias
    ui->tableTareas->setSortingEnabled(true);
    addingTarea_ = false;
}

/***********************************    CATEGORIAS   ********************************************/
void MainWindow::addCategoria() {
    addingCategoria_ = true;
    ui->tableCategorias->insertRow(ui->tableCategorias->rowCount());

    ui->tableCategorias->setItem(ui->tableCategorias->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tableCategorias->setItem(ui->tableCategorias->rowCount()-1, 1, new QTableWidgetItem(""));

    addingCategoria_ = false;
}

void MainWindow::onCategoriasCellChanged(int row) {
    if (addingCategoria_)
        return;

    addingCategoria_ = true;
    QSqlQuery query;

    if (ui->tableCategorias->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO categorias (name, descripcion) "
                 "VALUES ("+QString("'%1','%2');" )\
                 .arg(ui->tableCategorias->item(row, 0)->text())\
                 .arg(ui->tableCategorias->item(row, 1)->text()));

        ui->tableCategorias->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        qDebug() << "Entro en el update";
        query = db_.exec("UPDATE categorias "
                 "SET "+QString("name='%1',descripcion='%2' ")\
                 .arg(ui->tableCategorias->item(row, 0)->text())\
                 .arg(ui->tableCategorias->item(row, 1)->text()) +
                 "WHERE id = " + ui->tableCategorias->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingCategoria_ = false;
}


void MainWindow::onLoadCategorias() {
    addingCategoria_ = true;

    while (ui->tableCategorias->rowCount())
        ui->tableCategorias->removeRow(0);


    // Consulta
    QSqlQuery qCategorias = db_.exec("SELECT * FROM categorias;");

    // Recorro la lista de categorias
    while (qCategorias.next()) {
        ui->comboCategorias->addItem(GetField(qCategorias,"name").toString(), GetField(qCategorias,"id").toInt());
        int rowNumber = ui->tableCategorias->rowCount();
        ui->tableCategorias->insertRow(rowNumber);
        QTableWidgetItem* nombre = new QTableWidgetItem(GetField(qCategorias, "name").toString());
        ui->tableCategorias->setItem(rowNumber, 0, nombre);

        QTableWidgetItem* descripcion = new QTableWidgetItem(GetField(qCategorias, "descripcion").toString());
        ui->tableCategorias->setItem(rowNumber, 1, descripcion);
    }
    ui->tableCategorias->setSortingEnabled(true);
    ui->comboCategorias->setCurrentIndex(0);
}


/***********************************    ETIQUETAS   ********************************************/
void MainWindow::addEtiqueta() {
    addingEtiqueta_ = true;
    ui->tableEtiquetas->insertRow(ui->tableEtiquetas->rowCount());
    ui->tableEtiquetas->setItem(ui->tableEtiquetas->rowCount()-1, 0, new QTableWidgetItem(""));
    addingEtiqueta_ = false;
}


void MainWindow::onEtiquetasCellChanged(int row) {
    if (addingEtiqueta_)
        return;

    addingEtiqueta_ = true;
    QSqlQuery query;

    if (ui->tableEtiquetas->item(row, 0)->data(Qt::UserRole).isNull()) {
        query = db_.exec("INSERT INTO etiquetas(name) "
                 "VALUES ("+QString("'%1');" )\
                 .arg(ui->tableEtiquetas->item(row, 0)->text()));
        ui->tableEtiquetas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1'" )\
                 .arg(ui->tableEtiquetas->item(row, 0)->text()) +
                 "WHERE id = " + ui->tableEtiquetas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    }

    addingEtiqueta_ = false;
}


void MainWindow::onLoadEtiquetas() {
    addingEtiqueta_ = true;

    while (ui->tableEtiquetas->rowCount())
        ui->tableEtiquetas->removeRow(0);

    QSqlQuery qEtiquetas = db_.exec("SELECT * FROM etiquetas;");

    while (qEtiquetas.next()) {
        ui->comboEtiquetas->addItem(GetField(qEtiquetas,"name").toString(), GetField(qEtiquetas,"id").toInt());
        int rowNumber = ui->tableEtiquetas->rowCount();
        ui->tableEtiquetas->insertRow(rowNumber);
        QTableWidgetItem* nombre = new QTableWidgetItem(GetField(qEtiquetas, "name").toString());
        ui->tableEtiquetas->setItem(rowNumber, 0, nombre);
    }
    ui->tableEtiquetas->setSortingEnabled(true);
}


void MainWindow::onDescriptionTask(int row, int col) {
    QSqlQuery q = db_.exec( "SELECT descripcion "
                            "FROM tareas "
                            "WHERE name = '" + ui->tableTareas->item(row, 0)->text() + "';");

    qDebug() << "SELECT descripcion "
                "FROM tareas "
                "WHERE name = '" + ui->tableTareas->item(row, 0)->text() + "';";

    q.next();
    qDebug() << GetField(q, "descripcion").toString();
    ui->tareaDescription->setText(GetField(q, "descripcion").toString());
}

void MainWindow::onEtiquetasTask(int row, int col) {
    // Obtengo el id de la tarea seleccionada
    QSqlQuery qTarea = db_.exec("SELECT id "
                                "FROM tareas "
                                "WHERE name = '" + ui->tableTareas->item(row, 0)->text() + "';");
    qTarea.next();
    QString idTarea = GetField(qTarea, "id").toString();

    // Obtengo la lista de todos las etiquetas existentes
    QSqlQuery qEtiquetas = db_.exec("SELECT * "
                                    "FROM etiquetas;");

    // Obtengo los que están asignados a la tarea en concreto
    QSqlQuery qAsignados = db_.exec("SELECT * "
                                    "FROM tareas_etiq "
                                    "WHERE id = " + GetField(qTarea,"id").toString());

    int i = 0;
    while (qEtiquetas.next()) {
        QSqlQuery qIdElegido = db_.exec("SELECT * "
                                        "FROM etiquetas "
                                        "WHERE name='" + ui->tareaEtiquetas->item(i, 1)->text() + "';");
        qIdElegido.next();
        qDebug() << GetField(qIdElegido, "id").toString();
        QSqlQuery qAsignados = db_.exec("SELECT * "
                                        "FROM tareas_etiq "
                                        "WHERE ((id_tarea = " + GetField(qTarea,"id").toString() +
                                        ") & (id_etiq= " + GetField(qIdElegido, "id").toString() + "));");
        qDebug() << "SELECT * "
                    "FROM tareas_etiq "
                    "WHERE ((id_tarea = " + GetField(qTarea,"id").toString() +
                    ") & (id_etiq= " + GetField(qIdElegido, "id").toString() + "));";

        if (qAsignados.size() > 0) {
            qDebug() << "Tiene resultado";
        } else {
            qDebug() << "No tiene resultado " << qAsignados.size() << " " << qAsignados.numRowsAffected();
        }

        i++;
    }


}

void MainWindow::initTableEtiquetas() {
    // Obtengo la lista de todos las etiquetas existentes
    QSqlQuery qEtiquetas = db_.exec("SELECT * "
                                    "FROM etiquetas;");

    while (qEtiquetas.next()) {
        //ui->comboEtiquetas->addItem(GetField(qEtiquetas,"name").toString(), GetField(qEtiquetas,"id").toInt());
        int rowNumber = ui->tareaEtiquetas->rowCount();
        ui->tareaEtiquetas->insertRow(rowNumber);
        QTableWidgetItem* nombre = new QTableWidgetItem(GetField(qEtiquetas, "name").toString());
        ui->tareaEtiquetas->setItem(rowNumber, 1, nombre);
    }

}
