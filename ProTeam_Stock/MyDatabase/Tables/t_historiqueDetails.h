#ifndef T_HISTORIQUEDETAILS_H
#define T_HISTORIQUEDETAILS_H

#include "easyORM.h"

class t_historiqueDetails : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_historiqueDetails() { init(this); }
    ~t_historiqueDetails() {;}

    SYS_PROPERTY(int, id)
    SYS_PROPERTY(int, idH)
    SYS_PROPERTY(int, idP)

    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Designation)

    AUTO_PROPERTY(int, Quantite)
    AUTO_PROPERTY(int, Prix)
    AUTO_PROPERTY(int, Montant)
    ;
public:
    enum TableName
    {
        _00id, _01idH, _02idP,
        _03Code, _04Designation,
        _05Categorie, _06Quantite, _07Prix
    };
};

#endif // T_HISTORIQUEDETAILS_H
