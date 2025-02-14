#include "user.h"

User::User() {}

User::User(const QString &username, const QString &password)
    : username(username), password(password)
{
}

QString User::getUsername() const
{
    return username;
}

bool User::checkPassword(const QString &password) const
{
    return this->password == password;
} 