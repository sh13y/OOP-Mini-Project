#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "database.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
    Database *database;
};

#endif // LOGINWINDOW_H 