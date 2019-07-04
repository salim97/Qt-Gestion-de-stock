#ifndef T_HISTORIQUFL_H
#define T_HISTORIQUFL_H

#include "easyORM.h"

class t_historiqueFL : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_historiqueFL() { init(this); }
    ~t_historiqueFL() {;}

    SYS_PROPERTY(int, id)
    SYS_PROPERTY(int, idH)
    SYS_PROPERTY(int, idC)

    AUTO_PROPERTY(QString, Nom_Client)
    AUTO_PROPERTY(QString, Numero_Bon_De_Commande)
    AUTO_PROPERTY(QDate, Date)

    AUTO_PROPERTY(int, Total_General)

    AUTO_PROPERTY(int, Montant_Regle)
    AUTO_PROPERTY(int, Montant_A_Regler)
    ;
public:
    enum TableName
    {
        _00id, _01idH, _02idC, _03Nom_Client,
        _04Numero_Bon_De_Commande, _05Date_Bon_De_Commande,
        _06Total_General, _07Montant_Regle, _08Montant_A_Regler
    };


};

#endif // T_HISTORIQUFL_H
