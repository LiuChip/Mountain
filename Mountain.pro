QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/frameless_titlebar.cpp \
    general.cpp \
    ui/toolbar.cpp

HEADERS += \
    ui/mainwindow.h \
    ui/frameless_titlebar.h \
    general.h \
    ui/toolbar.h

FORMS += \
    ui/mainwindow.ui \
    ui/frameless_titlebar.ui \
    general.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
