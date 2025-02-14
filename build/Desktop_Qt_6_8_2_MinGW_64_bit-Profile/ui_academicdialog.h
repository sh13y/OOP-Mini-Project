/********************************************************************************
** Form generated from reading UI file 'academicdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACADEMICDIALOG_H
#define UI_ACADEMICDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AcademicDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *titleEdit;
    QLabel *label_2;
    QTextEdit *descriptionEdit;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *durationLabel;
    QSpinBox *durationSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AcademicDialog)
    {
        if (AcademicDialog->objectName().isEmpty())
            AcademicDialog->setObjectName("AcademicDialog");
        AcademicDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(AcademicDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(AcademicDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        titleEdit = new QLineEdit(AcademicDialog);
        titleEdit->setObjectName("titleEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, titleEdit);

        label_2 = new QLabel(AcademicDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        descriptionEdit = new QTextEdit(AcademicDialog);
        descriptionEdit->setObjectName("descriptionEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, descriptionEdit);

        label_3 = new QLabel(AcademicDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        dateTimeEdit = new QDateTimeEdit(AcademicDialog);
        dateTimeEdit->setObjectName("dateTimeEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, dateTimeEdit);

        durationLabel = new QLabel(AcademicDialog);
        durationLabel->setObjectName("durationLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, durationLabel);

        durationSpinBox = new QSpinBox(AcademicDialog);
        durationSpinBox->setObjectName("durationSpinBox");
        durationSpinBox->setMaximum(480);
        durationSpinBox->setSingleStep(15);

        formLayout->setWidget(3, QFormLayout::FieldRole, durationSpinBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(AcademicDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AcademicDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AcademicDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AcademicDialog);
    } // setupUi

    void retranslateUi(QDialog *AcademicDialog)
    {
        label->setText(QCoreApplication::translate("AcademicDialog", "Title:", nullptr));
        label_2->setText(QCoreApplication::translate("AcademicDialog", "Description:", nullptr));
        label_3->setText(QCoreApplication::translate("AcademicDialog", "Date/Time:", nullptr));
        durationLabel->setText(QCoreApplication::translate("AcademicDialog", "Duration (minutes):", nullptr));
        (void)AcademicDialog;
    } // retranslateUi

};

namespace Ui {
    class AcademicDialog: public Ui_AcademicDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACADEMICDIALOG_H
