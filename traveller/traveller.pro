#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T20:53:31
#
#-------------------------------------------------

QT       += core gui
# has to add sql module
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = traveller
TEMPLATE = app


SOURCES += main.cpp\
        travellermainwindow.cpp \
    welcomeframe.cpp \
    addnewtripframe.cpp \
    commoncolor.cpp \
    homeinfopane.cpp \
    ttextlabel.cpp \
    tlineedit.cpp \
    staticdata.cpp \
    tbutton.cpp \
    newdaypane.cpp \
    tcombobox.cpp \
    tpalette.cpp \
    tfont.cpp \
    tcombowithaddfield.cpp \
    eventpane.cpp \
    tcombowithcost.cpp \
    travellermodel.cpp \
    tripitem.cpp \
    dayitem.cpp \
    eventitem.cpp \
    tdatabase.cpp \
    travellercontroller.cpp \
    tripframe.cpp \
    stylesheetceator.cpp \
    cityitem.cpp \
    triptitleframe.cpp \
    tripdetailframe.cpp \
    triptitleframe.cpp \
    daylistframe.cpp \
    dayitemframe.cpp \
    cityitemframe.cpp \
    eventitemframe.cpp \
    addtripbuttonframe.cpp \
    addnewtripwindow.cpp \
    tripitemmenu.cpp \
    addeventorcitybutton.cpp \
    addneweventwindow.cpp \
    addnewcitywindow.cpp \
    citytitleframe.cpp \
    daytitleframe.cpp

HEADERS  += travellermainwindow.h \
    welcomeframe.h \
    addnewtripframe.h \
    commoncolor.h \
    homeinfopane.h \
    ttextlabel.h \
    tlineedit.h \
    staticdata.h \
    tbutton.h \
    newdaypane.h \
    tcombobox.h \
    tpalette.h \
    tfont.h \
    tcombowithaddfield.h \
    eventpane.h \
    tcombowithcost.h \
    travellermodel.h \
    tripitem.h \
    dayitem.h \
    eventitem.h \
    tdatabase.h \
    travellercontroller.h \
    tripframe.h \
    stylesheetceator.h \
    cityitem.h \
    tripdetailframe.h \
    triptitleframe.h \
    daylistframe.h \
    dayitemframe.h \
    cityitemframe.h \
    eventitemframe.h \
    addtripbuttonframe.h \
    addnewtripwindow.h \
    tripitemmenu.h \
    addeventorcitybutton.h \
    addneweventwindow.h \
    addnewcitywindow.h \
    citytitleframe.h \
    daytitleframe.h

FORMS    += travellermainwindow.ui
