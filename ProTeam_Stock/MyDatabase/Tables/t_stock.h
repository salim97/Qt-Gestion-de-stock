#ifndef T_PRODUITS_H
#define T_PRODUITS_H

#include "easyORM.h"

class t_stock: public easyORM
{
public:
    //INIT_CURD(t_stock) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_stock() { init(this); }
    ~t_stock() {;}

    SYS_PROPERTY(int, id)


    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Designation)

    AUTO_PROPERTY(int, Quantite)
    AUTO_PROPERTY(int, Prix_Achat)
    AUTO_PROPERTY(int, Montant_Achat)

    AUTO_PROPERTY(int, Prix_Vente_Gros)
    AUTO_PROPERTY(int, Prix_Vente_Demi_Gros)
    AUTO_PROPERTY(int, Prix_Vente_Detail)

    //AUTO_PROPERTY(QString, Montant_Vente)

    //AUTO_PROPERTY(QString, Recate)
    //    AUTO_PROPERTY(QDate, Date_Achat)
    AUTO_PROPERTY(QString, Date_Achat)
    //    AUTO_PROPERTY(QDate, Date_Expiration)
    AUTO_PROPERTY(QString, Date_Expiration)

};

#endif // T_PRODUITS_H
