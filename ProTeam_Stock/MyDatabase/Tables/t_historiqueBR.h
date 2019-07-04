#ifndef T_HISTORIQUEBR_H
#define T_HISTORIQUEBR_H

#include "easyORM.h"

class t_historiqueBR : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_historiqueBR() { init(this); }
    ~t_historiqueBR() {;}

    SYS_PROPERTY(int, id)
    SYS_PROPERTY(int, idH)
    SYS_PROPERTY(int, idF)

    AUTO_PROPERTY(QString, Nom_Fournisseur)
    AUTO_PROPERTY(QString, Numero_Bon_De_Commande)
    AUTO_PROPERTY(QDate, Date)

    AUTO_PROPERTY(int, Total_General)
    AUTO_PROPERTY(int, Montant_Regle)
    AUTO_PROPERTY(int, Montant_A_Regler)
    ;
public:
    enum TableName
    {
        _00id, _01idH, _02idF, _03Nom_Fournisseur,
        _04Numero_Bon_De_Commande, _05Date_Bon_De_Commande,
        _06Total_General, _07Montant_Regle, _08Montant_A_Regler
    };
};
//CREATE VEIW v_solde AS
#endif // T_HISTORIQUEBR_H
