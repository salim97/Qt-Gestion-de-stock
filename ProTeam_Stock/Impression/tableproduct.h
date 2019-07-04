#ifndef TABLEPRODUCT_H
#define TABLEPRODUCT_H

#include <QObject>
#include <QTableWidget>
#include <QDebug>

class RowProduct
{
public:
    void calc() { montant = quantite * prix ;}
    int id;
    QString code, designation;
    int quantite, prix, montant ;
    int _tmp1 ;
    enum TableName
    {
        _00id, _01code, _02designation, _03quantite,
        _04prix, _05montant
    };

};

class TableProduct : public QObject
{
    Q_OBJECT
public:
    explicit TableProduct(QTableWidget *tableWidget, QObject *parent = nullptr);

    void add(RowProduct rp);
    void removeAt(int index);
    RowProduct at(int index);

    void pitie(int row, int column, QVariant data);
    QList<RowProduct> rowProducts;
    void refresh();
    void refresh(QList<RowProduct> rps){
        rowProducts = rps ;
        refresh();
    }
    void initAction();
    int getMontantTotal() const;
    void setMontantTotal(int value);

signals:
    void montantTotalChanged(int newVal);
public slots:
    void cellChanged(int x, int y);
private:
    QTableWidget *tableWidget;
    int montantTotal ;
    bool skip = false ;
};

#endif // TABLEPRODUCT_H
