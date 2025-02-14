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

    Transaction getTransaction() const;

private:
    Ui::TransactionDialog *ui;
    Transaction::Type m_type;
};

#endif // TRANSACTIONDIALOG_H 