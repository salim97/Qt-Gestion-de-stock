#ifndef V_PRODUCT_H
#define V_PRODUCT_H


#include "easyORM.h"
#include "t_stock.h"

class v_product: public easyORM
{
public:
    //INIT_CURD(t_stock) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    v_product() { init(this); }
    ~v_product() {;}

    VIEW_OF(t_stock)

    SYS_PROPERTY(int, id)

    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Designation)


    AUTO_PROPERTY(int, Prix_Vente_Gros)
    AUTO_PROPERTY(int, Prix_Vente_Demi_Gros)
    AUTO_PROPERTY(int, Prix_Vente_Detail)

};

#endif // V_PRODUCT_H
