#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMap>
#include "user.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool addUser(const QString &username, const QString &password);
    bool validateUser(const QString &username, const QString &password);

private:
    QMap<QString, User> users;
};

#endif // DATABASE_H 