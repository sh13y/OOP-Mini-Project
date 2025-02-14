Here's a detailed `code_review.md` file that explains the code in a beginner-friendly manner. This document will help you understand the structure and functionality of your project, making it easier to explain during your viva session.

# Code Review for Personal Finance & Academic Organizer

## Overview
This document provides a detailed review of the codebase for the Personal Finance & Academic Organizer application. It explains the purpose of each file, the main classes and functions, and how they interact with each other.

## Project Structure
The project is organized into several directories and files:

```
PersonalOrganizer/
├── source/
│   ├── main.cpp               # Entry point of the application
│   ├── loginwindow.cpp        # Handles user login
│   ├── mainwindow.cpp         # Main application window
│   ├── transaction.cpp         # Manages financial transactions
│   └── academicitem.cpp       # Represents academic commitments
├── headers/
│   ├── loginwindow.h          # Header for login window
│   ├── mainwindow.h           # Header for main window
│   ├── transaction.h           # Header for transaction management
│   └── academicitem.h         # Header for academic item management
├── forms/
│   ├── loginwindow.ui         # UI for login window
│   ├── mainwindow.ui          # UI for main window
│   └── transactiondialog.ui    # UI for transaction dialog
├── resources/
│   └── app_icon.ico           # Application icon
└── PersonalOrganizer.pro       # Qt project file
```

### 1. `main.cpp`
This is the entry point of the application. It initializes the application and displays the login window.

```cpp
#include "loginwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set application-wide icon
    QApplication::setWindowIcon(QIcon(":/resources/app_icon.ico"));
    
    LoginWindow w; // Create an instance of LoginWindow
    w.show(); // Show the login window
    return a.exec(); // Start the event loop
}
```

### 2. `loginwindow.h` and `loginwindow.cpp`
These files define the `LoginWindow` class, which handles user authentication.

- **Header File (`loginwindow.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "database.h" // Include the database handler

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked(); // Slot for login button click
    void on_registerButton_clicked(); // Slot for register button click

private:
    Ui::LoginWindow *ui; // Pointer to the UI elements
    Database *database; // Pointer to the database handler
};

#endif // LOGINWINDOW_H
```

- **Source File (`loginwindow.cpp`)**: Implements the functionality of the login window.

```cpp
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerdialog.h"
#include <QMessageBox>
#include <QIcon>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , database(new Database(this)) // Initialize the database handler
{
    ui->setupUi(this); // Set up the UI
    setWindowTitle("Personal Organizer - Login");
    setWindowIcon(QIcon(":/resources/app_icon.ico")); // Set the window icon

    // Apply modern style
    setStyleSheet(R"(
        QMainWindow {
            background-color: #F0EEDC;  /* eggshell */
        }
        // Additional styles for buttons, line edits, etc.
    )");
}

LoginWindow::~LoginWindow()
{
    delete ui; // Clean up UI resources
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text(); // Get username
    QString password = ui->passwordInput->text(); // Get password

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter username and password");
        return; // Exit if fields are empty
    }

    if (database->validateUser(username, password)) { // Validate user credentials
        MainWindow *mainWindow = new MainWindow(this); // Create main window
        mainWindow->show(); // Show main window
        this->hide(); // Hide login window
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegisterDialog dialog(this); // Create registration dialog
    if (dialog.exec() == QDialog::Accepted) { // Show dialog and check if accepted
        QString username = dialog.getUsername(); // Get username
        QString password = dialog.getPassword(); // Get password
        
        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Registration Error", "Username and password cannot be empty");
            return; // Exit if fields are empty
        }
        
        if (database->addUser(username, password)) { // Add user to database
            QMessageBox::information(this, "Success", "Registration successful! You can now login.");
        } else {
            QMessageBox::warning(this, "Registration Error", "Username already exists");
        }
    }
}
```

### 3. `mainwindow.h` and `mainwindow.cpp`
These files define the `MainWindow` class, which is the main interface of the application.

- **Header File (`mainwindow.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "transaction.h"
#include <QtCharts>
#include "academicitem.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIncomeButton_clicked(); // Slot for adding income
    void on_addExpenseButton_clicked(); // Slot for adding expense
    void on_generateReportButton_clicked(); // Slot for generating report
    void on_setBudgetButton_clicked(); // Slot for setting budget
    void on_addLectureButton_clicked(); // Slot for adding lecture
    void on_addDeadlineButton_clicked(); // Slot for adding deadline
    void checkDeadlines(); // Slot for checking deadlines
    void onRemoveTransactionClicked(); // Slot for removing transaction
    void onRemoveAcademicItemClicked(); // Slot for removing academic item

private:
    void setupTransactionsTable(); // Set up the transactions table
    void addTransaction(const Transaction &transaction); // Add a transaction
    void updateChart(); // Update the financial chart
    void saveData(); // Save data to storage
    void loadData(); // Load data from storage
    void loadDummyData(); // Load dummy data for testing

    Ui::MainWindow *ui; // Pointer to the UI elements
    QVector<Transaction> transactions; // Vector to store transactions
    QMap<QString, double> budgets; // Map to store budgets
    QChartView *chartView; // Pointer to the chart view
    QVector<AcademicItem> academicItems; // Vector to store academic items
    QTimer *deadlineTimer; // Timer for checking deadlines
};

#endif // MAINWINDOW_H
```

- **Source File (`mainwindow.cpp`)**: Implements the functionality of the main window.

```cpp
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/app_icon.ico")); // Set the window icon
    setupTransactionsTable(); // Set up the transactions table
    setupAcademicTable(); // Set up the academic table
    
    // Remove the menubar
    ui->menubar->hide();
    
    // Apply modern style
    setStyleSheet(R"(
        QMainWindow {
            background-color: #F0EEDC;  /* eggshell */
        }
        // Additional styles for buttons, tables, etc.
    )");
    
    // Create chart view with styling
    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: white; border-radius: 4px;");
    ui->chartLayout->addWidget(chartView);
    
    // Set up deadline checker timer
    deadlineTimer = new QTimer(this);
    connect(deadlineTimer, &QTimer::timeout, this, &MainWindow::checkDeadlines);
    deadlineTimer->start(60000); // Check every minute
    
    loadData(); // Load existing data
    loadDummyData(); // Load dummy data for testing
    updateChart(); // Update the chart with loaded data
}

MainWindow::~MainWindow()
{
    saveData(); // Save data before closing
    delete ui; // Clean up UI resources
}
```

### 4. `transaction.h` and `transaction.cpp`
These files define the `Transaction` class, which represents financial transactions.

- **Header File (`transaction.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

class Transaction
{
public:
    enum Type { Income, Expense }; // Enum for transaction types

    Transaction(Type type, const QString &category, const QString &description, double amount, const QDate &date);
    
    Type type() const; // Get transaction type
    QString category() const; // Get transaction category
    QString description() const; // Get transaction description
    double amount() const; // Get transaction amount
    QDate date() const; // Get transaction date

private:
    Type m_type; // Transaction type
    QString m_category; // Transaction category
    QString m_description; // Transaction description
    double m_amount; // Transaction amount
    QDate m_date; // Transaction date
};

#endif // TRANSACTION_H
```

- **Source File (`transaction.cpp`)**: Implements the functionality of the `Transaction` class.

```cpp
#include "transaction.h"

Transaction::Transaction(Type type, const QString &category, const QString &description, double amount, const QDate &date)
    : m_type(type), m_category(category), m_description(description), m_amount(amount), m_date(date) {}

Transaction::Type Transaction::type() const { return m_type; }
QString Transaction::category() const { return m_category; }
QString Transaction::description() const { return m_description; }
double Transaction::amount() const { return m_amount; }
QDate Transaction::date() const { return m_date; }
```

### 5. `academicitem.h` and `academicitem.cpp`
These files define the `AcademicItem` class, which represents academic commitments.

- **Header File (`academicitem.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef ACADEMICITEM_H
#define ACADEMICITEM_H

#include <QString>
#include <QDateTime>

class AcademicItem
{
public:
    enum Type { Lecture, Deadline }; // Enum for academic item types

    AcademicItem(Type type, const QString &title, const QString &description, const QDateTime &dateTime, int durationMinutes);
    
    Type type() const; // Get academic item type
    QString title() const; // Get academic item title
    QString description() const; // Get academic item description
    QDateTime dateTime() const; // Get academic item date and time
    int durationMinutes() const; // Get duration in minutes
    bool isDeadlineApproaching() const; // Check if deadline is approaching

private:
    Type m_type; // Academic item type
    QString m_title; // Academic item title
    QString m_description; // Academic item description
    QDateTime m_dateTime; // Academic item date and time
    int m_durationMinutes; // Duration in minutes
};

#endif // ACADEMICITEM_H
```

- **Source File (`academicitem.cpp`)**: Implements the functionality of the `AcademicItem` class.

```cpp
#include "academicitem.h"
#include <QDateTime>

AcademicItem::AcademicItem(Type type, const QString &title, const QString &description, const QDateTime &dateTime, int durationMinutes)
    : m_type(type), m_title(title), m_description(description), m_dateTime(dateTime), m_durationMinutes(durationMinutes) {}

AcademicItem::Type AcademicItem::type() const { return m_type; }
QString AcademicItem::title() const { return m_title; }
QString AcademicItem::description() const { return m_description; }
QDateTime AcademicItem::dateTime() const { return m_dateTime; }
int AcademicItem::durationMinutes() const { return m_durationMinutes; }

bool AcademicItem::isDeadlineApproaching() const {
    // Check if the deadline is within the next 24 hours
    return m_dateTime <= QDateTime::currentDateTime().addDays(1);
}
```

### 6. `transactiondialog.h` and `transactiondialog.cpp`
These files define the `TransactionDialog` class, which is used for adding or editing transactions.

- **Header File (`transactiondialog.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include "transaction.h"

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(Transaction::Type type, QWidget *parent = nullptr);
    ~TransactionDialog();

    Transaction getTransaction() const; // Get the transaction data

private slots:
    void on_acceptButton_clicked(); // Slot for accept button click

private:
    Ui::TransactionDialog *ui; // Pointer to the UI elements
    Transaction::Type m_type; // Transaction type (Income or Expense)
};

#endif // TRANSACTIONDIALOG_H
```

- **Source File (`transactiondialog.cpp`)**: Implements the functionality of the transaction dialog.

```cpp
#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include <QMessageBox>

TransactionDialog::TransactionDialog(Transaction::Type type, QWidget *parent)
    : QDialog(parent), ui(new Ui::TransactionDialog), m_type(type)
{
    ui->setupUi(this);
    // Set dialog title based on transaction type
    setWindowTitle(type == Transaction::Income ? "Add Income" : "Add Expense");
}

TransactionDialog::~TransactionDialog()
{
    delete ui; // Clean up UI resources
}

Transaction TransactionDialog::getTransaction() const
{
    // Create and return a Transaction object based on user input
    return Transaction(
        m_type,
        ui->categoryInput->text(),
        ui->descriptionInput->text(),
        ui->amountInput->value(),
        ui->dateInput->date()
    );
}

void TransactionDialog::on_acceptButton_clicked()
{
    // Validate input and accept the dialog
    if (ui->categoryInput->text().isEmpty() || ui->descriptionInput->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return; // Exit if fields are empty
    }
    accept(); // Close the dialog and return accepted
}
```

### 7. `academicdialog.h` and `academicdialog.cpp`
These files define the `AcademicDialog` class, which is used for adding or editing academic items.

- **Header File (`academicdialog.h`)**: Contains the class definition and function declarations.

```cpp
#ifndef ACADEMICDIALOG_H
#define ACADEMICDIALOG_H

#include <QDialog>
#include "academicitem.h"

namespace Ui {
class AcademicDialog;
}

class AcademicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AcademicDialog(AcademicItem::Type type, QWidget *parent = nullptr);
    ~AcademicDialog();

    AcademicItem getAcademicItem() const; // Get the academic item data

private slots:
    void on_acceptButton_clicked(); // Slot for accept button click

private:
    Ui::AcademicDialog *ui; // Pointer to the UI elements
    AcademicItem::Type m_type; // Academic item type (Lecture or Deadline)
};

#endif // ACADEMICDIALOG_H
```

- **Source File (`academicdialog.cpp`)**: Implements the functionality of the academic dialog.

```cpp
#include "academicdialog.h"
#include "ui_academicdialog.h"
#include <QMessageBox>

AcademicDialog::AcademicDialog(AcademicItem::Type type, QWidget *parent)
    : QDialog(parent), ui(new Ui::AcademicDialog), m_type(type)
{
    ui->setupUi(this);
    // Set dialog title based on academic item type
    setWindowTitle(type == AcademicItem::Lecture ? "Add Lecture" : "Add Deadline");
}

AcademicDialog::~AcademicDialog()
{
    delete ui; // Clean up UI resources
}

AcademicItem AcademicDialog::getAcademicItem() const
{
    // Create and return an AcademicItem object based on user input
    return AcademicItem(
        m_type,
        ui->titleInput->text(),
        ui->descriptionInput->text(),
        ui->dateTimeInput->dateTime(),
        ui->durationInput->value()
    );
}

void AcademicDialog::on_acceptButton_clicked()
{
    // Validate input and accept the dialog
    if (ui->titleInput->text().isEmpty() || ui->descriptionInput->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return; // Exit if fields are empty
    }
    accept(); // Close the dialog and return accepted
}
```

### Conclusion
This code review provides a comprehensive overview of the Personal Finance & Academic Organizer application. Each component is designed to handle specific tasks, ensuring a modular and maintainable codebase. The use of Qt's features allows for a rich user interface and smooth user experience.

Feel free to reach out if you have any questions or need further clarification on any part of the code!
