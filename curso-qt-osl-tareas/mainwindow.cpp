#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    //Establecemos el tamaño inicial de la ventana
    this->setMaximumSize(maximumWidth(),maximumHeight());

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Gestor de tareas (SQLite)"));
    //setCentralWidget(this);

    //Mostramos la vista de la aplicacion inicial centrada respecto a la pantalla
    set_central_win();
/*
    //Inicializamos la barra de menus
    mainMenu_= new QMenuBar(this);
    setMenuBar(mainMenu_);

    //Pestaña Archivo
    mnuArchivo_= new QMenu(tr("&Archivo"),this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoGuardar_= new QAction(tr("&Guardar"),this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    mnuArchivo_->addAction(actArchivoGuardar_);
    connect(actArchivoGuardar_, SIGNAL(triggered()),this,SLOT(Guardar()));
    mnuArchivo_->addSeparator();
    actArchivoCerrar_ = new QAction(QIcon(":/iconos/Button-Close-icon.png"),tr("&Cerrar"),this);
    actArchivoCerrar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuArchivo_->addAction(actArchivoCerrar_);
    connect(actArchivoCerrar_, SIGNAL(triggered()),this,SLOT(Cerrar()));

    //Pestaña Ayuda
    mnuAyuda_= new QMenu(tr("A&yuda"),this);
    mainMenu_->addMenu(mnuAyuda_);

    mnuAyudaDoc_ = new QMenu(tr("Documentacion"),this);
    mnuAyuda_->addMenu(mnuAyudaDoc_);
    Documentacion();
    mnuAyuda_->addSeparator();

    actAyudaAcercaDe_ = new QAction(QIcon(""),tr("AcercaDe"),this);
    mnuAyuda_->addAction(actAyudaAcercaDe_);
    connect(actAyudaAcercaDe_, SIGNAL(triggered()),this,SLOT(AcercaDe()));
*/
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

    connect(ui->actionNueva, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int)));
    connect(ui->comboCategorias, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));
    connect(ui->categoriaNueva, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
    connect(ui->tableCategorias, SIGNAL(cellChanged(int,int)), this, SLOT(onCategoriasCellChanged(int)));
    connect(ui->etiquetaNueva, SIGNAL(triggered()), this, SLOT(onAddEtiqueta()));
    connect(ui->tableEtiquetas, SIGNAL(cellChanged(int,int)), this, SLOT(onEtiquetasCellChanged(int)));
    connect(ui->tblTareas, SIGNAL(cellClicked(int,int)), this, SLOT(onDescriptionTask(int, int)));
    connect(ui->tblTareas, SIGNAL(cellClicked(int,int)), this, SLOT(onEtiquetasTask(int, int)));

    addingTarea_ = false;
    addingCategoria_ = false;
    addingEtiqueta_ = false;

    onLoadCategorias();
    onLoadEtiquetas();
    initTableEtiquetas();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::set_central_win()
{
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 25;//barra_menus + barra_aplicacion (a OJO!)
    move ( x, y );

    setFixedSize(windowSize.width(), windowSize.height());
}


void MainWindow::Cargar()
{

}

void MainWindow::Guardar()
{

}

void MainWindow::Cerrar()
{
    QMessageBox msg(this);
    msg.setInformativeText("¿Esta seguro de salir?");
    msg.addButton("Si",QMessageBox::YesRole);
    msg.addButton("No",QMessageBox::NoRole);

    QMessageBox msg2(this);
    msg2.setInformativeText("¿Desea guardar el trabajo actual?");
    msg2.addButton("Si",QMessageBox::YesRole);
    msg2.addButton("No",QMessageBox::NoRole);
    if (!msg.exec())
    {
        if (!msg2.exec())
            Guardar();
        close();
    }
}

void MainWindow::Documentacion()
{
    QAction* actAyudaDoc1;
    actAyudaDoc1= new QAction(tr("Qt Documentacion"),this);
    mnuAyudaDoc_->addAction(actAyudaDoc1);
    connect(actAyudaDoc1, SIGNAL(triggered()),this,SLOT(abrirURL()));
}


void MainWindow::abrirURL()
{
    QDesktopServices::openUrl(QUrl("http://qt-project.org/doc/", QUrl::TolerantMode));
}


void MainWindow::AcercaDe()
{
    QMessageBox msg(this);
    msg.setWindowTitle(tr("Acerca de"));
    msg.setText("<p>Gestor de tareas (en Qt!)</p><p>v 1.0</p>");
    msg.addButton("OK",QMessageBox::AcceptRole);
    if (msg.exec())
        close();
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

void MainWindow::onTareasCellChanged(int row)
{
    if (addingTarea_)
        return;
    addingTarea_ = true;
    int checked = (ui->tblTareas->item(row, 4)->checkState() == Qt::Checked);
    QSqlQuery query;

    if (ui->tblTareas->item(row, 0)->data(Qt::UserRole).isNull())
    {
        query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, id_categ) "
                 "VALUES ("+QString("'%1','%2','%3','%4','%5');" ).arg(ui->tblTareas->item(row, 0)->text()).arg(ui->tareaDescription->toPlainText()).arg(ui->tblTareas->item(row, 1)->text()).arg(checked).arg(ui->comboCategorias->currentData().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    }
    else
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " ).arg(ui->tblTareas->item(row, 0)->text()).arg(ui->tareaDescription->toPlainText()).arg(ui->tblTareas->item(row, 1)->text()).arg(checked).arg(ui->comboCategorias->currentData().toInt()) + "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    addingTarea_ = false;
}

void MainWindow::onLoadTareas()
{
    addingTarea_ = true;
    while (ui->tblTareas->rowCount())
        ui->tblTareas->removeRow(0);

    QSqlQuery q = db_.exec("SELECT * "
                 "FROM tareas "
                 "WHERE id_categ = " + ui->comboCategorias->currentData().toString());

    QSqlQuery qCategoria = db_.exec("SELECT * "
                                    "FROM categorias "
                                    "WHERE id = " + ui->comboCategorias->currentData().toString());
    qCategoria.next();
    while (q.next())
    {
        int rowNumber = ui->tblTareas->rowCount();
        int id = GetField(q, "id").toInt();
        ui->tblTareas->insertRow(rowNumber);

        QTableWidgetItem* item = new QTableWidgetItem(GetField(q, "name").toString());
        item->setData(Qt::UserRole, id);
        ui->tblTareas->setItem(rowNumber, 0, item);
        ui->tblTareas->setItem(rowNumber, 1, new QTableWidgetItem(GetField(q, "date").toString()));
        ui->tblTareas->setItem(rowNumber, 2, new QTableWidgetItem(GetField(qCategoria, "name").toString()));

        item = new QTableWidgetItem("");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        if (GetField(q, "done").toInt())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tblTareas->setItem(rowNumber, 4, item);
    }
    ui->tblTareas->setSortingEnabled(true);
    addingTarea_ = false;
}


void MainWindow::onAddCategoria()
{
    addingCategoria_ = true;
    ui->tableCategorias->insertRow(ui->tableCategorias->rowCount());
    ui->tableCategorias->setItem(ui->tableCategorias->rowCount()-1, 0, new QTableWidgetItem(""));
    ui->tableCategorias->setItem(ui->tableCategorias->rowCount()-1, 1, new QTableWidgetItem(""));
    addingCategoria_ = false;
}


void MainWindow::onCategoriasCellChanged(int row)
{
    if (addingCategoria_)
        return;
    addingCategoria_ = true;
    QSqlQuery query;

    if (ui->tableCategorias->item(row, 0)->data(Qt::UserRole).isNull())
    {
        query = db_.exec("INSERT INTO categorias (name, descripcion) "
                 "VALUES ("+QString("'%1','%2');" ).arg(ui->tableCategorias->item(row, 0)->text()).arg(ui->tableCategorias->item(row, 1)->text()));
        ui->tableCategorias->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    }
    else
        query = db_.exec("UPDATE categorias "
                 "SET "+QString("name='%1',descripcion='%2' ").arg(ui->tableCategorias->item(row, 0)->text()).arg(ui->tableCategorias->item(row, 1)->text()) + "WHERE id = " + ui->tableCategorias->item(row, 0)->data(Qt::UserRole).toString() + ";");
    addingCategoria_ = false;
}


void MainWindow::onLoadCategorias()
{
    addingCategoria_ = true;

    while (ui->tableCategorias->rowCount())
        ui->tableCategorias->removeRow(0);

    QSqlQuery qCategorias = db_.exec("SELECT * FROM categorias;");

    while (qCategorias.next())
    {
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



void MainWindow::onAddEtiqueta()
{
    addingEtiqueta_ = true;
    ui->tableEtiquetas->insertRow(ui->tableEtiquetas->rowCount());
    ui->tableEtiquetas->setItem(ui->tableEtiquetas->rowCount()-1, 0, new QTableWidgetItem(""));
    addingEtiqueta_ = false;
}


void MainWindow::onEtiquetasCellChanged(int row)
{
    if (addingEtiqueta_)
        return;

    addingEtiqueta_ = true;
    QSqlQuery query;

    if (ui->tableEtiquetas->item(row, 0)->data(Qt::UserRole).isNull())
    {
        query = db_.exec("INSERT INTO etiquetas(name) "
                 "VALUES ("+QString("'%1');" )\
                 .arg(ui->tableEtiquetas->item(row, 0)->text()));
        ui->tableEtiquetas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    }
    else
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1'" ).arg(ui->tableEtiquetas->item(row, 0)->text()) + "WHERE id = " + ui->tableEtiquetas->item(row, 0)->data(Qt::UserRole).toString() + ";");
    addingEtiqueta_ = false;
}


void MainWindow::onLoadEtiquetas()
{
    addingEtiqueta_ = true;

    while (ui->tableEtiquetas->rowCount())
        ui->tableEtiquetas->removeRow(0);

    QSqlQuery qEtiquetas = db_.exec("SELECT * FROM etiquetas;");

    while (qEtiquetas.next())
    {
        ui->comboEtiquetas->addItem(GetField(qEtiquetas,"name").toString(), GetField(qEtiquetas,"id").toInt());
        int rowNumber = ui->tableEtiquetas->rowCount();
        ui->tableEtiquetas->insertRow(rowNumber);
        QTableWidgetItem* nombre = new QTableWidgetItem(GetField(qEtiquetas, "name").toString());
        ui->tableEtiquetas->setItem(rowNumber, 0, nombre);
    }
    ui->tableEtiquetas->setSortingEnabled(true);
}


void MainWindow::onDescriptionTask(int row, int col)
{
    QSqlQuery q = db_.exec( "SELECT descripcion "
                            "FROM tareas "
                            "WHERE name = '" + ui->tblTareas->item(row, 0)->text() + "';");
    q.next();
    ui->tareaDescription->setText(GetField(q, "descripcion").toString());
}

void MainWindow::onEtiquetasTask(int row, int col)
{
    QSqlQuery qTarea = db_.exec("SELECT id "
                                "FROM tareas "
                                "WHERE name = '" + ui->tblTareas->item(row, 0)->text() + "';");
    qTarea.next();
    QString idTarea = GetField(qTarea, "id").toString();

    QSqlQuery qEtiquetas = db_.exec("SELECT * "
                                    "FROM etiquetas;");

    QSqlQuery qAsignados = db_.exec("SELECT * "
                                    "FROM tareas_etiq "
                                    "WHERE id = " + GetField(qTarea,"id").toString());
    int i = 0;
    while (qEtiquetas.next())
    {
        QSqlQuery qIdElegido = db_.exec("SELECT * "
                                        "FROM etiquetas "
                                        "WHERE name='" + ui->tareaEtiquetas->item(i, 1)->text() + "';");
        qIdElegido.next();
        QSqlQuery qAsignados = db_.exec("SELECT * "
                                        "FROM tareas_etiq "
                                        "WHERE ((id_tarea = " + GetField(qTarea,"id").toString() +
                                        ") & (id_etiq= " + GetField(qIdElegido, "id").toString() + "));");
        i++;
    }
}

void MainWindow::initTableEtiquetas()
{
    QSqlQuery qEtiquetas = db_.exec("SELECT * "
                                    "FROM etiquetas;");
    while (qEtiquetas.next())
    {
        int rowNumber = ui->tareaEtiquetas->rowCount();
        ui->tareaEtiquetas->insertRow(rowNumber);
        QTableWidgetItem* nombre = new QTableWidgetItem(GetField(qEtiquetas, "name").toString());
        ui->tareaEtiquetas->setItem(rowNumber, 1, nombre);
    }
}
