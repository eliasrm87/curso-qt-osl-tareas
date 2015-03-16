#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addcategorydialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),
  cat_dialog_(0), label_dialog_(0) {
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
    connect(ui->tblTareas, SIGNAL(cellClicked(int,int)), this, SLOT(onSelectCell(int,int)));
    connect(ui->txtTareaDescr, SIGNAL(textChanged()), this, SLOT(onTareaDescrChanged()));
    connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));
    connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
    connect(ui->actionNuevaEtiq, SIGNAL(triggered()), this, SLOT(onAddEtiqueta()));

    ui->tblEtiq->setModel(&labelsModel_);
    ui->comboEtiqueta->setModel(&labelsModel_);
    ui->listEtiqueta->setModel(&labelsModel_);

    addingTarea_ = false;

    onLoadCategorias();
    onLoadEtiquetas();

    // Activamos el sorting
    ui->tblCateg->setSortingEnabled(true);
    ui->tblEtiq->setSortingEnabled(true);
    ui->tblTareas->setSortingEnabled(true);

    ui->comboCategoria->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    if (cat_dialog_)
        delete cat_dialog_;

    if (label_dialog_)
        delete label_dialog_;

    delete ui;
}

void MainWindow::onAddTarea() {
    // No añadimos tareas si está seleccionada la categoría "Todas"
    if (ui->comboCategoria->currentData().toInt() == -1)
        return;

    addingTarea_ = true;

    int tareaNumber = ui->tblTareas->rowCount();
    ui->tblTareas->insertRow(tareaNumber);

    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);

    ui->tblTareas->setItem(tareaNumber, 0, new QTableWidgetItem(""));
    ui->tblTareas->setItem(tareaNumber, 1, new QTableWidgetItem(""));
    ui->tblTareas->setItem(tareaNumber, 2, item);

    addingTarea_ = false;
}

void MainWindow::onAddCategoria() {
  if (cat_dialog_)
    delete cat_dialog_;

  cat_dialog_ = new AddCategoryDialog;
  QStringList categories;

  for (int i = 0; i < ui->comboCategoria->count(); ++i)
    categories.append(ui->comboCategoria->itemText(i));

  cat_dialog_->setExistingCategories(categories);
  cat_dialog_->setWindowModality(Qt::ApplicationModal);

  connect(cat_dialog_, SIGNAL(createCategory(QString)), this, SLOT(onCreateCategoria(QString)));

  cat_dialog_->setVisible(true);
  cat_dialog_->show();
}

void MainWindow::onAddEtiqueta() {
  if (label_dialog_)
    delete label_dialog_;

  label_dialog_ = new AddCategoryDialog;
  label_dialog_->setExistingCategories(labelsModel_.stringList());
  label_dialog_->setWindowModality(Qt::ApplicationModal);

  connect(label_dialog_, SIGNAL(createCategory(QString)), this, SLOT(onCreateEtiqueta(QString)));

  label_dialog_->setVisible(true);
  label_dialog_->show();
}

void MainWindow::onLoadTareas() {
    addingTarea_ = true;

    while (ui->tblTareas->rowCount())
        ui->tblTareas->removeRow(0);

    //Obtenemos las tareas
    QString query = "SELECT * FROM tareas ";
    QVariant catData = ui->comboCategoria->currentData();
    if (catData.toInt() != -1)
      query += "WHERE id_categ = " + catData.toString();

    QSqlQuery q = db_.exec(query);

    while (q.next()) {
        //Añadimos la tarea a la tabla de tareas
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

    addingTarea_ = false;
}

void MainWindow::onLoadCategorias() {
  // Categoría general para todas las categorías
  ui->comboCategoria->addItem("Todas", -1);

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
}

void MainWindow::onLoadEtiquetas() {
  //Obtenemos las etiquetas
  QSqlQuery q = db_.exec("SELECT * "
                         "FROM etiquetas;");

  while (q.next()) {
      //Añadimos la etiqueta al combo y como userData su ID
      labelsModel_.addLabel(GetField(q, "name").toString(), Qt::Unchecked, GetField(q, "id"));
  }
}

void MainWindow::onTareasCellChanged(int row, int /*column*/) {
    if (addingTarea_)
        return;

    addingTarea_ = true;

    int checked = (ui->tblTareas->item(row, 2)->checkState() == Qt::Checked);

    QSqlQuery query;
    QVariant taskID = ui->tblTareas->item(row, 0)->data(Qt::UserRole);

    if (taskID.isNull()) {
        query = db_.exec("INSERT INTO tareas (name, descripcion, date, done, id_categ) "
                 "VALUES (" + QString("'%1','%2','%3','%4','%5');")
                 .arg(ui->tblTareas->item(row, 0)->text())
                 .arg(ui->txtTareaDescr->toPlainText())
                 .arg(ui->tblTareas->item(row, 1)->text())
                 .arg(checked)
                 .arg(ui->comboCategoria->currentData().toInt()));
        ui->tblTareas->item(row, 0)->setData(Qt::UserRole, query.lastInsertId());
    }
    else {
        query = db_.exec("UPDATE tareas SET " +
                         QString("name='%1',descripcion='%2',date='%3',done='%4' ")
                         .arg(ui->tblTareas->item(row, 0)->text())
                         .arg(ui->txtTareaDescr->toPlainText())
                         .arg(ui->tblTareas->item(row, 1)->text())
                         .arg(checked) +
                         "WHERE id = " + taskID.toString() + ";");
    }

    addingTarea_ = false;
}

void MainWindow::onSelectCell(int row, int /*column*/) {
  QSqlQuery q = db_.exec("SELECT descripcion "
                         "FROM tareas "
                         "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");

  QString desc;
  if (q.next())
    desc = GetField(q, "descripcion").toString();

  ui->txtTareaDescr->setText(desc);
}

void MainWindow::onTareaDescrChanged() {
  onTareasCellChanged(ui->tblTareas->currentRow(), ui->tblTareas->currentColumn());
}

void MainWindow::onCreateCategoria(QString cat) {
  QSqlQuery query = db_.exec("INSERT INTO categorias (name) "
                             "VALUES (" + QString("'%1');")
                             .arg(cat));

  int index = ui->tblCateg->rowCount();
  ui->tblCateg->insertRow(index);
  ui->tblCateg->setItem(index, 0, new QTableWidgetItem(cat));

  ui->comboCategoria->addItem(cat, query.lastInsertId());
}

void MainWindow::onCreateEtiqueta(QString etq) {
  QSqlQuery query = db_.exec("INSERT INTO etiquetas (name) "
                             "VALUES (" + QString("'%1');")
                             .arg(etq));

  labelsModel_.addLabel(etq, Qt::Unchecked, query.lastInsertId());
}
