INCLUDEPATH += $$PWD/Tables
include(Tables/Tables.pri)

HEADERS += \
    $$PWD/mydatabase.h \
    $$PWD/mypropertyhelper.h \
    $$PWD/easyORM.h


SOURCES += \
    $$PWD/mydatabase.cpp \
    $$PWD/easyORM.cpp

