#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include <QDate>

TransactionDialog::TransactionDialog(Transaction::Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionDialog)
    , m_type(type)
{
    ui->setupUi(this);
    
    if (type == Transaction::Income) {
        // Set up income sources
        ui->categoryComboBox->addItems({
            "Job",
            "Allowance from Parents",
            "Scholarships",
            "Student Aid"
        });
    } else {
        // Set up expense categories
        ui->categoryComboBox->addItems({
            "Food",
            "Entertainment",
            "Travel",
            "Clothing",
            "Education Equipment",
            "University Fees",
            "Other"
        });
    }
    
    // Set up date edit
    ui->dateEdit->setDate(QDate::currentDate());
    
    // Set window title based on transaction type
    setWindowTitle(type == Transaction::Income ? "Add Income" : "Add Expense");
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}

Transaction TransactionDialog::getTransaction() const
{
    return Transaction(
        m_type,
        ui->descriptionEdit->text(),
        ui->categoryComboBox->currentText(),
        ui->amountSpinBox->value(),
        ui->dateEdit->date()
    );
} 