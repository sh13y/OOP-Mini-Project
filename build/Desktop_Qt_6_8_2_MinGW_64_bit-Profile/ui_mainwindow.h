/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *financeTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *addIncomeButton;
    QPushButton *addExpenseButton;
    QPushButton *setBudgetButton;
    QPushButton *generateReportButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *transactionsTable;
    QVBoxLayout *chartLayout;
    QWidget *academicTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addLectureButton;
    QPushButton *addDeadlineButton;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *scheduleTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        financeTab = new QWidget();
        financeTab->setObjectName("financeTab");
        verticalLayout_2 = new QVBoxLayout(financeTab);
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName("horizontalLayout");
        addIncomeButton = new QPushButton(financeTab);
        addIncomeButton->setObjectName("addIncomeButton");

        horizontalLayout->addWidget(addIncomeButton);

        addExpenseButton = new QPushButton(financeTab);
        addExpenseButton->setObjectName("addExpenseButton");

        horizontalLayout->addWidget(addExpenseButton);

        setBudgetButton = new QPushButton(financeTab);
        setBudgetButton->setObjectName("setBudgetButton");

        horizontalLayout->addWidget(setBudgetButton);

        generateReportButton = new QPushButton(financeTab);
        generateReportButton->setObjectName("generateReportButton");

        horizontalLayout->addWidget(generateReportButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        transactionsTable = new QTableWidget(financeTab);
        transactionsTable->setObjectName("transactionsTable");

        verticalLayout_2->addWidget(transactionsTable);

        chartLayout = new QVBoxLayout();
        chartLayout->setObjectName("chartLayout");

        verticalLayout_2->addLayout(chartLayout);

        tabWidget->addTab(financeTab, QString());
        academicTab = new QWidget();
        academicTab->setObjectName("academicTab");
        verticalLayout_3 = new QVBoxLayout(academicTab);
        verticalLayout_3->setSpacing(12);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addLectureButton = new QPushButton(academicTab);
        addLectureButton->setObjectName("addLectureButton");

        horizontalLayout_2->addWidget(addLectureButton);

        addDeadlineButton = new QPushButton(academicTab);
        addDeadlineButton->setObjectName("addDeadlineButton");

        horizontalLayout_2->addWidget(addDeadlineButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        scheduleTable = new QTableWidget(academicTab);
        scheduleTable->setObjectName("scheduleTable");

        verticalLayout_3->addWidget(scheduleTable);

        tabWidget->addTab(academicTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Personal Finance Manager", nullptr));
        addIncomeButton->setText(QCoreApplication::translate("MainWindow", "Add Income", nullptr));
        addExpenseButton->setText(QCoreApplication::translate("MainWindow", "Add Expense", nullptr));
        setBudgetButton->setText(QCoreApplication::translate("MainWindow", "Set Budget", nullptr));
        generateReportButton->setText(QCoreApplication::translate("MainWindow", "Generate Report", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(financeTab), QCoreApplication::translate("MainWindow", "Finance", nullptr));
        addLectureButton->setText(QCoreApplication::translate("MainWindow", "Add Lecture", nullptr));
        addDeadlineButton->setText(QCoreApplication::translate("MainWindow", "Add Deadline", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(academicTab), QCoreApplication::translate("MainWindow", "Academic Schedule", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
