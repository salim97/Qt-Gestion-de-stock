#ifndef T_CLIENT_H
#define T_CLIENT_H

#include "easyORM.h"

class t_client : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_client() { init(this); }
    ~t_client() {;}

    SYS_PROPERTY(int, id)

    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Nom)
    AUTO_PROPERTY(QString, Type)

    AUTO_PROPERTY(QString, Adresse)
    AUTO_PROPERTY(QString, Localite)
    AUTO_PROPERTY(QString, Wilaya)

    AUTO_PROPERTY(QString, Telephone)
    AUTO_PROPERTY(QString, Email)

    AUTO_PROPERTY(QString, Numero_RC)
    AUTO_PROPERTY(QString, Numero_Fiscal)
    AUTO_PROPERTY(QString, Numero_Art_IMPO)
    AUTO_PROPERTY(QString, Numero_IS)
    ;
public:
    enum TableName
    {
        _00id, _01Code, _02Nom,
        _03Type, _04Adresse,
        _05Localite, _06Wilaya,
        _07Telephone, _08Email,
        _09Numero_RC, _10Numero_Fiscal
    };
};

#endif // T_CLIENT_H
