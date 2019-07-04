#ifndef V_STOCK_H
#define V_STOCK_H

#include "easyORM.h"
#include "t_stock.h"


class v_stock: public easyORM
{
public:
    //INIT_CURD(t_stock) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    v_stock() { init(this); }
    ~v_stock() {;}



//    VIEW_OF(t_stock)
    VIEW_OF_WHERE(t_stock, " WHERE Quantite > 0")

    SYS_PROPERTY(int, id)


    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Designation)

    AUTO_PROPERTY(int, Quantite)
    AUTO_PROPERTY(int, Prix_Achat)
    AUTO_PROPERTY(int, Montant_Achat)

    AUTO_PROPERTY(QString, Date_Achat)
    AUTO_PROPERTY(QString, Date_Expiration)

};

#endif // V_STOCK_H
