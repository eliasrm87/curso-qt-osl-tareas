#ifndef JDIALOGO_H
#define JDIALOGO_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QSqlDatabase>
#include <dbconnection.h>
#include <QDebug>

class JDialog : public QDialog
{
    Q_OBJECT
public:
    explicit JDialog(QWidget *parent = 0);

private:
    QPushButton* aceptar_;
    QPushButton* cancelar_;
    QGridLayout* layout_;
    QLineEdit* nombre_;
    QLineEdit* fecha_;
    QLineEdit* descripcion_;
    QLineEdit* hecha_;

private slots:
    void lanzaSenal();

signals:
    void anadido(QString nombre, QString fecha, QString descripcion, QString hecha);
};

#endif // JDIALOGO_H
