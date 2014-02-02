#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T10:00:39
#
#-------------------------------------------------

QT       += core gui sql multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Balls
TEMPLATE = app


SOURCES += main.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp \
    connectfour.cpp \
    chip.cpp \
    dialog.cpp \
    databaseaccessclass.cpp \
    myanimation.cpp \
    audioplayer.cpp \
    mygradient.cpp \
    myfield.cpp \
    aiplayer.cpp

HEADERS  += \
    mygraphicsview.h \
    mygraphicsscene.h \
    connectfour.h \
    chip.h \
    dialog.h \
    databaseaccessclass.h \
    myanimation.h \
    audioplayer.h \
    mygradient.h \
    myfield.h \
    aiplayer.h

FORMS    += \
    dialog.ui \
    message.ui

RESOURCES += \
    res/test.qrc
