#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T09:57:18
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bullet.cpp \
    airplain.cpp \
    enemy.cpp \
    host.cpp \
    enemybullet.cpp \
    hostbullet.cpp \
    upgradeitem.cpp

HEADERS += \
        mainwindow.h \
    bullet.h \
    airplain.h \
    enemy.h \
    host.h \
    enemybullet.h \
    hostbullet.h \
    upgradeitem.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
