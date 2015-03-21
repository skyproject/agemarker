#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T21:15:20
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fext-numeric-literals
QMAKE_CXXFLAGS_RELEASE += -O2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# When compiling Agemarker with USING_FLOAT128,
# change TARGET (executable name) to "agemarker-ep".
# Don't forget to do the same for the library.
#
# Also note that the LIBS include at the bottom
# of this file should match the library's name.
TARGET = agemarker

TEMPLATE = app

SOURCES += main.cpp \
           Windows\mainwindow.cpp \
           Windows\aboutwindow.cpp \
           Windows\settingswindow.cpp \
           Windows\calculationwindow.cpp \
           Windows\recoverywindow.cpp \
           Widgets\oxidestablewidget.cpp \
           Widgets\elementstablewidget.cpp \
           Widgets\settingstablewidget.cpp \
           Widgets\contentunitstable.cpp \
           Widgets\calculationwidget.cpp \
           Widgets\multiplierwidget.cpp \
           Widgets\welcomewidget.cpp \
           IO\calculationdata.cpp \
           IO\results.cpp \
           initialize.cpp \
           data.cpp


HEADERS  += Windows\mainwindow.h \
            Windows\aboutwindow.h \
            Windows\settingswindow.h \
            Windows\calculationwindow.h \
            Windows\recoverywindow.h \
            Widgets\oxidestablewidget.h \
            Widgets\elementstablewidget.h \
            Widgets\settingstablewidget.h \
            Widgets\contentunitstable.h \
            Widgets\calculationwidget.h \
            Widgets\multiplierwidget.h \
            Widgets\welcomewidget.h \
            IO\calculationdata.h \
            IO\results.h \
            initialize.h \
            application.h \
            data.h


FORMS    += Windows\mainwindow.ui \
            Windows\aboutwindow.ui \
            Windows\settingswindow.ui \
            Windows\calculationwindow.ui \
            Windows\recoverywindow.ui \
            Widgets\oxidestablewidget.ui \
            Widgets\elementstablewidget.ui \
            Widgets\settingstablewidget.ui \
            Widgets\contentunitstable.ui \
            Widgets\calculationwidget.ui \
            Widgets\multiplierwidget.ui \
            Widgets\welcomewidget.ui


RESOURCES += graphics.qrc


win32:RC_FILE = resources.rc

LIBS += -lquadmath

# When compiling Agemarker with USING_FLOAT128,
# change "-lagemarker-core" to "-lagemarker-core-ep".
LIBS += -Lc:/Users/mlabu_000.RESONANS-PC/Documents/Builds/agemarker-core/debug -lagemarker-core
LIBS += -Lc:/Users/mlabu_000.RESONANS-PC/Documents/Builds/software-update/debug -lsoftware-update
LIBS += -Lc:/Users/mlabu_000.RESONANS-PC/Documents/Builds/skyproject-ui/debug -lskyproject-ui

INCLUDEPATH += $$quote(c:/Users/mlabu_000.RESONANS-PC/Documents/GitHub/agemarker-core/src)
INCLUDEPATH += $$quote(c:/Users/mlabu_000.RESONANS-PC/Documents/GitHub/skyproject-ui/src)
INCLUDEPATH += $$quote(c:/Users/mlabu_000.RESONANS-PC/Documents/GitHub/software-update/src)

INCLUDEPATH += $$quote(c:/Users/mlabu_000.RESONANS-PC/Documents/Libs)
