/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myopenglwidget.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionFlight_Mechanics;
    QAction *actionSearch;
    QAction *actionSearch_and_Engage;
    QAction *actionSurvivability;
    QAction *actionSurveillance;
    QAction *actionPerform_New;
    QAction *actionPlay_Existing;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    MyOpenGLWidget *openGLWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCustomPlot *widget_2;
    QCustomPlot *widget;
    QGroupBox *groupBox_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuVignette;
    QMenu *menuOperations_Research;
    QMenu *menuInverse_Simulation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1084, 650);
        MainWindow->setMinimumSize(QSize(500, 0));
        MainWindow->setStyleSheet(QLatin1String("QMainWindow{\n"
"background-color: #004;\n"
"}\n"
"\n"
"QWidget{\n"
"background-color: #004;\n"
"color: #fff;\n"
"}\n"
"\n"
"QToolBar{\n"
"background-color: #004;\n"
"padding: 5px;\n"
"}\n"
"\n"
"QMenuBar{\n"
"background-color: #004;\n"
"color: #fff;\n"
"}\n"
"\n"
"QMenuBar::item{\n"
"background-color: #004;\n"
"color: #fff;\n"
"}\n"
"\n"
"QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0.67, y1:1, x2:0.653864, y2:0, stop:0 rgba(170, 0, 0, 255), stop:1 rgba(255, 170, 127, 255));\n"
"color: rgb(255, 255, 255);\n"
"border-width: 2px;\n"
"border-color: #000;\n"
"border-style: solid;\n"
"border-radius: 10;\n"
"padding: 2px;\n"
"font-size: 10px;\n"
"font-weight: bold;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 50px;\n"
"max-width: 50px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Icons/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Icons/Save-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionFlight_Mechanics = new QAction(MainWindow);
        actionFlight_Mechanics->setObjectName(QStringLiteral("actionFlight_Mechanics"));
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QStringLiteral("actionSearch"));
        actionSearch_and_Engage = new QAction(MainWindow);
        actionSearch_and_Engage->setObjectName(QStringLiteral("actionSearch_and_Engage"));
        actionSurvivability = new QAction(MainWindow);
        actionSurvivability->setObjectName(QStringLiteral("actionSurvivability"));
        actionSurveillance = new QAction(MainWindow);
        actionSurveillance->setObjectName(QStringLiteral("actionSurveillance"));
        actionPerform_New = new QAction(MainWindow);
        actionPerform_New->setObjectName(QStringLiteral("actionPerform_New"));
        actionPlay_Existing = new QAction(MainWindow);
        actionPlay_Existing->setObjectName(QStringLiteral("actionPlay_Existing"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(1084, 0));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        openGLWidget = new MyOpenGLWidget(splitter);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(500, 300));
        splitter->addWidget(openGLWidget);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(300, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QCustomPlot(groupBox);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget_2);

        widget = new QCustomPlot(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);

        splitter->addWidget(groupBox);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMinimumSize(QSize(0, 100));
        groupBox_2->setMaximumSize(QSize(16777215, 150));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 30, 64, 21));

        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1084, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuVignette = new QMenu(menuBar);
        menuVignette->setObjectName(QStringLiteral("menuVignette"));
        menuOperations_Research = new QMenu(menuVignette);
        menuOperations_Research->setObjectName(QStringLiteral("menuOperations_Research"));
        menuInverse_Simulation = new QMenu(menuVignette);
        menuInverse_Simulation->setObjectName(QStringLiteral("menuInverse_Simulation"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setStyleSheet(QStringLiteral(""));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuVignette->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuVignette->addAction(menuOperations_Research->menuAction());
        menuVignette->addAction(menuInverse_Simulation->menuAction());
        menuVignette->addAction(actionFlight_Mechanics);
        menuVignette->addAction(actionSurvivability);
        menuVignette->addAction(actionSurveillance);
        menuOperations_Research->addAction(actionSearch);
        menuOperations_Research->addAction(actionSearch_and_Engage);
        menuInverse_Simulation->addAction(actionPerform_New);
        menuInverse_Simulation->addAction(actionPlay_Existing);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenGL Testing Application", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "Create a New Scene", 0));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open an Existing Scene XML File", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0));
        actionFlight_Mechanics->setText(QApplication::translate("MainWindow", "Flight Mechanics", 0));
        actionSearch->setText(QApplication::translate("MainWindow", "Search", 0));
        actionSearch_and_Engage->setText(QApplication::translate("MainWindow", "Search and Engage", 0));
        actionSurvivability->setText(QApplication::translate("MainWindow", "Survivability", 0));
        actionSurveillance->setText(QApplication::translate("MainWindow", "Surveillance", 0));
        actionPerform_New->setText(QApplication::translate("MainWindow", "Perform New", 0));
        actionPlay_Existing->setText(QApplication::translate("MainWindow", "Play Existing", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Animated Plots", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Simulation...", 0));
        pushButton->setText(QApplication::translate("MainWindow", "RUN", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuVignette->setTitle(QApplication::translate("MainWindow", "Vignette", 0));
        menuOperations_Research->setTitle(QApplication::translate("MainWindow", "Operations Research", 0));
        menuInverse_Simulation->setTitle(QApplication::translate("MainWindow", "Inverse Simulation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
