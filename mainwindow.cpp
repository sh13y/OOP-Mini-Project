#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "transactiondialog.h"
#include <QMessageBox>
#include <QtCharts>
#include <QInputDialog>
#include "academicdialog.h"
#include <QTimer>
#include <QSettings>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Set window title and icon
    setWindowTitle("Personal Organizer");
    setWindowIcon(QIcon(":/icons/organizer.png"));
    
    // Remove the menubar
    ui->menubar->hide();
    
    // Apply modern style
    setStyleSheet(R"(
        QMainWindow {
            background-color: #F0EEDC;  /* eggshell */
        }
        QPushButton {
            background-color: #9F6571;  /* rose-taupe */
            color: #F0EEDC;  /* eggshell */
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            min-width: 100px;
        }
        QPushButton:hover {
            background-color: #F27D97;  /* rose-pompadour */
        }
        QTabWidget::pane {
            border: 1px solid #BBB68C;  /* sage */
            background-color: white;
            border-radius: 4px;
        }
        QTabBar::tab {
            background-color: #F0EEDC;  /* eggshell */
            color: #000000;  /* black */
            padding: 8px 16px;
            border: none;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }
        QTabBar::tab:selected {
            background-color: white;
        }
        QComboBox, QDateEdit {
            background-color: white;
            border: 1px solid #BBB68C;
            border-radius: 4px;
            padding: 4px;
        }
        QTableWidget {
            background-color: white;
            border: 1px solid #BBB68C;  /* sage */
            border-radius: 4px;
            gridline-color: #F0EEDC;  /* eggshell */
            selection-background-color: #F0EEDC;  /* eggshell */
        }
        QTableWidget::item {
            padding: 4px;
            color: #000000;  /* black */
        }
        QTableWidget::item:selected {
            background-color: #F0EEDC;  /* eggshell */
            color: #000000;  /* black */
        }
        QHeaderView::section {
            background-color: #BBB68C;  /* sage */
            color: #000000;  /* black */
            padding: 8px;
            border: none;
        }
    )");
    
    // Initialize tables and charts
    setupTransactionsTable();
    setupAcademicTable();
    setupChartFilters();
    
    // Initialize chart view
    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_2->addWidget(chartView);
    
    // Set default chart type and month
    chartTypeCombo->setCurrentIndex(0); // Expense
    chartMonthEdit->setDate(QDate::currentDate());
    
    // Set up deadline checker timer
    deadlineTimer = new QTimer(this);
    connect(deadlineTimer, &QTimer::timeout, this, &MainWindow::checkDeadlines);
    deadlineTimer->start(60000); // Check every minute
    
    // Load data and dummy data
    loadData();
    loadDummyData();
    updateChart();
    
    // Connect save signals for existing buttons
    connect(ui->addIncomeButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->addExpenseButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->setBudgetButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->addLectureButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->addDeadlineButton, &QPushButton::clicked, this, &MainWindow::saveData);
    
    // Save data when window is closed
    connect(this, &MainWindow::destroyed, this, &MainWindow::saveData);
}

MainWindow::~MainWindow()
{
    saveData();
    delete ui;
}

void MainWindow::setupTransactionsTable()
{
    ui->transactionsTable->setColumnCount(6);
    ui->transactionsTable->setHorizontalHeaderLabels({
        "Type", "Date", "Category", "Description", "Amount", ""});
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->transactionsTable->horizontalHeader()->resizeSection(5, 30);
    
    // Make cells editable except the remove button column
    ui->transactionsTable->setEditTriggers(QAbstractItemView::DoubleClicked | 
                                         QAbstractItemView::EditKeyPressed);
}

void MainWindow::on_addIncomeButton_clicked()
{
    TransactionDialog dialog(Transaction::Income, this);
    if (dialog.exec() == QDialog::Accepted) {
        addTransaction(dialog.getTransaction());
        updateChart();
    }
}

void MainWindow::on_addExpenseButton_clicked()
{
    TransactionDialog dialog(Transaction::Expense, this);
    if (dialog.exec() == QDialog::Accepted) {
        addTransaction(dialog.getTransaction());
        updateChart();
    }
}

void MainWindow::addTransaction(const Transaction &transaction)
{
    transactions.append(transaction);
    updateTransactionsTable();
    updateChart();
}

void MainWindow::setupChartFilters()
{
    // Create filter layout
    QHBoxLayout *filterLayout = new QHBoxLayout();
    filterLayout->setSpacing(8);
    
    // Create type combo box
    chartTypeCombo = new QComboBox(this);
    chartTypeCombo->addItem("Expenses");
    chartTypeCombo->addItem("Income");
    connect(chartTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onChartTypeChanged);
    
    // Create month selector with only month and year
    chartMonthEdit = new QDateEdit(this);
    chartMonthEdit->setDisplayFormat("MMMM yyyy");
    chartMonthEdit->setCalendarPopup(false); // Disable calendar popup
    chartMonthEdit->setDate(QDate::currentDate());
    // Set minimum and maximum dates
    chartMonthEdit->setMinimumDate(QDate(2000, 1, 1));
    chartMonthEdit->setMaximumDate(QDate(2100, 12, 31));
    // Set up month/year navigation
    QSpinBox *monthSpin = chartMonthEdit->findChild<QSpinBox*>("qt_spinbox_lineedit");
    if (monthSpin) {
        monthSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    }
    connect(chartMonthEdit, &QDateEdit::dateChanged,
            this, &MainWindow::onChartMonthChanged);
    
    // Add widgets to layout
    filterLayout->addWidget(new QLabel("Show:"));
    filterLayout->addWidget(chartTypeCombo);
    filterLayout->addWidget(new QLabel("for:"));
    filterLayout->addWidget(chartMonthEdit);
    filterLayout->addStretch();
    
    // Add filter layout to main layout
    ui->verticalLayout_2->insertLayout(1, filterLayout);
}

void MainWindow::onChartTypeChanged(int)
{
    updateChart();
}

void MainWindow::onChartMonthChanged(const QDate&)
{
    updateChart();
    updateTransactionsTable();
}

void MainWindow::updateChart()
{
    QMap<QString, double> categoryTotals;
    QDate selectedMonth = chartMonthEdit->date();
    bool showExpenses = (chartTypeCombo->currentIndex() == 0);
    
    // Initialize all categories with zero
    QStringList allCategories;
    if (showExpenses) {
        allCategories = {"Food", "Entertainment", "Travel", "Clothing", "Education", "Other"};
    } else {
        allCategories = {"Salary", "Scholarship", "Allowance", "Student Aid", "Other"};
    }
    
    for (const QString &category : allCategories) {
        categoryTotals[category] = 0.0;
    }
    
    // Calculate totals by category for selected month
    for (const Transaction &t : transactions) {
        if ((showExpenses && t.type() == Transaction::Expense) ||
            (!showExpenses && t.type() == Transaction::Income)) {
            if (t.date().month() == selectedMonth.month() &&
                t.date().year() == selectedMonth.year()) {
            categoryTotals[t.category()] += t.amount();
            }
        }
    }
    
    // Create bar chart with styling
    QBarSet *set = new QBarSet(showExpenses ? "Expenses" : "Income");
    set->setColor(QColor("#9F6571"));  // rose-taupe
    QStringList categories;
    
    for (auto it = categoryTotals.constBegin(); it != categoryTotals.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    
    QBarSeries *series = new QBarSeries();
    series->append(set);
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString("%1 by Category - %2 %3")
                       .arg(showExpenses ? "Expenses" : "Income")
                       .arg(selectedMonth.toString("MMMM"))
                       .arg(selectedMonth.year()));
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Amount (Rs.)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    // Apply theme
    chart->setTheme(QChart::ChartThemeLight);
    
    chartView->setChart(chart);
}

void MainWindow::on_setBudgetButton_clicked()
{
    QString category = QInputDialog::getItem(this, "Set Budget", 
        "Select Category:", {"Food", "Entertainment", "Travel", "Clothing", "Education", "Other"});
    
    if (!category.isEmpty()) {
        bool ok;
        double amount = QInputDialog::getDouble(this, "Set Budget", 
            "Enter budget amount:", budgets.value(category, 0.0), 
            0.0, 1000000.0, 2, &ok);
        
        if (ok) {
            budgets[category] = amount;
            QMessageBox::information(this, "Budget Set", 
                QString("Budget for %1 set to %2").arg(category).arg(amount));
        }
    }
}

void MainWindow::saveData()
{
    QSettings settings("PersonalOrganizerDB", "PersonalOrganizer");
    
    // Save Academic Items
    settings.beginGroup("AcademicItems");
    settings.remove(""); // Clear existing items
    settings.setValue("count", academicItems.size());
    for (int i = 0; i < academicItems.size(); ++i) {
        const AcademicItem &item = academicItems[i];
        settings.beginGroup(QString::number(i));
        settings.setValue("type", item.type());
        settings.setValue("title", item.title());
        settings.setValue("description", item.description());
        settings.setValue("dateTime", item.dateTime());
        settings.setValue("duration", item.durationMinutes());
        settings.endGroup();
    }
    settings.endGroup();
    
    // Save Transactions
    settings.beginGroup("Transactions");
    settings.remove(""); // Clear existing items
    settings.setValue("count", transactions.size());
    for (int i = 0; i < transactions.size(); ++i) {
        const Transaction &t = transactions[i];
        settings.beginGroup(QString::number(i));
        settings.setValue("type", t.type());
        settings.setValue("description", t.description());
        settings.setValue("category", t.category());
        settings.setValue("amount", t.amount());
        settings.setValue("date", t.date());
        settings.endGroup();
    }
    settings.endGroup();
    
    // Save Budgets
    settings.beginGroup("Budgets");
    settings.remove(""); // Clear existing items
    for (auto it = budgets.constBegin(); it != budgets.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }
    settings.endGroup();
    
    // Force save
    settings.sync();
    
    // Debug output
    qDebug() << "Data saved to:" << settings.fileName();
    qDebug() << "Academic items saved:" << academicItems.size();
    qDebug() << "Transactions saved:" << transactions.size();
    qDebug() << "Budgets saved:" << budgets.size();
}

void MainWindow::loadData()
{
    QSettings settings("PersonalOrganizerDB", "PersonalOrganizer");
    
    // Debug output
    qDebug() << "Loading data from:" << settings.fileName();
    
    // Load Academic Items
    settings.beginGroup("AcademicItems");
    int aCount = settings.value("count", 0).toInt();
    qDebug() << "Found academic items:" << aCount;
    for (int i = 0; i < aCount; ++i) {
        settings.beginGroup(QString::number(i));
        AcademicItem item(
            static_cast<AcademicItem::Type>(settings.value("type").toInt()),
            settings.value("title").toString(),
            settings.value("description").toString(),
            settings.value("dateTime").toDateTime(),
            settings.value("duration").toInt()
        );
        settings.endGroup();
        addAcademicItem(item);
    }
    settings.endGroup();
    
    // Load Transactions
    settings.beginGroup("Transactions");
    int tCount = settings.value("count", 0).toInt();
    qDebug() << "Found transactions:" << tCount;
    for (int i = 0; i < tCount; ++i) {
        settings.beginGroup(QString::number(i));
        Transaction t(
            static_cast<Transaction::Type>(settings.value("type").toInt()),
            settings.value("description").toString(),
            settings.value("category").toString(),
            settings.value("amount").toDouble(),
            settings.value("date").toDate()
        );
        settings.endGroup();
        addTransaction(t);
    }
    settings.endGroup();
    
    // Load Budgets
    settings.beginGroup("Budgets");
    QStringList categories = settings.childKeys();
    qDebug() << "Found budget categories:" << categories;
    for (const QString &category : categories) {
        budgets[category] = settings.value(category).toDouble();
    }
    settings.endGroup();
}

void MainWindow::on_generateReportButton_clicked()
{
    QMap<QString, double> incomeByCategory;
    QMap<QString, double> expenseByCategory;
    QDate selectedMonth = chartMonthEdit->date();
    
    // Calculate totals by category for selected month
    for (const Transaction &t : transactions) {
        if (t.date().month() == selectedMonth.month() && 
            t.date().year() == selectedMonth.year()) {
            if (t.type() == Transaction::Income) {
                incomeByCategory[t.category()] += t.amount();
            } else {
                expenseByCategory[t.category()] += t.amount();
            }
        }
    }
    
    // Create detailed report
    QString report = QString("Financial Report for %1 %2\n\n")
                        .arg(selectedMonth.toString("MMMM"))
                        .arg(selectedMonth.year());
    
    // Add Income Details
    double totalIncome = 0;
    report += "INCOME:\n";
    report += "----------------------------------------\n";
    for (auto it = incomeByCategory.constBegin(); it != incomeByCategory.constEnd(); ++it) {
        report += QString("%1: Rs. %2\n")
                     .arg(it.key(), -20)
                     .arg(QString::number(it.value(), 'f', 2));
        totalIncome += it.value();
    }
    report += QString("Total Income: Rs. %1\n\n").arg(QString::number(totalIncome, 'f', 2));
    
    // Add Expense Details
    double totalExpense = 0;
    report += "EXPENSES:\n";
    report += "----------------------------------------\n";
    for (auto it = expenseByCategory.constBegin(); it != expenseByCategory.constEnd(); ++it) {
        double budgetAmount = budgets.value(it.key(), 0.0);
        QString status;
        if (budgetAmount > 0) {
            if (it.value() > budgetAmount) {
                status = " (OVER BUDGET!)";
            } else {
                status = QString(" (Budget: Rs. %.2f)").arg(budgetAmount);
            }
        }
        report += QString("%1: Rs. %2%3\n")
                     .arg(it.key(), -20)
                     .arg(QString::number(it.value(), 'f', 2))
                     .arg(status);
        totalExpense += it.value();
    }
    report += QString("Total Expenses: Rs. %1\n\n").arg(QString::number(totalExpense, 'f', 2));
    
    // Add Summary
    report += "SUMMARY:\n";
    report += "----------------------------------------\n";
    report += QString("Total Income:  Rs. %1\n")
                 .arg(QString::number(totalIncome, 'f', 2));
    report += QString("Total Expense: Rs. %1\n")
                 .arg(QString::number(totalExpense, 'f', 2));
    report += QString("Net Savings:   Rs. %1\n")
                 .arg(QString::number(totalIncome - totalExpense, 'f', 2));
    
    // Create a custom dialog for the report
    QDialog *reportDialog = new QDialog(this);
    reportDialog->setWindowTitle("Monthly Financial Report");
    reportDialog->setMinimumWidth(500);
    
    QVBoxLayout *layout = new QVBoxLayout(reportDialog);
    
    // Add report text in a QTextEdit
    QTextEdit *textEdit = new QTextEdit(reportDialog);
    textEdit->setReadOnly(true);
    textEdit->setFont(QFont("Courier", 10));
    textEdit->setText(report);
    layout->addWidget(textEdit);
    
    // Add OK button
    QPushButton *okButton = new QPushButton("OK", reportDialog);
    okButton->setStyleSheet(R"(
        QPushButton {
            background-color: #9F6571;  /* rose-taupe */
            color: #F0EEDC;  /* eggshell */
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            min-width: 100px;
        }
        QPushButton:hover {
            background-color: #F27D97;  /* rose-pompadour */
        }
    )");
    layout->addWidget(okButton);
    
    // Connect OK button to close dialog
    connect(okButton, &QPushButton::clicked, reportDialog, &QDialog::accept);
    
    // Show the dialog
    reportDialog->exec();
    
    // Clean up
    delete reportDialog;
}

void MainWindow::on_addLectureButton_clicked()
{
    AcademicDialog dialog(AcademicItem::Lecture, this);
    if (dialog.exec() == QDialog::Accepted) {
        addAcademicItem(dialog.getAcademicItem());
    }
}

void MainWindow::on_addDeadlineButton_clicked()
{
    AcademicDialog dialog(AcademicItem::Deadline, this);
    if (dialog.exec() == QDialog::Accepted) {
        addAcademicItem(dialog.getAcademicItem());
    }
}

void MainWindow::setupAcademicTable()
{
    ui->scheduleTable->setColumnCount(6);
    ui->scheduleTable->setHorizontalHeaderLabels({
        "Type", "Title", "Description", "Date/Time", "Duration", ""});
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->scheduleTable->horizontalHeader()->resizeSection(5, 30);
    
    // Make cells editable except the remove button column
    ui->scheduleTable->setEditTriggers(QAbstractItemView::DoubleClicked | 
                                     QAbstractItemView::EditKeyPressed);
}

void MainWindow::addAcademicItem(const AcademicItem &item)
{
    academicItems.append(item);
    
    int row = ui->scheduleTable->rowCount();
    ui->scheduleTable->insertRow(row);
    
    ui->scheduleTable->setItem(row, 0, 
        new QTableWidgetItem(item.type() == AcademicItem::Lecture ? "Lecture" : "Deadline"));
    ui->scheduleTable->setItem(row, 1, 
        new QTableWidgetItem(item.title()));
    ui->scheduleTable->setItem(row, 2, 
        new QTableWidgetItem(item.description()));
    ui->scheduleTable->setItem(row, 3, 
        new QTableWidgetItem(item.dateTime().toString("dd/MM/yyyy hh:mm AP")));
    ui->scheduleTable->setItem(row, 4, 
        new QTableWidgetItem(item.type() == AcademicItem::Lecture ? 
            QString("%1 minutes").arg(item.durationMinutes()) : "-"));

    // Add remove button
    QPushButton* removeButton = new QPushButton("×", ui->scheduleTable);
    removeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #F27D97;  /* rose-pompadour */
            color: white;
            border: none;
            border-radius: 3px;
            padding: 0px;
            font-size: 16px;
            font-family: Arial;
            min-width: 20px;
            max-width: 20px;
            min-height: 20px;
            max-height: 20px;
        }
        QPushButton:hover {
            background-color: #9F6571;  /* rose-taupe */
        }
    )");
    ui->scheduleTable->setCellWidget(row, 5, removeButton);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveAcademicItemClicked);
}

void MainWindow::checkDeadlines()
{
    for (const AcademicItem &item : academicItems) {
        if (item.isDeadlineApproaching()) {
            QMessageBox::warning(this, "Deadline Approaching",
                QString("Deadline '%1' is approaching!\n\n"
                       "Due: %2\n"
                       "Description: %3")
                    .arg(item.title())
                    .arg(item.dateTime().toString("dd/MM/yyyy hh:mm AP"))
                    .arg(item.description()));
        }
    }
}

void MainWindow::onRemoveTransactionClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    // Find the row of the button
    for (int row = 0; row < ui->transactionsTable->rowCount(); ++row) {
        if (ui->transactionsTable->cellWidget(row, 5) == button) {
            // Get the transaction details from the table
            QString dateStr = ui->transactionsTable->item(row, 1)->text();
            QString category = ui->transactionsTable->item(row, 2)->text();
            QString description = ui->transactionsTable->item(row, 3)->text();
            double amount = ui->transactionsTable->item(row, 4)->text().toDouble();
            Transaction::Type type = ui->transactionsTable->item(row, 0)->text() == "Income" 
                ? Transaction::Income : Transaction::Expense;
            
            // Find and remove the transaction from the vector
            for (int i = 0; i < transactions.size(); ++i) {
                if (transactions[i].date().toString("dd/MM/yyyy") == dateStr &&
                    transactions[i].category() == category &&
                    transactions[i].description() == description &&
                    transactions[i].amount() == amount &&
                    transactions[i].type() == type) {
                    transactions.remove(i);
                    break;
                }
            }
            
            // Update the table and chart
            updateTransactionsTable();
            updateChart();
            break;
        }
    }
}

void MainWindow::onRemoveAcademicItemClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    // Find the row of the button
    for (int row = 0; row < ui->scheduleTable->rowCount(); ++row) {
        if (ui->scheduleTable->cellWidget(row, 5) == button) {
            // Remove from both table and vector
            academicItems.remove(row);
            ui->scheduleTable->removeRow(row);
            break;
        }
    }
}

void MainWindow::loadDummyData()
{
    // Add sample income transactions
    addTransaction(Transaction(
        Transaction::Income,
        "Monthly Salary",
        "Job",
        45000,
        QDate::currentDate().addDays(-5)
    ));

    addTransaction(Transaction(
        Transaction::Income,
        "Scholarship Payment",
        "Scholarships",
        15000,
        QDate::currentDate().addDays(-15)
    ));

    addTransaction(Transaction(
        Transaction::Income,
        "Monthly Allowance",
        "Allowance from Parents",
        10000,
        QDate::currentDate().addDays(-2)
    ));

    // Add sample expenses
    addTransaction(Transaction(
        Transaction::Expense,
        "Textbooks",
        "Education Equipment",
        2500,
        QDate::currentDate().addDays(-10)
    ));

    addTransaction(Transaction(
        Transaction::Expense,
        "Monthly Bus Pass",
        "Travel",
        1200,
        QDate::currentDate().addDays(-8)
    ));

    addTransaction(Transaction(
        Transaction::Expense,
        "Lunch at Cafeteria",
        "Food",
        150,
        QDate::currentDate()
    ));

    // Add sample academic schedule items
    addAcademicItem(AcademicItem(
        AcademicItem::Lecture,
        "Object Oriented Programming",
        "Room 301, Engineering Building",
        QDateTime::currentDateTime().addDays(1).addSecs(36000), // 10:00 AM tomorrow
        120 // 2 hours
    ));

    addAcademicItem(AcademicItem(
        AcademicItem::Lecture,
        "Database Management",
        "Room 205, CS Department",
        QDateTime::currentDateTime().addDays(2).addSecs(46800), // 1:00 PM day after tomorrow
        90 // 1.5 hours
    ));

    addAcademicItem(AcademicItem(
        AcademicItem::Deadline,
        "OOP Project Submission",
        "Final project submission with documentation",
        QDateTime::currentDateTime().addDays(7).addSecs(75600), // 9:00 PM next week
        0
    ));

    addAcademicItem(AcademicItem(
        AcademicItem::Deadline,
        "Database Quiz",
        "Chapters 1-5, Normalization focus",
        QDateTime::currentDateTime().addDays(3).addSecs(39600), // 11:00 AM in 3 days
        0
    ));

    updateChart();
}

QVector<Transaction> MainWindow::getTransactionsForMonth(const QDate &date)
{
    QVector<Transaction> filteredTransactions;
    for (const Transaction &t : transactions) {
        if (t.date().month() == date.month() && 
            t.date().year() == date.year()) {
            filteredTransactions.append(t);
        }
    }
    return filteredTransactions;
}

void MainWindow::updateTransactionsTable()
{
    // Clear existing rows
    ui->transactionsTable->setRowCount(0);
    
    // Get transactions for selected month
    QVector<Transaction> monthTransactions = getTransactionsForMonth(chartMonthEdit->date());
    
    // Add transactions to table
    for (const Transaction &t : monthTransactions) {
        int row = ui->transactionsTable->rowCount();
        ui->transactionsTable->insertRow(row);
        
        // Type
        ui->transactionsTable->setItem(row, 0, 
            new QTableWidgetItem(t.type() == Transaction::Income ? "Income" : "Expense"));
        
        // Date
        ui->transactionsTable->setItem(row, 1, 
            new QTableWidgetItem(t.date().toString("dd/MM/yyyy")));
        
        // Category
        ui->transactionsTable->setItem(row, 2, 
            new QTableWidgetItem(t.category()));
        
        // Description
        ui->transactionsTable->setItem(row, 3, 
            new QTableWidgetItem(t.description()));
        
        // Amount
        ui->transactionsTable->setItem(row, 4, 
            new QTableWidgetItem(QString::number(t.amount(), 'f', 2)));
        
        // Remove button
        QPushButton* removeButton = new QPushButton("×", ui->transactionsTable);
        removeButton->setStyleSheet(R"(
            QPushButton {
                background-color: #F27D97;  /* rose-pompadour */
                color: white;
                border: none;
                border-radius: 3px;
                padding: 0px;
                font-size: 16px;
                font-family: Arial;
                min-width: 20px;
                max-width: 20px;
                min-height: 20px;
                max-height: 20px;
            }
            QPushButton:hover {
                background-color: #9F6571;  /* rose-taupe */
            }
        )");
        ui->transactionsTable->setCellWidget(row, 5, removeButton);
        connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveTransactionClicked);
    }
} 