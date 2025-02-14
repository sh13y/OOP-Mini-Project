#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerdialog.h"
#include <QMessageBox>
#include <QIcon>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , database(new Database(this))
{
    ui->setupUi(this);
    setWindowTitle("Personal Organizer - Login");
    setWindowIcon(QIcon(":/resources/app_icon.ico"));

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
        }
        QLineEdit:focus {
            border: 2px solid #F27D97;  /* rose-pompadour */
        }
        QLabel {
            color: #000000;  /* black */
            font-size: 14px;
            font-weight: bold;
        }
    )");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter username and password");
        return;
    }

    if (database->validateUser(username, password)) {
        mainWindow = new MainWindow(this);
        mainWindow->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegisterDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();
        
        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Registration Error", "Username and password cannot be empty");
            return;
        }
        
        if (database->addUser(username, password)) {
            QMessageBox::information(this, "Success", "Registration successful! You can now login.");
        } else {
            QMessageBox::warning(this, "Registration Error", "Username already exists");
        }
    }
} 