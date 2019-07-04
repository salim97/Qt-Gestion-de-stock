#pragma once
#include <QObject>
#include <QDate>

#define READONLY_PROPERTY(TYPE, NAME, VAL) \
    Q_PROPERTY(TYPE NAME READ NAME CONSTANT ) \
    public: \
       TYPE NAME() const { return m_ ## NAME ; } \
    private: \
       void NAME(TYPE value) {m_ ## NAME = value; } \
       TYPE m_ ## NAME = VAL ;


#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ get ## NAME WRITE set ## NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE get ## NAME() const { return m_ ## NAME ; } \
       void set ## NAME(TYPE value) { \
          if (m_ ## NAME == value)  return; \
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE m_ ## NAME;

#define VIEW_OF(TABLE) \
    READONLY_PROPERTY(QVariant, _parentTable, #TABLE) \
    TABLE parentTable ; \
public:\
    bool updateChild(){\
       if(!parentTable.whereid(getid()))\
           return false ;\
       fillparent();\
       return parentTable.update();\
    }\
    bool insertChild(){\
        parentTable.clearRow();\
        fillparent();\
        return parentTable.insert();\
    }\
private:\
    void fillparent()\
    {\
        for(int i = this->metaObject()->propertyOffset(); i < this->metaObject()->propertyCount(); i++)\
        {\
            if(this->metaObject()->property(i).name() == "id")\
                continue ;\
            if(QString(this->metaObject()->property(i).name()).at(0) == '_')\
                continue;\
            parentTable.setProperty(this->metaObject()->property(i).name(), this->metaObject()->property(i).read(this));\
        }\
    }

#define VIEW_OF_WHERE(TABLE, CONDITION) \
    VIEW_OF(TABLE)\
    READONLY_PROPERTY(QVariant, _extraCondition, #CONDITION)

#define SYS_PROPERTY(TYPE, NAME) \
    AUTO_PROPERTY(TYPE, NAME) \
    AUTO_PROPERTY(TYPE, _ ## NAME)

#define INIT_CURD(CLASS_NAME) \
    Q_OBJECT \
    public:\
    CLASS_NAME() { init(this); }


