#ifndef T_HISTORIQUFE_H
#define T_HISTORIQUFE_H

#include "easyORM.h"

class t_historiqueFE : public easyORM
{
    //    INIT_CURD(t_client) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_historiqueFE() { init(this); }
    ~t_historiqueFE() {;}

    SYS_PROPERTY(int, id)
    SYS_PROPERTY(int, idH)
    SYS_PROPERTY(int, idC)


    AUTO_PROPERTY(QString, Nom_Client)
    AUTO_PROPERTY(QString, TypeClient) // TODO : important for benifice separe

    AUTO_PROPERTY(QString, Numero_Bon_De_Commande)
    AUTO_PROPERTY(QDate, Date)

    AUTO_PROPERTY(int, Montant_H_T)
    AUTO_PROPERTY(int, Montant_T_V_A)
    AUTO_PROPERTY(int, Montant_Timbre)
    AUTO_PROPERTY(int, Total_General)

    AUTO_PROPERTY(int, Montant_Regle)
    AUTO_PROPERTY(int, Montant_A_Regler)
    ;
public:
    enum TableName
    {
        _00id, _01idH, _02idC, _03Nom_Client,
        _04Numero_Bon_De_Commande, _05Date_Bon_De_Commande,
        _06Montant_H_T, _07Montant_T_V_A, _08Montant_Timbre,
        _09Total_General, _10Montant_Regle, _11Montant_A_Regler
    };

};

#endif // T_HISTORIQUFE_H
