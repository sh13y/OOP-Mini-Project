#include "database.h"
#include <QCryptographicHash>
#include <QDebug>

Database::Database(QObject *parent)
    : QObject(parent)
    , settings(new QSettings("PersonalOrganizerDB", "PersonalOrganizer", this))
{
    loadUsers();
}

bool Database::addUser(const QString &username, const QString &password)
{
    if (users.contains(username)) {
        qDebug() << "User already exists:" << username;
        return false;
    }

    // Hash the password
    QByteArray hashedPassword = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
    );

    // Store the hashed password
    users[username] = hashedPassword;
    
    // Save to settings
    saveUsers();
    
    qDebug() << "User added:" << username;
    return true;
}

bool Database::validateUser(const QString &username, const QString &password)
{
    if (!users.contains(username)) {
        qDebug() << "User not found:" << username;
        return false;
    }

    // Hash the input password
    QByteArray hashedInput = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
    );

    // Compare with stored hash
    bool isValid = (users[username] == hashedInput);
    qDebug() << "User validation for" << username << ":" << (isValid ? "success" : "failed");
    return isValid;
}

void Database::saveUsers()
{
    settings->beginGroup("Users");
    settings->remove(""); // Clear existing users
    
    // Save each user
    for (auto it = users.constBegin(); it != users.constEnd(); ++it) {
        settings->setValue(it.key(), it.value().toHex());
    }
    
    settings->endGroup();
    settings->sync();
    
    qDebug() << "Users saved. Total users:" << users.size();
    printUsers(); // Debug output
}

void Database::loadUsers()
{
    settings->beginGroup("Users");
    
    // Get all user keys
    QStringList usernames = settings->childKeys();
    
    // Load each user
    for (const QString &username : usernames) {
        QByteArray hashedPassword = QByteArray::fromHex(settings->value(username).toByteArray());
        users[username] = hashedPassword;
    }
    
    settings->endGroup();
    
    qDebug() << "Users loaded. Total users:" << users.size();
    printUsers(); // Debug output
}

void Database::printUsers()
{
    qDebug() << "Current users in database:";
    for (auto it = users.constBegin(); it != users.constEnd(); ++it) {
        qDebug() << "Username:" << it.key() 
                 << "Password Hash:" << it.value().toHex();
    }
} 