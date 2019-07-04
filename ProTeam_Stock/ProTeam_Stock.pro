#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:00:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProTeam_Stock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# those are my fucking library
############################################
INCLUDEPATH += $$PWD/MyDatabase
include(MyDatabase/MyDatabase.pri)

INCLUDEPATH += $$PWD/TableViewTools
include(TableViewTools/TableViewTools.pri)

INCLUDEPATH += $$PWD/QtRptProject
include($$PWD/QtRptProject/QtRPT/QtRPT.pri)

############################################

INCLUDEPATH += $$PWD/Client
include(Client/Client.pri)

INCLUDEPATH += $$PWD/Fournisseurs
include(Fournisseurs/Fournisseurs.pri)

INCLUDEPATH += $$PWD/Stock
include(Stock/Stock.pri)

INCLUDEPATH += $$PWD/Impression
include(Impression/Impression.pri)

INCLUDEPATH += $$PWD/Loads
include(Loads/Loads.pri)

INCLUDEPATH += $$PWD/Documents
include(Documents/Documents.pri)

INCLUDEPATH += $$PWD/Historique
include(Historique/Historique.pri)

INCLUDEPATH += $$PWD/Solde
include(Solde/Solde.pri)



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myparentobject.cpp \
    settings.cpp \
    chekla.cpp \
    mybackuptousb.cpp

HEADERS += \
        mainwindow.h \
    myparentobject.h \
    settings.h \
    chekla.h \
    mybackuptousb.h

FORMS += \
        mainwindow.ui \
    settings.ui \
    chekla.ui \
    mybackuptousb.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc



# my auto deploy on release mode
CONFIG(release, debug|release ) {
    # set exe to bin directory and others file to tmp
    OBJECTS_DIR = tmp
    MOC_DIR = tmp
    DESTDIR = bin

    # on release mode
    win32{
        TARGET_EXT = .exe
        DEPLOY_COMMAND = windeployqt
        DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/$${DESTDIR}/$${TARGET}$${TARGET_EXT}))

        #warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})
        QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
    }
}
