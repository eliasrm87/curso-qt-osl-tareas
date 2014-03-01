/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Task;
    QAction *actionDelete_Task;
    QAction *actionSelect_Today;
    QAction *actionAdd_Category;
    QAction *actionNueva_Tarea;
    QAction *actionCategorias;
    QAction *actionCategorias_2;
    QAction *actionEtiquetas;
    QAction *actionVer_Hoy;
    QWidget *centralwidget;
    QCalendarWidget *calendar_;
    QLabel *label;
    QTextEdit *textEditName;
    QPushButton *pushButton;
    QTextEdit *textEditDesc;
    QLabel *label_2;
    QTextEdit *textEditDia;
    QLabel *label_3;
    QTextEdit *textEditCateg;
    QLabel *label_4;
    QListWidget *listWidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(722, 473);
        MainWindow->setMinimumSize(QSize(722, 473));
        MainWindow->setMaximumSize(QSize(722, 473));
        actionAdd_Task = new QAction(MainWindow);
        actionAdd_Task->setObjectName(QStringLiteral("actionAdd_Task"));
        actionDelete_Task = new QAction(MainWindow);
        actionDelete_Task->setObjectName(QStringLiteral("actionDelete_Task"));
        actionSelect_Today = new QAction(MainWindow);
        actionSelect_Today->setObjectName(QStringLiteral("actionSelect_Today"));
        actionAdd_Category = new QAction(MainWindow);
        actionAdd_Category->setObjectName(QStringLiteral("actionAdd_Category"));
        actionNueva_Tarea = new QAction(MainWindow);
        actionNueva_Tarea->setObjectName(QStringLiteral("actionNueva_Tarea"));
        actionCategorias = new QAction(MainWindow);
        actionCategorias->setObjectName(QStringLiteral("actionCategorias"));
        actionCategorias_2 = new QAction(MainWindow);
        actionCategorias_2->setObjectName(QStringLiteral("actionCategorias_2"));
        actionEtiquetas = new QAction(MainWindow);
        actionEtiquetas->setObjectName(QStringLiteral("actionEtiquetas"));
        actionVer_Hoy = new QAction(MainWindow);
        actionVer_Hoy->setObjectName(QStringLiteral("actionVer_Hoy"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        calendar_ = new QCalendarWidget(centralwidget);
        calendar_->setObjectName(QStringLiteral("calendar_"));
        calendar_->setGeometry(QRect(0, 0, 341, 191));
        calendar_->setStyleSheet(QStringLiteral("font: 13pt \"Source Code Pro\";"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 210, 91, 31));
        textEditName = new QTextEdit(centralwidget);
        textEditName->setObjectName(QStringLiteral("textEditName"));
        textEditName->setGeometry(QRect(110, 210, 201, 31));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 390, 91, 32));
        textEditDesc = new QTextEdit(centralwidget);
        textEditDesc->setObjectName(QStringLiteral("textEditDesc"));
        textEditDesc->setGeometry(QRect(110, 250, 201, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 250, 91, 31));
        textEditDia = new QTextEdit(centralwidget);
        textEditDia->setObjectName(QStringLiteral("textEditDia"));
        textEditDia->setGeometry(QRect(110, 290, 201, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 290, 91, 31));
        textEditCateg = new QTextEdit(centralwidget);
        textEditCateg->setObjectName(QStringLiteral("textEditCateg"));
        textEditCateg->setGeometry(QRect(110, 330, 201, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 330, 91, 31));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(340, 0, 381, 441));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 390, 91, 32));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(true);
        pushButton_3->setGeometry(QRect(240, 390, 87, 32));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 722, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAdd_Task->setText(QApplication::translate("MainWindow", "Add Task", 0));
        actionDelete_Task->setText(QApplication::translate("MainWindow", "Delete Task", 0));
        actionSelect_Today->setText(QApplication::translate("MainWindow", "Select Today", 0));
        actionAdd_Category->setText(QApplication::translate("MainWindow", "Add Category", 0));
        actionNueva_Tarea->setText(QApplication::translate("MainWindow", "Nueva Tarea", 0));
        actionCategorias->setText(QApplication::translate("MainWindow", "Categorias", 0));
        actionCategorias_2->setText(QApplication::translate("MainWindow", "Categorias", 0));
        actionEtiquetas->setText(QApplication::translate("MainWindow", "Etiquetas", 0));
        actionVer_Hoy->setText(QApplication::translate("MainWindow", "Ver Hoy", 0));
        label->setText(QApplication::translate("MainWindow", "Nombre:", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Actualizar", 0));
        label_2->setText(QApplication::translate("MainWindow", "Descripcion:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Dia:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Gategoria:", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Nueva", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Borrar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
