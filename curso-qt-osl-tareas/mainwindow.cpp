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
              "id_etiq INTEGER,"
              "PRIMARY KEY(id_tarea, id_etiq));");

    connect(ui->actionNuevaTarea, SIGNAL(triggered()), this, SLOT(onAddTarea()));
    connect(ui->tblTareas, SIGNAL(cellChanged(int,int)), this, SLOT(onTareasCellChanged(int,int)));
    connect(ui->tblTareas, SIGNAL(cellClicked(int,int)), this, SLOT(onSelectCell(int,int)));
    connect(ui->txtTareaDescr, SIGNAL(textChanged()), this, SLOT(onTareaDescrChanged()));
    connect(ui->comboCategoria, SIGNAL(currentIndexChanged(int)), this, SLOT(onLoadTareas()));
    connect(ui->comboEtiqueta, SIGNAL(currentIndexChanged(int)), this, SLOT(onFilterEtiquetas(int)));
    connect(ui->actionNuevaCateg, SIGNAL(triggered()), this, SLOT(onAddCategoria()));
    connect(ui->actionNuevaEtiq, SIGNAL(triggered()), this, SLOT(onAddEtiqueta()));
    connect(&labelsModel_, SIGNAL(checkChanged(int)), this, SLOT(onUpdateEtiquetas(int)));

    ui->tblCateg->setModel(&categoriesModel_);
    ui->comboCategoria->setModel(&categoriesModel_);
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
  qDebug() << "onAddTarea()";

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

  qDebug() << "onAddCategoria()";

  cat_dialog_ = new AddCategoryDialog;
  QStringList categories = categoriesModel_.stringList();

  cat_dialog_->setExistingCategories(categories);
  cat_dialog_->setWindowModality(Qt::ApplicationModal);

  connect(cat_dialog_, SIGNAL(createCategory(QString)), this, SLOT(onCreateCategoria(QString)));

  cat_dialog_->setVisible(true);
  cat_dialog_->show();
}

void MainWindow::onAddEtiqueta() {
  qDebug() << "onAddEtiqueta()";

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
  qDebug() << "onLoadTareas()";

    addingTarea_ = true;

    while (ui->tblTareas->rowCount())
        ui->tblTareas->removeRow(0);

    //Obtenemos las tareas
    int row = ui->comboCategoria->currentIndex();
    QVariant catData = categoriesModel_.data(categoriesModel_.index(row), Qt::UserRole);

    QString query = "SELECT * FROM tareas ";
    if (!catData.isNull() && catData.toInt() != -1)
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
  qDebug() << "onLoadCategorias()";

  // Categoría general para todas las categorías
  int row = categoriesModel_.rowCount();
  categoriesModel_.insertRow(row);

  QModelIndex idx = categoriesModel_.index(row);
  categoriesModel_.setData(idx, "Todas");
  categoriesModel_.setData(idx, -1, Qt::UserRole);

  //Obtenemos las categorias
  QSqlQuery q = db_.exec("SELECT * "
                         "FROM categorias;");

  while (q.next()) {
    row = categoriesModel_.rowCount();
    categoriesModel_.insertRow(row);

    idx = categoriesModel_.index(row);
    categoriesModel_.setData(idx, GetField(q,"name"));
    categoriesModel_.setData(idx, GetField(q,"id"), Qt::UserRole);
  }
}

void MainWindow::onLoadEtiquetas() {
  qDebug() << "onLoadEtiquetas()";

  //Obtenemos las etiquetas
  QSqlQuery q = db_.exec("SELECT * "
                         "FROM etiquetas;");

  while (q.next()) {
      //Añadimos la etiqueta al combo y como userData su ID
      labelsModel_.addLabel(GetField(q, "name").toString(), Qt::Unchecked, GetField(q, "id"));
  }
}

void MainWindow::onFilterEtiquetas(int index) {
  qDebug() << "onFilterEtiquetas()";


}

void MainWindow::onTareasCellChanged(int row, int /*column*/) {
    if (addingTarea_)
        return;

    qDebug() << "onTareasCellChanged()";

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
  qDebug() << "onSelectCell()";

  QSqlQuery q = db_.exec("SELECT descripcion "
                         "FROM tareas "
                         "WHERE id = " + ui->tblTareas->item(row, 0)->data(Qt::UserRole).toString() + ";");

  QString desc;
  if (q.next())
    desc = GetField(q, "descripcion").toString();

  ui->txtTareaDescr->setText(desc);
}

void MainWindow::onTareaDescrChanged() {
  qDebug() << "onTareaDescrChanged()";

  onTareasCellChanged(ui->tblTareas->currentRow(), ui->tblTareas->currentColumn());
}

void MainWindow::onCreateCategoria(QString cat) {
  qDebug() << "onCreateCategoria()";

  QSqlQuery query = db_.exec("INSERT INTO categorias (name) "
                             "VALUES (" + QString("'%1');")
                             .arg(cat));

  int row = categoriesModel_.rowCount();
  categoriesModel_.insertRow(row);
  QModelIndex idx = categoriesModel_.index(row);

  categoriesModel_.setData(idx, cat);
  categoriesModel_.setData(idx, query.lastInsertId(), Qt::UserRole);
}

void MainWindow::onCreateEtiqueta(QString etq) {
  qDebug() << "onCreateEtiqueta()";

  QSqlQuery query = db_.exec("INSERT INTO etiquetas (name) "
                             "VALUES (" + QString("'%1');")
                             .arg(etq));

  labelsModel_.addLabel(etq, Qt::Unchecked, query.lastInsertId());
}

void MainWindow::onUpdateEtiquetas(int row) {
  qDebug() << "onUpdateEtiquetas()";

  QModelIndex index = labelsModel_.index(row, 0);
  QTableWidgetItem* itm = ui->tblTareas->currentItem();

  if (itm) {
    bool checked = labelsModel_.data(index, Qt::CheckStateRole).toBool();
    int id_tarea = itm->data(Qt::UserRole).toInt();
    int id_etiq = labelsModel_.data(index, Qt::UserRole).toInt();

    QString queryStr;
    if (checked)
      queryStr = QString("INSERT INTO tareas_etiq (id_tarea, id_etiq) "
                         "VALUES (%1, %2);").arg(id_tarea).arg(id_etiq);
    else
      queryStr = QString("DELETE FROM tareas_etiq "
                         "WHERE id_tarea = %1 AND id_etiq = %2;").arg(id_tarea).arg(id_etiq);

    db_.exec(queryStr);
  }
}
