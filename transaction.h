#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

class Transaction {
public:
    enum Type {
        Income,
        Expense
    };

    Transaction(Type type, const QString &description, const QString &category, 
               double amount, const QDate &date);

    Type type() const { return m_type; }
    QString description() const { return m_description; }
    QString category() const { return m_category; }
    double amount() const { return m_amount; }
    QDate date() const { return m_date; }

private:
    Type m_type;
    QString m_description;
    QString m_category;
    double m_amount;
    QDate m_date;
};

#endif // TRANSACTION_H 