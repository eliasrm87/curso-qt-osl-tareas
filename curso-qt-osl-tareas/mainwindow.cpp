#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    inicializaBD();

    catModif_ = false;
    editar_ = true;
    desc_tarea_ = false;


    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    this->setGeometry(30, 30, 800, 600);
    this->setWindowTitle(tr("Gestor de Tareas"));



    txtEditor_ = new QTextEdit(this);
    tareas_ = new QTableWidget(0,5,this);
    categorias_ = new QTableWidget(0,2,this);
    etiquetas_ = new QTableWidget(0,2,this);

    QTextDocument * textDocument = txtEditor_->document();
    textDocument->setModified(false);

    connect(txtEditor_, SIGNAL(textChanged()), this, SLOT(guardarDescripcion()));

    tareas_->setAutoScroll(true);

    categorias_->setAutoScroll(true);
    categorias_->verticalHeader()->hide();
    categorias_->horizontalHeader()->hide();

    etiquetas_->setAutoScroll(true);
    etiquetas_->verticalHeader()->hide();
    etiquetas_->horizontalHeader()->hide();


    QLabel* labEtiquetas = new QLabel("Etiquetas");
    QLabel* labCategorias = new QLabel("Categorías");
    QLabel* labDescripcion = new QLabel("Descripción");

    lytMain_->addWidget(labCategorias,0,1,1,1);
    lytMain_->addWidget(categorias_,1,1,1,1);
    lytMain_->addWidget(labEtiquetas,0,0,1,1);
    lytMain_->addWidget(etiquetas_,1,0,1,1);
    lytMain_->addWidget(tareas_,2,0,1,2);
    lytMain_->addWidget(labDescripcion,0,2,1,1);
    lytMain_->addWidget(txtEditor_,1,2,3,2);


    mostrarTareas();
    mostrarCategorias();
    mostrarEtiquetas();

}

MainWindow::~MainWindow()
{

}



/*void MainWindow::verDescripcionCat (int row, int col) {

}*/

void MainWindow::verDescripcion (int row, int col) {

    row_act_ = row;
    col_act_ = 0;
    QSqlQuery q_tar_desc = db_.exec("SELECT descripcion FROM tareas;");
    QSqlQuery q_tar_count = db_.exec("SELECT count(*) FROM tareas;");
    QString descripcion ;

    q_tar_count.first();
    if (q_tar_count.value(0)  > row) {
        q_tar_desc.seek(row);
        descripcion = q_tar_desc.value("descripcion").toString();
    }
    else {
        descripcion = "";
    }
    txtEditor_->setText(descripcion);
    desc_tarea_ = true;

}


void MainWindow::guardarContenido(int row, int col) {

    if (!editar_)  {
        return;
    }

    row_act_ = row;
    col_act_ = col;

    QSqlQuery q_tar_count = db_.exec("SELECT count(*) FROM tareas;");

    QString texto = tareas_->item(row, col)->text();

    q_tar_count.first();
    if (q_tar_count.value(0)  > row) {

        QSqlQuery q_tar_id = db_.exec("SELECT id FROM tareas;");
        q_tar_id.seek(row);
        QString id_tar = q_tar_id.value("id").toString();


        switch (col) {
        case 0:
            db_.exec("UPDATE tareas SET name =\""+ texto + "\" WHERE id = \""+ id_tar + "\" ;");
            break;
        case 1:
            db_.exec("UPDATE tareas SET date =\""+ texto + "\" WHERE id = \""+ id_tar + "\" ;");
            break;
        case 2:
            db_.exec("UPDATE tareas SET done =\""+ texto + "\" WHERE id = \""+ id_tar + "\" ;");
            break;
        default:
            break;
        }

    }
    else {

        switch (col) {
        case 0:
            db_.exec("INSERT INTO tareas (name, date, done, descripcion, id_categ) VALUES (\" "+ texto + "\", \"\", \"0\", \"\", \"-1\");");
            break;
        case 1:
            db_.exec("INSERT INTO tareas (name, date, done, descripcion, id_categ) VALUES (\"\", \" "+ texto + "\", \"0\", \"\", \"-1\);");
            break;
        case 2:
            db_.exec("INSERT INTO tareas (name, date, done, descripcion, id_categ) VALUES (\"\", \"\", \" "+ texto + "\", \"\", \"-1\);");
            break;
        default:
            break;
        }

        tareas_->setRowCount(tareas_->rowCount() + 1);
    }
}

void MainWindow::mostrarCategorias () {
    q_cat.first();
    QStringList cabeceraCategorias;
    cabeceraCategorias << "Categoria";
    categorias_->setHorizontalHeaderLabels(cabeceraCategorias);
    categorias_->setShowGrid(false);

    QSignalMapper* mapper = new QSignalMapper(this);



    int row = 0;
    bool impar = false;
    QRadioButton *radio = new QRadioButton("TODAS", this);
    categorias_->insertRow(row);
    radio->setChecked(true);
    categorias_->setCellWidget(row,0,radio);

    connect(radio, SIGNAL(toggled(bool)), mapper, SLOT(map()));
    mapper->setMapping(radio, "TODAS");

    do {
        QString categoria = q_cat.value(1).toString();
        radio = new QRadioButton(categoria, this);
        if (impar) {
            categorias_->insertRow(row);
            categorias_->setCellWidget(row,0,radio);
        }
        else {
            categorias_->setCellWidget(row,1,radio);
            row++;
        }
        impar = !impar;

        connect(radio, SIGNAL(toggled(bool)), mapper, SLOT(map()));
        mapper->setMapping(radio, categoria);

    } while (q_cat.next());
    categorias_->insertRow(row);


    connect(mapper,SIGNAL(mapped(QString)),this,SLOT(cambiaCategoria(QString)));

}


void MainWindow::setCategoria (QString cat) {
   /* QStringList catL = cat.split("-");
    int id_tarea = catL.at(1).toInt();
    int row = catL.at(0).toInt();
    qDebug() << "id_tarea: " << id_tarea << " row: " << row;*/
    qDebug() << cat;

}


void MainWindow::cambiaCategoria (QString cat) {
    editar_ = false;

    if (catModif_) {
        if (cat != "TODAS") {
            q_tar.clear();
            q_tar.prepare("SELECT t.id, t.name, t.descripcion, t.date, t.done, t.id_categ  FROM categorias c, tareas t WHERE  c.name=:cat AND  c.id = t.id_categ;");
            q_tar.bindValue(":cat", cat);
            q_tar.exec();
            q_tar.first();

            QSqlQuery q_cat_desc = db_.exec("SELECT id, descripcion FROM categorias WHERE name=\""+cat+"\";");
            QString descripcion = "prueba";
            q_cat_desc.first();
            descripcion = q_cat_desc.value("descripcion").toString();

            id_cat_act_ = q_cat_desc.value("id").toInt();

            txtEditor_->setText(descripcion);
            desc_tarea_ = false;

            q_cat_desc.clear();



        }

        else{
            q_tar.clear();
            q_tar = db_.exec("SELECT * FROM tareas;");
            txtEditor_->setText("");
            id_cat_act_ = -1;
        }
        mostrarTareas();
    }
    catModif_ = !catModif_;
    editar_ = true;
}


void MainWindow::mostrarEtiquetas (){
    QStringList cabeceraEtiquetas;
    cabeceraEtiquetas << "Etiqueta";
    etiquetas_->setHorizontalHeaderLabels(cabeceraEtiquetas);
    etiquetas_->setShowGrid(false);

    bool impar = true;
    int row = 0;
    while (q_etiq.next()) {
        QString etiqueta = q_etiq.value(1).toString();
        QCheckBox *checkbox_ = new QCheckBox(etiqueta);
        checkbox_->setChecked(true);

        if (impar) {
            etiquetas_->insertRow(row);
            etiquetas_->setCellWidget(row,0,checkbox_);
        }
        else {
            etiquetas_->setCellWidget(row,1,checkbox_);
            row++;
        }
        impar = !impar;

    }
    etiquetas_->insertRow(row);
}


void MainWindow::mostrarTareas () {
    QStringList cabeceraTareas;
    tareas_->setRowCount(0);
    tareas_->clear();
    cabeceraTareas << "Nombre" << "Fecha" << "Estado" << "Categoría" << "Etiquetas";
    tareas_->setHorizontalHeaderLabels(cabeceraTareas);
    tareas_->setShowGrid(false);
    int row = 0;
    q_tar.first();
    do  {
        QString nombre = q_tar.value(1).toString();
        QString descripcion = q_tar.value(2).toString();
        QString fecha = q_tar.value(3).toString();

        QString estado = q_tar.value(4).toString();

        QString id_cat = q_tar.value(5).toString();

        QString id_tarea = q_tar.value(0).toString();

        QCheckBox *checkbox_ = new QCheckBox();
        if (estado == "0") {
            checkbox_->setChecked(false);
         }
        else {
            checkbox_->setChecked(true);
        }

        tareas_->insertRow(row);
        tareas_->setItem(row, 0, new QTableWidgetItem (nombre));

        tareas_->setItem(row, 1, new QTableWidgetItem (fecha));

        tareas_->setCellWidget(row,2,checkbox_);


        QSqlQuery q_cat_tar = db_.exec("SELECT name FROM categorias WHERE id = "+id_cat+";");

        QComboBox* combo = new QComboBox(this);
        comboL.insert(row, combo);
        q_cat.first();
        QStringList listaCat;

        if (id_cat == "-1") {
            listaCat << "Sin categoria";
            combo->addItem("Sin categoria", "hola");
        }
        do {
            if (q_cat.isValid()) {
                listaCat << q_cat.value(1).toString();
                combo->addItem(q_cat.value(1).toString(), "hola");
            }
        } while (q_cat.next());

       // combo->addItems(listaCat);

        q_cat_tar.first();
        QString categorias_tarea;
        if (id_cat == "-1") {
            categorias_tarea = "Sin categoria";
        }
        else {
            categorias_tarea = q_cat_tar.value(0).toString();
        }


        combo->setCurrentText(categorias_tarea);

        combo->setUserData(row, (QObjectUserData*)"hola");


        tareas_->setCellWidget(row,3,combo);

        //QSignalMapper* mapper = new QSignalMapper(tareas_);


        //connect(combo, SIGNAL(currentTextChanged(QString)), mapper, SLOT(map()));

        connect(combo, SIGNAL(currentTextChanged(QString)), this, SLOT(setCategoria(QString)));

        //mapper->setMapping(combo, QString("%1-%2").arg(row).arg(id_tarea));
        //connect(mapper,SIGNAL(mapped(QString)),this,SLOT(setCategoria(QString)));

        QSqlQuery q_tar_etiq = db_.exec("SELECT e.name FROM  tareas t, etiquetas e, tareas_etiq x WHERE t.id = x.id_tarea AND e.id = x.id_etiq AND t.id = "+id_tarea+";");


        QString etiqueta_tarea = "";
        do {
            if (q_tar_etiq.value(0).toString() != "") {
                etiqueta_tarea += "," + q_tar_etiq.value(0).toString();
            }
        } while (q_tar_etiq.next());
        tareas_->setItem(row, 4, new QTableWidgetItem (etiqueta_tarea));
        row++;

    } while (q_tar.next());

    connect(tareas_, SIGNAL(cellClicked(int,int)), this, SLOT(verDescripcion(int, int)));

    if (editar_) {
        connect(tareas_, SIGNAL(cellChanged(int,int)), this, SLOT(guardarContenido(int, int)));
    }
    tareas_->insertRow(row);

}


void MainWindow::guardarDescripcion () {

    if (!editar_) {
        return;
    }



    if (desc_tarea_) {
        QSqlQuery q_tar_id = db_.exec("SELECT id FROM tareas;");
        q_tar_id.seek(row_act_);
        QString id_tar = q_tar_id.value("id").toString();
        QString texto = txtEditor_->toPlainText();
        db_.exec("UPDATE tareas SET descripcion =\""+ texto + "\" WHERE id = \""+ id_tar + "\" ;");
    }
    else {
        if (id_cat_act_ != -1) {
            QSqlQuery q_cat_id = db_.exec("SELECT id FROM categorias;");
            q_cat_id.seek(id_cat_act_);
            QString id_cat = q_cat_id.value("id").toString();
            QString texto = txtEditor_->toPlainText();
            db_.exec("UPDATE categorias SET descripcion =\""+ texto + "\" WHERE id = \""+ id_cat + "\" ;");
        }

    }
}


void MainWindow::inicializaBD () {
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


    q_cat = db_.exec("SELECT * FROM categorias;");
    q_tar = db_.exec("SELECT * FROM tareas;");
    q_etiq = db_.exec("SELECT * FROM etiquetas;");
}
