#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T16:50:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = passenger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    client_socket.cpp \
    passenger_client.cpp \
    reading_file_err.cpp \
    tools.cpp \
    passengerpanel.cpp \
    registrationform.cpp

HEADERS  += mainwindow.h \
    client_socket.h \
    network_exception.h \
    passenger_client.h \
    reading_file_err.h \
    tools.h \
    passengerpanel.h \
    registrationform.h

FORMS    += mainwindow.ui \
    passengerpanel.ui \
    registrationform.ui

RESOURCES += \
    rs.qrc
