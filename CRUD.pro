#-------------------------------------------------
# Project created by QtCreator
#-------------------------------------------------

QT += core gui widgets sql charts positioning location quickwidgets

CONFIG += c++17

TARGET = CRUD
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    connexion.cpp \
    client.cpp

HEADERS += \
    mainwindow.h \
    connexion.h \
    client.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    MapView.qml
