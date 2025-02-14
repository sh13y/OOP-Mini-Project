#include "database.h"

Database::Database(QObject *parent)
    : QObject(parent)
{
}

bool Database::addUser(const QString &username, const QString &password)
{
    if (users.contains(username))
        return false;

    users.insert(username, User(username, password));
    return true;
}

bool Database::validateUser(const QString &username, const QString &password)
{
    if (!users.contains(username))
        return false;

    return users[username].checkPassword(password);
} 