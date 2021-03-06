QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aircraft.cpp \
    aircraftpath.cpp \
    cdpoint.cpp \
    controller.cpp \
    convert.cpp \
    fieldpoints.cpp \
    fieldview.cpp \
    fieldviewitem.cpp \
    graphics_view_zoom.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    IAircraftObservable.h \
    IAircraftObserver.h \
    IAircraftTimerObserver.h \
    IController.h \
    IModel.h \
    aircraft.h \
    aircraftpath.h \
    cdpoint.h \
    controller.h \
    convert.h \
    fieldpoints.h \
    fieldview.h \
    fieldviewitem.h \
    graphics_view_zoom.h \
    mainwindow.h \
    model.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
