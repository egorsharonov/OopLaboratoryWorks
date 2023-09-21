/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *priceLabel;
    QSpinBox *priceBox;
    QLabel *volumeLabel;
    QSpinBox *volumeBox;
    QPushButton *popButton;
    QPushButton *addButton;
    QPushButton *writeButton;
    QPushButton *readButton;
    QCheckBox *checkBox;
    QTableWidget *listTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(866, 617);
        MainWindow->setMinimumSize(QSize(844, 570));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName("nameLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(14);
        nameLabel->setFont(font);
        nameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(nameLabel, 1, 1, 1, 1);

        nameLineEdit = new QLineEdit(centralwidget);
        nameLineEdit->setObjectName("nameLineEdit");

        gridLayout->addWidget(nameLineEdit, 1, 2, 1, 1);

        priceLabel = new QLabel(centralwidget);
        priceLabel->setObjectName("priceLabel");
        priceLabel->setFont(font);
        priceLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(priceLabel, 2, 1, 1, 1);

        priceBox = new QSpinBox(centralwidget);
        priceBox->setObjectName("priceBox");
        priceBox->setMaximum(9999999);

        gridLayout->addWidget(priceBox, 2, 2, 1, 1);

        volumeLabel = new QLabel(centralwidget);
        volumeLabel->setObjectName("volumeLabel");
        volumeLabel->setFont(font);
        volumeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(volumeLabel, 3, 1, 1, 1);

        volumeBox = new QSpinBox(centralwidget);
        volumeBox->setObjectName("volumeBox");
        volumeBox->setMinimum(0);
        volumeBox->setMaximum(9999999);

        gridLayout->addWidget(volumeBox, 3, 2, 1, 1);

        popButton = new QPushButton(centralwidget);
        popButton->setObjectName("popButton");

        gridLayout->addWidget(popButton, 4, 1, 1, 1);

        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");

        gridLayout->addWidget(addButton, 4, 2, 1, 1);

        writeButton = new QPushButton(centralwidget);
        writeButton->setObjectName("writeButton");

        gridLayout->addWidget(writeButton, 5, 1, 1, 1);

        readButton = new QPushButton(centralwidget);
        readButton->setObjectName("readButton");

        gridLayout->addWidget(readButton, 5, 2, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setLayoutDirection(Qt::RightToLeft);
        checkBox->setChecked(false);
        checkBox->setTristate(false);

        gridLayout->addWidget(checkBox, 0, 2, 1, 1);

        listTable = new QTableWidget(centralwidget);
        listTable->setObjectName("listTable");

        gridLayout->addWidget(listTable, 0, 0, 6, 1);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(2, 2);

        gridLayout_2->addLayout(gridLayout, 0, 0, 2, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 866, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "name", nullptr));
        nameLineEdit->setInputMask(QString());
        priceLabel->setText(QCoreApplication::translate("MainWindow", "price", nullptr));
        volumeLabel->setText(QCoreApplication::translate("MainWindow", "volume", nullptr));
        popButton->setText(QCoreApplication::translate("MainWindow", "pop node", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "add new node", nullptr));
        writeButton->setText(QCoreApplication::translate("MainWindow", "write file", nullptr));
        readButton->setText(QCoreApplication::translate("MainWindow", "read file", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Stack of coins", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
