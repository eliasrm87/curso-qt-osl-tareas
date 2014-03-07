#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Setup database
    ConecToDb(db_, "tareas");

    db_.exec("CREATE TABLE IF NOT EXISTS tareas ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT,"
              "description TEXT"
              "date TEXT,"
              "category_id INT,"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS categories ("
              "id INTEGER,"
              "name TEXT,"
              "description TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS tag ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
              "name TEXT"
              ");");

    db_.exec("CREATE TABLE IF NOT EXISTS tag_tareas ("
              "tag_id INT,"
              "tareas_id INT"
              ");");

    dbList_ = new dblist(db_);
    setCentralWidget(dbList_);
}

MainWindow::~MainWindow()
{

}
