/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *usernameEdit;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QLabel *label_3;
    QLineEdit *confirmPasswordEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(400, 200);
        verticalLayout = new QVBoxLayout(RegisterDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(RegisterDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        usernameEdit = new QLineEdit(RegisterDialog);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameEdit);

        label_2 = new QLabel(RegisterDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        passwordEdit = new QLineEdit(RegisterDialog);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordEdit);

        label_3 = new QLabel(RegisterDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        confirmPasswordEdit = new QLineEdit(RegisterDialog);
        confirmPasswordEdit->setObjectName("confirmPasswordEdit");
        confirmPasswordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, confirmPasswordEdit);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(RegisterDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(RegisterDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, RegisterDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, RegisterDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        label->setText(QCoreApplication::translate("RegisterDialog", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterDialog", "Password:", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterDialog", "Confirm Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
