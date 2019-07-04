#ifndef T_HISTORIQUE_H
#define T_HISTORIQUE_H

#include "easyORM.h"

class t_historique : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_historique() { init(this); }
    ~t_historique() {;}

    SYS_PROPERTY(int, id)

    AUTO_PROPERTY(QDate, dateDocument)
    AUTO_PROPERTY(QString, tableName)
    ;
public:
    enum TableName
    {
        _00id, _01dateDocument
    };
};

#endif // T_HISTORIQUE_H
