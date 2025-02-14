#include "loginwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set application-wide icon
    QApplication::setWindowIcon(QIcon(":/resources/app_icon.ico"));
    
    LoginWindow w;
    w.show();
    return a.exec();
} 