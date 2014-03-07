#include "dblist.h"

dblist::dblist(QSqlDatabase db, QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(600);
    layout_ = new QGridLayout(this);
    tableView_ = new QTableView(this);
    nameTarea_ = new QLabel("Tarea: ");
    dateTarea_ = new QLabel("Fecha: ");
    categoryTarea_ = new QLabel("Categoria: ");
    categoryTarea_->setWordWrap(true);
    categoryTarea_->setMinimumWidth(200);
    categoryTarea_->setMaximumWidth(200);
    categoryDescrTarea_ = new QLabel("Descripcion: ");
    categoryDescrTarea_->setWordWrap(true);
    categoryDescrTarea_->setMinimumWidth(200);
    categoryDescrTarea_->setMaximumWidth(200);
    tagTitle_ = new QLabel("Lista de etiquetas");
    tagsView_ = new QListView(this);
    tagsView_->setMinimumWidth(200);
    checkTarea_ = new QCheckBox("Realizada",this);

    layout_->addWidget(tableView_,0,0,1,3);
    layout_->addWidget(nameTarea_,1,0,1,1);
    layout_->addWidget(dateTarea_,1,1,1,1);
    layout_->addWidget(checkTarea_,1,2,1,1);
    layout_->addWidget(categoryTarea_,3,2,1,1);
    layout_->addWidget(categoryDescrTarea_,4,2,1,1);
    layout_->addWidget(tagTitle_,2,0,1,1);
    layout_->addWidget(tagsView_,3,0,2,1);
    db_ = db;

    onLoad();
}

void dblist::clicked(const QModelIndex &index)
{
    nameTarea_->setText(model_->item(index.row(),1)->text());
    dateTarea_->setText(model_->item(index.row(),2)->text());
    QSqlQuery query = db_.exec(QString("SELECT name,description FROM categories WHERE id = %1").arg(model_->item(index.row(),0)->text()));
    if(query.next()){
        categoryTarea_->setText("Categoria: "+GetField(query,"name").toString());
        categoryDescrTarea_->setText("Descripción: "+GetField(query,"description").toString());
    }
    else{
        categoryTarea_->setText("Categoria no asignada");
        categoryDescrTarea_->setText("No disponible");
    }
}

void dblist::onLoad()
{
    if(db_.isOpen()){
        QSqlQuery count= db_.exec("SELECT id FROM tareas;");
        int i = 0;
        while(count.next())
            i++;


        model_ = new QStandardItemModel(i,2,this);
        model_->setHorizontalHeaderItem(0,new QStandardItem("ID"));
        model_->setHorizontalHeaderItem(1,new QStandardItem("Tarea"));
        model_->setHorizontalHeaderItem(2,new QStandardItem("Fecha"));

        QSqlQuery query_= db_.exec("SELECT id,name,date FROM tareas;");
        int j=0;
        while(query_.next()){
            QStandardItem *row = new QStandardItem(GetField(query_,"id").toString());
            model_->setItem(j,0,row);
            row = new QStandardItem(GetField(query_,"name").toString());
            model_->setItem(j,1,row);
            row = new QStandardItem(GetField(query_,"date").toString());
            model_->setItem(j,2,row);
            j++;
        }
        tableView_->setModel(model_);
        tableView_->hideColumn(0);
        tableView_->setColumnWidth(1,250);
        tableView_->setColumnWidth(2,250);
        tableView_->setMinimumSize(530,100);
        connect(tableView_,SIGNAL(clicked(QModelIndex)),this,SLOT(clicked(QModelIndex)));
    }


}

