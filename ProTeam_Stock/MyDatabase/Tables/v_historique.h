#ifndef V_HISTORIQUE_H
#define V_HISTORIQUE_H

#include <QObject>
#include <qsqlquerymodel.h>
#include <easyORM.h>

class v_historique : public QObject
{
    Q_OBJECT
public:
    explicit v_historique(QObject *parent = nullptr);
    void select() { model.select() ;}
    QSqlTableModel *toModel(){ return &model; }
    static QString tableName() { return "v_historique" ;}
    static QString getQuery()
    {
        QString query;
        query += "CREATE VIEW IF NOT EXISTS v_historique AS " ;
        query += "select a.id, b.tableName,"
                 "CASE b.tableName WHEN 't_historiqueBR'  THEN  't_fournisseur'"
                 "ELSE 'null' END AS personneTable,"
                 " a.idF AS idP, "
                 " b.dateDocument, a.Nom_Fournisseur AS Nom,"
                 " a.total_general, a.Montant_Regle, a.Montant_A_Regler "
                 "from t_historiqueBR a, t_historique  b where a.idH == b.id";
        query += " UNION all";

        query += " select a.id, b.tableName,"
                 "CASE b.tableName WHEN 't_historiqueFE'  THEN  't_client'"
                 "ELSE 'null' END AS personneTable,"
                 " a.idC AS idP, "
                 " b.dateDocument, a.Nom_Client AS Nom,"
                 "  a.total_general, a.Montant_Regle, a.Montant_A_Regler "
                 "from t_historiqueFE a, t_historique b where a.idH == b.id";

        query += " UNION all";

        query += " select a.id, b.tableName,"
                 "CASE b.tableName WHEN 't_historiqueFL'  THEN  't_client'"
                 "ELSE 'null' END AS personneTable,"
                 " a.idC AS idP, "
                 " b.dateDocument,  a.Nom_Client AS Nom, "
                 "a.total_general, a.Montant_Regle, a.Montant_A_Regler "
                 "from t_historiqueFL a, t_historique b where a.idH == b.id";
        return query;
    }
    enum TableName
    {
        _00id, _01tableName, _02personneTable, _03idP,_04dateDocument,
        _05Nom, _06total_general, _07Montant_Regle, _08Montant_A_Regler
    };

    AUTO_PROPERTY(int, id)
    AUTO_PROPERTY(QString, tableName)
    AUTO_PROPERTY(QString, personneTable)
    AUTO_PROPERTY(int, idP)
    AUTO_PROPERTY(QString, dateDocument)
    AUTO_PROPERTY(QString, Nom)
    AUTO_PROPERTY(int, total_general)
    AUTO_PROPERTY(int, Montant_Regle)
    AUTO_PROPERTY(int, Montant_A_Regler)

signals:

public slots:

private:
    QSqlTableModel model;
};

#endif // V_HISTORIQUE_H
