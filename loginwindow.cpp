#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "mainwindow.h"
#include "registerdialog.h"
#include "database.h"
#include <QMessageBox>
#include <QIcon>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , db(new Database(this))
    , mainWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Login - Personal Organizer");
    
    // Remove the menubar
    ui->menubar->hide();
    
    // Apply modern style
    setStyleSheet(R"(
        QMainWindow {
            background-color: #F0EEDC;  /* eggshell */
        }
        QWidget#centralwidget {
            background-color: #F0EEDC;  /* eggshell */
        }
        QPushButton {
            background-color: #9F6571;  /* rose-taupe */
            color: #F0EEDC;  /* eggshell */
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            min-width: 100px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #F27D97;  /* rose-pompadour */
        }
        QPushButton#registerButton {
            background-color: #BBB68C;  /* sage */
        }
        QPushButton#registerButton:hover {
            background-color: #9F6571;  /* rose-taupe */
        }
        QLineEdit {
            padding: 8px;
            border: 1px solid #9F6571;  /* rose-taupe */
            border-radius: 4px;
            background-color: white;
            font-size: 14px;
            min-width: 200px;
        }
        QLineEdit:focus {
            border: 2px solid #F27D97;  /* rose-pompadour */
        }
        QLabel {
            color: #000000;  /* black */
            font-size: 14px;
            font-weight: bold;
        }
        #logoLabel {
            font-size: 32px;
            font-weight: bold;
            color: #9F6571;  /* rose-taupe */
            font-family: 'Arial';
            margin-bottom: 5px;
        }
        #subtitleLabel {
            font-size: 14px;
            font-style: italic;
            color: #BBB68C;  /* sage */
            font-family: 'Arial';
            margin-bottom: 20px;
        }
        QFormLayout {
            spacing: 15px;
        }
        QHBoxLayout {
            spacing: 10px;
        }
    )");
    
    // Create and add logo label
    QLabel *logoLabel = new QLabel("Personal Organizer", this);
    logoLabel->setObjectName("logoLabel");
    logoLabel->setAlignment(Qt::AlignCenter);
    
    // Create and add subtitle label
    QLabel *subtitleLabel = new QLabel("Your personal finance and academic companion", this);
    subtitleLabel->setObjectName("subtitleLabel");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    
    // Create a container widget for the logo and subtitle
    QWidget *headerWidget = new QWidget(this);
    QVBoxLayout *headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setSpacing(0);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->addWidget(logoLabel);
    headerLayout->addWidget(subtitleLabel);
    
    // Add the header widget to the main layout
    ui->verticalLayout->insertWidget(0, headerWidget);
    
    // Adjust spacing in the main layout
    ui->verticalLayout->setSpacing(20);
    ui->verticalLayout->setContentsMargins(40, 40, 40, 40);
    
    // Adjust form layout spacing
    ui->formLayout->setSpacing(15);
    ui->formLayout->setContentsMargins(0, 0, 0, 0);
    
    // Adjust button layout spacing
    ui->horizontalLayout->setSpacing(10);
    ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    
    // Add spacing after the header
    ui->verticalLayout->insertSpacing(1, 30);
    
    // Add spacing before the buttons
    ui->verticalLayout->insertSpacing(3, 20);

    // Connect signals
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::on_registerButton_clicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    if (mainWindow) {
        delete mainWindow;
    }
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password");
        return;
    }

    if (db->validateUser(username, password)) {
        qDebug() << "Login successful for user:" << username;
        if (!mainWindow) {
            mainWindow = new MainWindow();
        }
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegisterDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Registration Failed", "Username and password cannot be empty");
            return;
        }

        if (db->addUser(username, password)) {
            QMessageBox::information(this, "Registration Successful", "Account created successfully! You can now login.");
            qDebug() << "New user registered:" << username;
            ui->usernameInput->clear();
            ui->passwordInput->clear();
        } else {
            QMessageBox::warning(this, "Registration Failed", "Username already exists");
        }
    }
}
