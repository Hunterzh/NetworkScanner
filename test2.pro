#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T13:31:11
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += sql
QT       += xml
QT       += network
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES +=\
    socket/crc32.cpp \
    socket/udpsocket.cpp \
    form/adddevice.cpp \
    form/alarm.cpp \
    form/device.cpp \
    form/home.cpp \
    form/login.cpp \
    form/setting.cpp \
    form/user.cpp \
    com/externvalue.cpp \
    com/main.cpp \
    database/sqldb.cpp \
    socket/tcpclient.cpp \
    device/modelpei.cpp \
    database/initdatabase.cpp \
    device/modelchest.cpp \
    device/modelscan.cpp \
    device/modeltreenode.cpp \
    device/modelswitch.cpp \
    device/modelpeixianjialink.cpp \
    com/qtreeviewmouseevent.cpp \
    com/loadmemorythread.cpp

HEADERS  += \
    socket/crc32.h \
    socket/udpsocket.h \
    form/adddevice.h \
    form/alarm.h \
    form/device.h \
    form/home.h \
    form/login.h \
    form/setting.h \
    form/user.h \
    database/mysql.h \
    com/externvalue.h \
    database/sqldb.h \
    socket/tcpclient.h \
    device/modelpei.h \
    database/initdatabase.h \
    device/modelchest.h \
    device/modelscan.h \
    device/modeltreenode.h \
    device/modelswitch.h \
    com/scroll.h \
    com/scroll.h \
    device/modelpeixianjialink.h \
    com/qtreeviewmouseevent.h \
    com/loadmemorythread.h

FORMS    += \
    login.ui \
    user.ui \
    home.ui \
    device.ui \
    adddevice.ui \
    setting.ui \
    alarm.ui

RESOURCES += \
    resoure.qrc

DISTFILES += \
    qss/home.qss \
    qss/login.qss \
    qss/device.qss \
    qss/addDevice.qss \
    qss/user.qss \
    qss/setting.qss \
    qss/alarm.qss


INCLUDEPATH += "C:\Program Files (x86)\MySQL\MySQL Server 5.5\include"
INCLUDEPATH += ./form
INCLUDEPATH += ./device
INCLUDEPATH += ./com
INCLUDEPATH += ./socket
INCLUDEPATH += ./database

LIBS += "C:\Program Files (x86)\MySQL\MySQL Server 5.5\lib\libmysql.lib"

win32-msvc*:QMAKE_CXXFLAGS += /wd"4819"

RC_ICONS = scan.ico
