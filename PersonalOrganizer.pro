QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = PersonalOrganizer
TEMPLATE = app

RESOURCES += app.qrc

RC_ICONS = resources/app_icon.ico

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    loginwindow.cpp \
    user.cpp \
    database.cpp \
    transaction.cpp \
    transactiondialog.cpp \
    registerdialog.cpp \
    academicitem.cpp \
    academicdialog.cpp

HEADERS += \
    mainwindow.h \
    loginwindow.h \
    user.h \
    database.h \
    transaction.h \
    transactiondialog.h \
    registerdialog.h \
    academicitem.h \
    academicdialog.h

FORMS += \
    mainwindow.ui \
    loginwindow.ui \
    transactiondialog.ui \
    registerdialog.ui \
    academicdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target 