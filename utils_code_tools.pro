#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T17:50:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utils_code_tools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codeformatter.cpp \
    common_type.cpp

HEADERS  += mainwindow.h \
    common_type.h \
    codeformatter.h

FORMS    += mainwindow.ui
