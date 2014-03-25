#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T21:15:20
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -O2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = agemarker
TEMPLATE = app


SOURCES += main.cpp \
           Windows\mainwindow.cpp \
           Windows\aboutwindow.cpp \
           Windows\settingswindow.cpp \
           Windows\calculationwindow.cpp \
           Widgets\oxidestablewidget.cpp \
           Widgets\elementstablewidget.cpp \
           Widgets\settingstablewidget.cpp \
           Widgets\calculationwidget.cpp \
           Widgets\multiplierwidget.cpp \
           Widgets\welcomewidget.cpp \
           IO\calculationdata.cpp \
           IO\results.cpp \
           data.cpp


HEADERS  += Windows\mainwindow.h \
            Windows\aboutwindow.h \
            Windows\settingswindow.h \
            Windows\calculationwindow.h \
            Widgets\oxidestablewidget.h \
            Widgets\elementstablewidget.h \
            Widgets\settingstablewidget.h \
            Widgets\calculationwidget.h \
            Widgets\multiplierwidget.h \
            Widgets\welcomewidget.h \
            IO\calculationdata.h \
            IO\results.h \
            application.h \
            data.h


FORMS    += Windows\mainwindow.ui \
            Windows\aboutwindow.ui \
            Windows\settingswindow.ui \
            Windows\calculationwindow.ui \
            Widgets\oxidestablewidget.ui \
            Widgets\elementstablewidget.ui \
            Widgets\settingstablewidget.ui \
            Widgets\calculationwidget.ui \
            Widgets\multiplierwidget.ui \
            Widgets\welcomewidget.ui


RESOURCES += graphics.qrc


win32:RC_FILE = resources.rc


LIBS += -Lc:/Users/mlabu_000/Documents/Builds -lagemarker-core
LIBS += -Lc:/Users/mlabu_000/Documents/Builds -lsoftware-update
LIBS += -Lc:/Users/mlabu_000/Documents/Builds -lskyproject-ui


INCLUDEPATH += $$quote(c:/Users/mlabu_000/Documents/Builds/Include)
