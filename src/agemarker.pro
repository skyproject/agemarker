#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T21:15:20
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

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
            Widgets\calculationwidget.ui


RESOURCES += graphics.qrc


win32:RC_FILE = resources.rc


# ------ d:/l/acl is a path to folder with agemarker-core library
# ------ d:/l/sul is a path to folder with software-update library
# ------ d:/l/suil is a path to folder with skyproject-ui library

LIBS += -Ld:/l/acl -lagemarker-core
LIBS += -Ld:/l/sul -lsoftware-update
LIBS += -Ld:/l/suil -lskyproject-ui

# ------ d:/l/acl/includes/ is a path to folder with agemarker-core library header files
# ------ d:/l/sul/includes/ is a path to folder with software-update library header files
# ------ d:/l/suil/includes/ is a path to folder with skyproject-ui library header files

INCLUDEPATH += d:/l/acl/includes/
INCLUDEPATH += d:/l/sul/includes/
INCLUDEPATH += d:/l/suil/includes/
