QT       += widgets

TARGET = qtfig
TEMPLATE = lib

DEFINES += QTFIG_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        QFig.cpp

HEADERS += \
        QFig.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
