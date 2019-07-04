#ifndef T_LOADS_H
#define T_LOADS_H

#include "easyORM.h"

class t_loads : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_loads() { init(this); }
    ~t_loads() {;}

    SYS_PROPERTY(int, id)

    AUTO_PROPERTY(QString, Date)
    AUTO_PROPERTY(QString, LIBELLE)
    AUTO_PROPERTY(int, DEPENSES)


};

#endif // T_LOADS_H
