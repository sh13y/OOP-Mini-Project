/********************************************************************************
** Form generated from reading UI file 'transactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONDIALOG_H
#define UI_TRANSACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TransactionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *descriptionEdit;
    QLabel *label_2;
    QComboBox *categoryComboBox;
    QLabel *label_3;
    QDoubleSpinBox *amountSpinBox;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TransactionDialog)
    {
        if (TransactionDialog->objectName().isEmpty())
            TransactionDialog->setObjectName("TransactionDialog");
        TransactionDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(TransactionDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(TransactionDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        descriptionEdit = new QLineEdit(TransactionDialog);
        descriptionEdit->setObjectName("descriptionEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, descriptionEdit);

        label_2 = new QLabel(TransactionDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        categoryComboBox = new QComboBox(TransactionDialog);
        categoryComboBox->setObjectName("categoryComboBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, categoryComboBox);

        label_3 = new QLabel(TransactionDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        amountSpinBox = new QDoubleSpinBox(TransactionDialog);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setMaximum(1000000.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, amountSpinBox);

        label_4 = new QLabel(TransactionDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        dateEdit = new QDateEdit(TransactionDialog);
        dateEdit->setObjectName("dateEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, dateEdit);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(TransactionDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TransactionDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TransactionDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TransactionDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *TransactionDialog)
    {
        label->setText(QCoreApplication::translate("TransactionDialog", "Description:", nullptr));
        label_2->setText(QCoreApplication::translate("TransactionDialog", "Category:", nullptr));
        label_3->setText(QCoreApplication::translate("TransactionDialog", "Amount:", nullptr));
        label_4->setText(QCoreApplication::translate("TransactionDialog", "Date:", nullptr));
        (void)TransactionDialog;
    } // retranslateUi

};

namespace Ui {
    class TransactionDialog: public Ui_TransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONDIALOG_H
