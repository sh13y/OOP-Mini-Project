#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSettings>
#include <QCryptographicHash>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    bool addUser(const QString &username, const QString &password);
    bool validateUser(const QString &username, const QString &password);
    void saveUsers();
    void loadUsers();
    void printUsers(); // Debug function to print all users

private:
    QSettings* settings;
    QMap<QString, QByteArray> users; // username -> hashed password
};

#endif // DATABASE_H 