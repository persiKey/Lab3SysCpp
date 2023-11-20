QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database.cpp \
    dbdisplayer.cpp \
    filemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    radio.cpp

HEADERS += \
    Database.hpp \
    dbdisplayer.h \
    filemanager.h \
    mainwindow.h \
    radio.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Lab3.pro.user

FORMS +=
