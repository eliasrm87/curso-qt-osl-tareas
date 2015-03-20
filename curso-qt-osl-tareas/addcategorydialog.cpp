#include "addcategorydialog.h"
#include "ui_addcategorydialog.h"

AddCategoryDialog::AddCategoryDialog(QWidget *parent): QFrame(parent), ui(new Ui::AddCategoryDialog) {
  ui->setupUi(this);

  setWindowTitle(tr("Añadir"));
  connect(ui->name_, SIGNAL(textEdited(QString)), this, SLOT(onTextChanged(QString)));
  connect(ui->cancel_, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->create_, SIGNAL(clicked()), this, SLOT(onCreate()));
  connect(ui->create_, SIGNAL(clicked()), this, SLOT(close()));
}

AddCategoryDialog::~AddCategoryDialog() {
  delete ui;
}

void AddCategoryDialog::setExistingCategories(QStringList categories) {
  categories_ = categories;
  onTextChanged(ui->name_->text());
}

void AddCategoryDialog::onTextChanged(QString text) {
  ui->create_->setEnabled(!categories_.contains(text, Qt::CaseInsensitive));
}

void AddCategoryDialog::onCreate() {
  emit(createCategory(ui->name_->text()));
}
