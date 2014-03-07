#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setup menu
    //Establecemos el tamaño inicial de la ventana
    this->setMaximumSize(maximumWidth(),maximumHeight());

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Gestor de tareas (SQLite)"));
    //setCentralWidget(this);

    //Mostramos la vista de la aplicacion inicial centrada respecto a la pantalla
    set_central_win();

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

/*    //Pestaña Ayuda
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
    //Activamos el sorting en la tabla de categorias
    ui->tblCateg->setSortingEnabled(true);

    ui->comboCategoria->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    mainMenu_->deleteLater();
    mnuArchivo_->deleteLater();
    actArchivoGuardar_->deleteLater();
    actArchivoCerrar_->deleteLater();
    mnuAyudaDoc_->deleteLater();
    actAyudaAcercaDe_->deleteLater();
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

void MainWindow::abrirURL(){
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
    } else {
        query = db_.exec("UPDATE tareas "
                 "SET "+QString("name='%1',descripcion='%2',date='%3',done='%4',id_categ='%5' " )\
                 .arg(ui->tblTareas->item(row, 0)->text())\
                 .arg(ui->txtTareaDescr->toPlainText())\
                 .arg(ui->tblTareas->item(row, 1)->text())\
                 .arg(checked)\
                 .arg(ui->comboCategoria->currentData().toInt()) +
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
