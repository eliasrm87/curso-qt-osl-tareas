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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNuevaTarea;
    QAction *actionNuevaCategoria;
    QAction *actionNuevaEtiqueta;
    QAction *actionCerrar;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *Pestanas;
    QWidget *tab_tareas;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QComboBox *comboBoxEtiqueta;
    QTextEdit *TextDescripcion;
    QTableWidget *TablaTareas;
    QComboBox *comboBoxCategorias;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QWidget *tab_categorias;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QTableWidget *TablaCategorias;
    QWidget *tab_etiquetas;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QTableWidget *TablaEtiquetas;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuCategorias;
    QMenu *menuEtiquetas;
    QMenu *menuTareas;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(385, 314);
        actionNuevaTarea = new QAction(MainWindow);
        actionNuevaTarea->setObjectName(QStringLiteral("actionNuevaTarea"));
        actionNuevaCategoria = new QAction(MainWindow);
        actionNuevaCategoria->setObjectName(QStringLiteral("actionNuevaCategoria"));
        actionNuevaEtiqueta = new QAction(MainWindow);
        actionNuevaEtiqueta->setObjectName(QStringLiteral("actionNuevaEtiqueta"));
        actionCerrar = new QAction(MainWindow);
        actionCerrar->setObjectName(QStringLiteral("actionCerrar"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Pestanas = new QTabWidget(centralwidget);
        Pestanas->setObjectName(QStringLiteral("Pestanas"));
        tab_tareas = new QWidget();
        tab_tareas->setObjectName(QStringLiteral("tab_tareas"));
        gridLayout_4 = new QGridLayout(tab_tareas);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        comboBoxEtiqueta = new QComboBox(tab_tareas);
        comboBoxEtiqueta->setObjectName(QStringLiteral("comboBoxEtiqueta"));

        gridLayout_3->addWidget(comboBoxEtiqueta, 1, 1, 1, 1);

        TextDescripcion = new QTextEdit(tab_tareas);
        TextDescripcion->setObjectName(QStringLiteral("TextDescripcion"));
        TextDescripcion->setMaximumSize(QSize(16777215, 100));

        gridLayout_3->addWidget(TextDescripcion, 7, 0, 1, 2);

        TablaTareas = new QTableWidget(tab_tareas);
        if (TablaTareas->columnCount() < 3)
            TablaTareas->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TablaTareas->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TablaTareas->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TablaTareas->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        TablaTareas->setObjectName(QStringLiteral("TablaTareas"));

        gridLayout_3->addWidget(TablaTareas, 6, 0, 1, 2);

        comboBoxCategorias = new QComboBox(tab_tareas);
        comboBoxCategorias->setObjectName(QStringLiteral("comboBoxCategorias"));

        gridLayout_3->addWidget(comboBoxCategorias, 1, 0, 1, 1);

        lineEdit = new QLineEdit(tab_tareas);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_3->addWidget(lineEdit, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(tab_tareas);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_3->addWidget(lineEdit_2, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        Pestanas->addTab(tab_tareas, QString());
        tab_categorias = new QWidget();
        tab_categorias->setObjectName(QStringLiteral("tab_categorias"));
        gridLayout_6 = new QGridLayout(tab_categorias);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        TablaCategorias = new QTableWidget(tab_categorias);
        if (TablaCategorias->columnCount() < 2)
            TablaCategorias->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TablaCategorias->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TablaCategorias->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        TablaCategorias->setObjectName(QStringLiteral("TablaCategorias"));

        gridLayout_5->addWidget(TablaCategorias, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        Pestanas->addTab(tab_categorias, QString());
        tab_etiquetas = new QWidget();
        tab_etiquetas->setObjectName(QStringLiteral("tab_etiquetas"));
        gridLayout_8 = new QGridLayout(tab_etiquetas);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        TablaEtiquetas = new QTableWidget(tab_etiquetas);
        if (TablaEtiquetas->columnCount() < 1)
            TablaEtiquetas->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TablaEtiquetas->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        TablaEtiquetas->setObjectName(QStringLiteral("TablaEtiquetas"));

        gridLayout_7->addWidget(TablaEtiquetas, 1, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        Pestanas->addTab(tab_etiquetas, QString());

        gridLayout->addWidget(Pestanas, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 385, 20));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        menuCategorias = new QMenu(menubar);
        menuCategorias->setObjectName(QStringLiteral("menuCategorias"));
        menuEtiquetas = new QMenu(menubar);
        menuEtiquetas->setObjectName(QStringLiteral("menuEtiquetas"));
        menuTareas = new QMenu(menubar);
        menuTareas->setObjectName(QStringLiteral("menuTareas"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuTareas->menuAction());
        menubar->addAction(menuCategorias->menuAction());
        menubar->addAction(menuEtiquetas->menuAction());
        menuArchivo->addAction(actionCerrar);
        menuCategorias->addAction(actionNuevaCategoria);
        menuEtiquetas->addAction(actionNuevaEtiqueta);
        menuTareas->addAction(actionNuevaTarea);

        retranslateUi(MainWindow);

        Pestanas->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestor de Tareas", 0));
        actionNuevaTarea->setText(QApplication::translate("MainWindow", "Nueva", 0));
        actionNuevaCategoria->setText(QApplication::translate("MainWindow", "Nueva", 0));
        actionNuevaEtiqueta->setText(QApplication::translate("MainWindow", "Nueva", 0));
        actionCerrar->setText(QApplication::translate("MainWindow", "Cerrar", 0));
        QTableWidgetItem *___qtablewidgetitem = TablaTareas->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Nombre", 0));
        QTableWidgetItem *___qtablewidgetitem1 = TablaTareas->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Fecha", 0));
        QTableWidgetItem *___qtablewidgetitem2 = TablaTareas->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Terminada", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "Categorias", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "Etiqueta", 0));
        Pestanas->setTabText(Pestanas->indexOf(tab_tareas), QApplication::translate("MainWindow", "Tareas", 0));
        QTableWidgetItem *___qtablewidgetitem3 = TablaCategorias->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Nombre", 0));
        QTableWidgetItem *___qtablewidgetitem4 = TablaCategorias->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Descripci\303\263n", 0));
        Pestanas->setTabText(Pestanas->indexOf(tab_categorias), QApplication::translate("MainWindow", "Categorias", 0));
        QTableWidgetItem *___qtablewidgetitem5 = TablaEtiquetas->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Tipo", 0));
        Pestanas->setTabText(Pestanas->indexOf(tab_etiquetas), QApplication::translate("MainWindow", "Etiquetas", 0));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
        menuCategorias->setTitle(QApplication::translate("MainWindow", "Categorias", 0));
        menuEtiquetas->setTitle(QApplication::translate("MainWindow", "Etiquetas", 0));
        menuTareas->setTitle(QApplication::translate("MainWindow", "Tareas", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
