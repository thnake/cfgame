#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T10:00:39
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Balls
TEMPLATE = app


SOURCES += main.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp \
    connectfour.cpp \
    panel.cpp \
    chip.cpp \
    mainwindow.cpp \
    dialog.cpp \
    databaseaccessclass.cpp \
    myanimation.cpp \
    audioplayer.cpp \
    mygradient.cpp

HEADERS  += \
    mygraphicsview.h \
    mygraphicsscene.h \
    connectfour.h \
    panel.h \
    chip.h \
    mainwindow.h \
    dialog.h \
    databaseaccessclass.h \
    myanimation.h \
    audioplayer.h \
    mygradient.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    res/test.qrc
