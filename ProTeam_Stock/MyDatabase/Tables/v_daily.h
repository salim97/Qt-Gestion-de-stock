#ifndef V_DAILY_H
#define V_DAILY_H

#include <QObject>
#include <qsqlquerymodel.h>
#include <easyORM.h>


class v_dialy : public QObject
{
    Q_OBJECT
public:
    explicit v_dialy(QObject *parent = nullptr)
    {

    }
    void select() { model.select() ;}
    QSqlTableModel *toModel(){ return &model; }
    static QString tableName() { return "v_dialy" ;}
    static QString getQuery()
    {
        QString query;
        query += "CREATE VIEW IF NOT EXISTS v_dialy AS select d.id, d.idH, d.idP, h.dateDocument, "
                 "  CASE tableName "
                 " WHEN 't_historiqueBR'  THEN 'Entrer' "
                 " WHEN 't_historiqueFL'  THEN 'Sortie'"
                 " WHEN 't_historiqueFE'  THEN 'Sortie'"
                 " ELSE NULL END AS type, "
                 " d.Code, d.Designation, d.Quantite, d.Prix, d.Montant "
                 " from t_historique h, t_historiqueDetails d where h.id == d.idH ORDER BY h.dateDocument DESC";

        return query;
    }
    enum TableName
    {
        _00id, _01idH, _02idP, _03dateDocument,_04type,
        _05Code, _06Designation, _07Quantite, _08Prix, _09Montant
    };


signals:

public slots:

private:
    QSqlTableModel model;
};


#endif // V_DAILY_H
