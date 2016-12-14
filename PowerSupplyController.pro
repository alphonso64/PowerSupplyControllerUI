######################################################################
# Automatically generated by qmake (3.0) Wed Dec 14 04:11:30 2016
######################################################################
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = PowerSupplyController
INCLUDEPATH += .

# Input
HEADERS += const_define.h mainwindow.h \
    json/allocator.h \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/reader.h \
    json/value.h \
    json/version.h \
    json/writer.h \
    cusdialog.h \
    actiondialog.h \
    dpustatus.h \
    pcstatus.h
FORMS += mainwindow.ui \
    cusdialog.ui \
    actiondialog.ui
SOURCES += main.cpp mainwindow.cpp \
    cusdialog.cpp \
    actiondialog.cpp \
    dpustatus.cpp \
    pcstatus.cpp

unix:!macx: LIBS += -L$$PWD/ -ljsoncpp

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx: PRE_TARGETDEPS += $$PWD/libjsoncpp.a
