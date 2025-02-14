#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QPushButton>
#include <QDialogButtonBox>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Register New User");

    // Apply modern style using the same color palette as LoginWindow
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
        QLineEdit {
            padding: 8px;
            border: 1px solid #dcdcdc;
            border-radius: 4px;
            background-color: white;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 2px solid #9F6571;  /* rose-taupe */
        }
        QLabel {
            color: #000000;  /* black */
            font-size: 14px;
            font-weight: bold;
        }
        QDialogButtonBox QPushButton {
            min-width: 80px;
        }
    )");

    // Add password validation
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &RegisterDialog::validatePasswords);
    connect(ui->confirmPasswordEdit, &QLineEdit::textChanged, this, &RegisterDialog::validatePasswords);
}

void RegisterDialog::validatePasswords()
{
    QPushButton* okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (ui->passwordEdit->text() != ui->confirmPasswordEdit->text()) {
        ui->confirmPasswordEdit->setStyleSheet(R"(
            QLineEdit {
                padding: 8px;
                border: 1px solid #dc3545;  /* red for error */
                border-radius: 4px;
                background-color: #fff8f8;  /* light red background */
            }
        )");
        okButton->setEnabled(false);
    } else {
        ui->confirmPasswordEdit->setStyleSheet(""); // Reset style
        okButton->setEnabled(true);
    }
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