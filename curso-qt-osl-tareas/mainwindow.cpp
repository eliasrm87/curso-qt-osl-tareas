#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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


    QSqlQuery q_cat = db_.exec("SELECT * FROM categorias;");
    QSqlQuery q_tar = db_.exec("SELECT * FROM tareas;");
    QSqlQuery q_etiq = db_.exec("SELECT * FROM etiquetas;");

    QWidget* wgtMain_ = new QWidget(this);
    QGridLayout* lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    this->setGeometry(30, 30, 800, 600);
    this->setWindowTitle(tr("Gestor de Tareas"));



    txtEditor_ = new QTextEdit(this);
    tareas_ = new QTableWidget(0,3,this);
    categorias_ = new QTableWidget(0,1,this);
    etiquetas_ = new QTableWidget(0,1,this);


    tareas_->setAutoScroll(true);
    categorias_->setAutoScroll(true);

    lytMain_->addWidget(categorias_,0,1,1,1);
    lytMain_->addWidget(etiquetas_,0,0,1,1);
    lytMain_->addWidget(tareas_,1,0,1,2);
    lytMain_->addWidget(txtEditor_,0,2,2,2);

    QStringList listaTareas;
    listaTareas << "Hola" << "a sdad " << "cas sads ad";
   // tareas_->addItems(listaTareas);


    QStringList cabeceraTareas;
    cabeceraTareas << "Nombre" << "Fecha" << "Estado";
    tareas_->setHorizontalHeaderLabels(cabeceraTareas);
    tareas_->setShowGrid(false);
    int row = 0;
    while (q_tar.next()) {
        QString nombre = q_tar.value(1).toString();
        QString descripcion = q_tar.value(2).toString();
        QString fecha = q_tar.value(3).toString();

        QString estado = q_tar.value(4).toString();

        QCheckBox *checkbox_ = new QCheckBox();
        if (estado == "0") {
            checkbox_->setChecked(false);
         }
        else {
            checkbox_->setChecked(true);
        }

        //int row = tareas_->rowCount();
        tareas_->insertRow(row);
        tareas_->setItem(row, 0, new QTableWidgetItem (nombre));
        //tareas_->setItem(row, 1, new QTableWidgetItem (descripcion));
        //txtEditor_->setText(descripcion);
        tareas_->setItem(row, 1, new QTableWidgetItem (fecha));

        tareas_->setCellWidget(row,2,checkbox_);
        row++;

        connect(tareas_, SIGNAL(cellClicked(int,int)), this, SLOT(verDescripcion(int, int)));
        connect(tareas_, SIGNAL(cellChanged(int,int)), this, SLOT(guardarContenido(int, int)));

    }
    tareas_->insertRow(row);

    QStringList cabeceraCategorias;
    cabeceraCategorias << "Categoria";
    categorias_->setHorizontalHeaderLabels(cabeceraCategorias);
    categorias_->setShowGrid(false);
    row = 0;
    while (q_cat.next()) {
        QString categoria = q_cat.value(1).toString();
        //int row = tareas_->rowCount();
        categorias_->insertRow(row);
        categorias_->setItem(row, 0, new QTableWidgetItem (categoria));
        row++;
    }
    categorias_->insertRow(row);

    QStringList cabeceraEtiquetas;
    cabeceraEtiquetas << "Etiqueta";
    etiquetas_->setHorizontalHeaderLabels(cabeceraEtiquetas);
    etiquetas_->setShowGrid(false);
    row = 0;
    while (q_etiq.next()) {
        QString etiqueta = q_etiq.value(1).toString();
        QCheckBox *checkbox_ = new QCheckBox(etiqueta);
        checkbox_->setChecked(true);


        //int row = tareas_->rowCount();
        etiquetas_->insertRow(row);
      //  etiquetas_->setItem(row, 0, new QTableWidgetItem (etiqueta));
        etiquetas_->setCellWidget(row,0,checkbox_);

        row++;
    }
    etiquetas_->insertRow(row);

}

MainWindow::~MainWindow()
{

}



void MainWindow::verDescripcion (int row, int col) {
    QSqlQuery q_tar_desc = db_.exec("SELECT count(*), descripcion FROM tareas;");
    QString descripcion ;
    if (q_tar_desc.last()  > row) {
        q_tar_desc.seek(row);
        descripcion = q_tar_desc.value(1).toString();
    }
    else {
        descripcion = "";
    }
    txtEditor_->setText(descripcion);
}


void MainWindow::guardarContenido(int row, int col) {
    QSqlQuery q_tar_count = db_.exec("SELECT count(*) FROM tareas;");
    QString texto = tareas_->item(row, col)->text();
    if (q_tar_count.last()  > row) {

        qDebug ("%d - %d", row, col);
        switch (col) {
        case 0:
            db_.exec("UPDATE tareas SET name =\" "+ texto + "\" WHERE id = 0 ;");
            qDebug()<<"Aqui falla "<<db_.lastError();
            break;
        case 1:
            db_.exec("UPDATE tareas SET date =\" "+ texto + "\" WHERE id = 0 ;");
            break;
        case 2:
            db_.exec("UPDATE tareas SET done =\" "+ texto + "\" WHERE id = 0 ;");
            break;
        default:
            break;
        }

    }
    else {
        qDebug ("ELSE %d - %d", row, col);
      /*  switch (col) {
        case 0:
            db_.exec("INSERT INTO tareas (name) VALUES (\" "+ texto + "\");");
            qDebug()<<"Aqui falla "<<db_.lastError();
            break;
        case 1:
            db_.exec("INSERT INTO tareas (date) VALUES (\" "+ texto + "\");");
            break;
        case 2:
            db_.exec("INSERT INTO tareas (done) VALUES (\" "+ texto + "\");");
            break;
        default:
            break;
        }*/
        tareas_->setRowCount(tareas_->rowCount() + 1);
    }
}
