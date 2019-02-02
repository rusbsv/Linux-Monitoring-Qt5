#-------------------------------------------------
#
# Project created by QtCreator 2018-06-04T23:02:01
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monitoring
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    sysinfowindow.cpp \
    userswindow.cpp \
    sravneniewindow.cpp \
    about.cpp \
    raspisaniewindow.cpp \
    processwindow.cpp \
    tcpdump.cpp \
    snmp.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    sysinfowindow.h \
    userswindow.h \
    sravneniewindow.h \
    about.h \
    raspisaniewindow.h \
    processwindow.h \
    tcpdump.h \
    snmp.h

FORMS    += mainwindow.ui \
    sysinfowindow.ui \
    userswindow.ui \
    sravneniewindow.ui \
    about.ui \
    raspisaniewindow.ui \
    processwindow.ui \
    tcpdump.ui \
    snmp.ui
