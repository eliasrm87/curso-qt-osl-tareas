#ifndef ADDCATEGORYDIALOG_H
#define ADDCATEGORYDIALOG_H

#include <QFrame>
#include <QStringList>

namespace Ui {
class AddCategoryDialog;
}

class AddCategoryDialog: public QFrame {
  Q_OBJECT

public:
  explicit AddCategoryDialog(QWidget *parent = 0);
  ~AddCategoryDialog();

signals:
  void createCategory(QString category);

public slots:
  void setExistingCategories(QStringList categories);

private slots:
  void onTextChanged(QString text);
  void onCreate();

private:
  Ui::AddCategoryDialog *ui;
  QStringList categories_;

};

#endif // ADDCATEGORYDIALOG_H
