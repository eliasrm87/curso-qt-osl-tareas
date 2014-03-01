#include "jdialog.h"

JDialog::JDialog(QWidget *parent) :
    QDialog(parent) {
    aceptar_ = new QPushButton("Aceptar", this);
    cancelar_ = new QPushButton("Cancelar", this);
    layout_ = new QGridLayout;
    nombre_ = new QLineEdit;
    fecha_ = new QLineEdit;
    descripcion_ = new QLineEdit;
    hecha_ = new QLineEdit;

    QLabel* etiNombre = new QLabel("Nombre: ");
    QLabel* etiFecha = new QLabel("Fecha: ");
    QLabel* etiDescripcion = new QLabel("Descripción: ");
    QLabel* etiHecha = new QLabel("Hecha: ");

    layout_->addWidget(etiNombre, 0, 0, 1, 1);
    layout_->addWidget(nombre_, 0, 1, 1, 3);

    layout_->addWidget(etiFecha, 1, 0, 1, 1);
    layout_->addWidget(fecha_, 1, 1, 1, 3);

    layout_->addWidget(etiDescripcion, 2, 0, 1, 1);
    layout_->addWidget(descripcion_, 2, 1, 1, 3);

    layout_->addWidget(etiHecha, 3, 0, 1, 1);
    layout_->addWidget(hecha_, 3, 1, 1, 3);

    layout_->addWidget(aceptar_, 4, 3, 1, 1);
    layout_->addWidget(cancelar_, 4, 2, 1, 1);

    setLayout(layout_);

    connect(cancelar_, SIGNAL(pressed()), this, SLOT(close()));
    connect(aceptar_, SIGNAL(pressed()), this, SLOT(lanzaSenal()));

}

void JDialog::lanzaSenal() {
    emit anadido(nombre_->text(), fecha_->text(), descripcion_->text(), hecha_->text());
    close();
}
