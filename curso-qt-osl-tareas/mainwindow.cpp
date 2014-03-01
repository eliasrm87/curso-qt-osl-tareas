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

    connect(ui->actionVer_Hoy, SIGNAL(triggered()), this, SLOT( onCurrentDay() ));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT( onUpdate() ));

    ui->calendar_->setGridVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendar__selectionChanged()
{
    QDate selectedDate = ui->calendar_->selectedDate();

    QString unProcessTime = selectedDate.toString();
    QStringList listTime = unProcessTime.split(' ');

    QString processedDay = listTime.at(2);

    if (processedDay.length() == 1)
    {
        processedDay = "0" + processedDay;
    }

    QString processedName = "Nombre";
    ui->textEditName->setText(processedName);

    QString processedDesc = "Descripcion";
    ui->textEditDesc->setText(processedDesc);

    QString processedCateg = "Categoria";
    ui->textEditCateg->setText(processedCateg);

    QString processedTime = processedDay +"-"+ listTime.at(1) +"-"+ listTime.at(3);
    ui->textEditDia->setText(processedTime);
}

void MainWindow::onCurrentDay()
{
    ui->calendar_->showToday();
}

void MainWindow::onUpdate()
{
    QString unProcessTime = "hello";

    qDebug()<<"hello";

}

