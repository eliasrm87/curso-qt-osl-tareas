/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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
    QAction *actionSalir;
    QAction *actionNueva;
    QAction *categoriaNueva;
    QAction *etiquetaNueva;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tareas;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_7;
    QComboBox *comboEtiquetas;
    QTextEdit *tareaDescription;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QComboBox *comboCategorias;
    QTableWidget *tableTareas;
    QWidget *categorias;
    QGridLayout *gridLayout_3;
    QTableWidget *tableCategorias;
    QWidget *etiquetas;
    QGridLayout *gridLayout_5;
    QTableWidget *tableEtiquetas;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuTarea;
    QMenu *menuCategorias;
    QMenu *menuEtiquetas;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(635, 420);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        actionNueva = new QAction(MainWindow);
        actionNueva->setObjectName(QStringLiteral("actionNueva"));
        categoriaNueva = new QAction(MainWindow);
        categoriaNueva->setObjectName(QStringLiteral("categoriaNueva"));
        etiquetaNueva = new QAction(MainWindow);
        etiquetaNueva->setObjectName(QStringLiteral("etiquetaNueva"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tareas = new QWidget();
        tareas->setObjectName(QStringLiteral("tareas"));
        gridLayout_4 = new QGridLayout(tareas);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(tareas);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        comboEtiquetas = new QComboBox(groupBox);
        comboEtiquetas->setObjectName(QStringLiteral("comboEtiquetas"));

        gridLayout_7->addWidget(comboEtiquetas, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 1, 1, 1);

        tareaDescription = new QTextEdit(tareas);
        tareaDescription->setObjectName(QStringLiteral("tareaDescription"));
        tareaDescription->setMinimumSize(QSize(0, 75));
        tareaDescription->setMaximumSize(QSize(16777215, 75));

        gridLayout_4->addWidget(tareaDescription, 4, 0, 1, 2);

        groupBox_2 = new QGroupBox(tareas);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        comboCategorias = new QComboBox(groupBox_2);
        comboCategorias->setObjectName(QStringLiteral("comboCategorias"));

        gridLayout_6->addWidget(comboCategorias, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        tableTareas = new QTableWidget(tareas);
        if (tableTareas->columnCount() < 5)
            tableTareas->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTareas->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTareas->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTareas->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableTareas->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableTareas->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableTareas->setObjectName(QStringLiteral("tableTareas"));

        gridLayout_4->addWidget(tableTareas, 3, 0, 1, 2);

        tabWidget->addTab(tareas, QString());
        categorias = new QWidget();
        categorias->setObjectName(QStringLiteral("categorias"));
        gridLayout_3 = new QGridLayout(categorias);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableCategorias = new QTableWidget(categorias);
        if (tableCategorias->columnCount() < 2)
            tableCategorias->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableCategorias->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableCategorias->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableCategorias->setObjectName(QStringLiteral("tableCategorias"));

        gridLayout_3->addWidget(tableCategorias, 0, 0, 1, 1);

        tabWidget->addTab(categorias, QString());
        etiquetas = new QWidget();
        etiquetas->setObjectName(QStringLiteral("etiquetas"));
        gridLayout_5 = new QGridLayout(etiquetas);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tableEtiquetas = new QTableWidget(etiquetas);
        if (tableEtiquetas->columnCount() < 1)
            tableEtiquetas->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setText(QStringLiteral("Nombre"));
        tableEtiquetas->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        tableEtiquetas->setObjectName(QStringLiteral("tableEtiquetas"));

        gridLayout_5->addWidget(tableEtiquetas, 0, 0, 1, 1);

        tabWidget->addTab(etiquetas, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 635, 20));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        menuTarea = new QMenu(menubar);
        menuTarea->setObjectName(QStringLiteral("menuTarea"));
        menuCategorias = new QMenu(menubar);
        menuCategorias->setObjectName(QStringLiteral("menuCategorias"));
        menuEtiquetas = new QMenu(menubar);
        menuEtiquetas->setObjectName(QStringLiteral("menuEtiquetas"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuTarea->menuAction());
        menubar->addAction(menuCategorias->menuAction());
        menubar->addAction(menuEtiquetas->menuAction());
        menuArchivo->addAction(actionSalir);
        menuTarea->addAction(actionNueva);
        menuCategorias->addAction(categoriaNueva);
        menuEtiquetas->addAction(etiquetaNueva);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionNueva->setText(QApplication::translate("MainWindow", "Nueva tarea", 0));
        categoriaNueva->setText(QApplication::translate("MainWindow", "Nueva categoria", 0));
        etiquetaNueva->setText(QApplication::translate("MainWindow", "Nueva etiqueta", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Etiquetas", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Categorias", 0));
        QTableWidgetItem *___qtablewidgetitem = tableTareas->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Tarea", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableTareas->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Fecha", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableTareas->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Categoria", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableTareas->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Etiquetas", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableTareas->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Realizado", 0));
        tabWidget->setTabText(tabWidget->indexOf(tareas), QApplication::translate("MainWindow", "Tareas", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableCategorias->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Nombre", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableCategorias->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Descripcion", 0));
        tabWidget->setTabText(tabWidget->indexOf(categorias), QApplication::translate("MainWindow", "Categorias", 0));
        tabWidget->setTabText(tabWidget->indexOf(etiquetas), QApplication::translate("MainWindow", "Etiquetas", 0));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
        menuTarea->setTitle(QApplication::translate("MainWindow", "Tarea", 0));
        menuCategorias->setTitle(QApplication::translate("MainWindow", "Categorias", 0));
        menuEtiquetas->setTitle(QApplication::translate("MainWindow", "Etiquetas", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
