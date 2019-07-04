#ifndef T_FOURNISSEUR_H
#define T_FOURNISSEUR_H

#include "easyORM.h"

class t_fournisseur: public easyORM
{
public:
    //INIT_CURD(t_fournisseur) // add CURD methods( Create, Update, Read, Delete)
    Q_OBJECT
public:
    t_fournisseur() { init(this); }
    ~t_fournisseur() {;}

    SYS_PROPERTY(int, id)

    AUTO_PROPERTY(QString, Code)
    AUTO_PROPERTY(QString, Nom)

    AUTO_PROPERTY(QString, Adresse)
    AUTO_PROPERTY(QString, Localite)
    AUTO_PROPERTY(QString, Wilaya)

    AUTO_PROPERTY(QString, Telephone)
    AUTO_PROPERTY(QString, Fax)
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
        _03Adresse, _04Localite,
        _05Wilaya, _06Telephone,
        _07Fax, _08Email, _09Numero_RC,
        _10Numero_Fiscal, _11Numero_Art_IMPO
    };

};

#endif // T_FOURNISSEUR_H
