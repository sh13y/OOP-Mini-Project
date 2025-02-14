#include "transaction.h"

Transaction::Transaction(Type type, const QString &description, const QString &category, 
                       double amount, const QDate &date)
    : m_type(type)
    , m_description(description)
    , m_category(category)
    , m_amount(amount)
    , m_date(date)
{
} 