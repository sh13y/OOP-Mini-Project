#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Register New User");
    
    // Apply modern style
    setStyleSheet(R"(
        QDialog {
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
        QPushButton#buttonBox > QPushButton[text="Cancel"] {
            background-color: #BBB68C;  /* sage */
        }
        QPushButton#buttonBox > QPushButton[text="Cancel"]:hover {
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
    )");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

QString RegisterDialog::getUsername() const
{
    return ui->usernameEdit->text();
}

QString RegisterDialog::getPassword() const
{
    return ui->passwordEdit->text();
}

void RegisterDialog::on_buttonBox_accepted()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "All fields are required");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Registration Error", "Passwords do not match");
        return;
    }

    accept();
}

void RegisterDialog::on_buttonBox_rejected()
{
    reject();
} 