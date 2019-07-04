#ifndef BONDELIVRAISON_H
#define BONDELIVRAISON_H

#include "tableproduct.h"

#include <QDialog>
#include <myparentobject.h>
#include <t_client.h>
#include <t_historiqueFL.h>
#include <t_stock.h>

namespace Ui {
class BonDeLivraison;
}

class BonDeLivraison : public QDialog, public MyParentObject
{
    Q_OBJECT

public:
    explicit BonDeLivraison(QWidget *parent = 0);
    ~BonDeLivraison();

    void fillGUI();
    void pitie(int row, int column, QString data);

    void calcPrice();
    void printer();
    void init(QList<RowProduct> rowProduct, t_historiqueFL *historiqueFL);

public slots:
     void calcSum(int sum);

private slots:
    void on_toolButton_add_to_table_clicked();

    void on_toolButton_clear_clicked();

    void on_toolButton_add_product_clicked();

    void on_toolButton_add_client_clicked();

    void on_comboBox_product_currentIndexChanged(int index);

    void on_spinBox_client_a_verse_valueChanged(int arg1);

    void on_pushButton_annuler_clicked();

    void on_pushButton_confirmer_clicked();

    void on_pushButton_imprimer_clicked();

    void on_comboBox_client_currentIndexChanged(int index);

    void on_comboBox_client_type_currentIndexChanged(int index);

private:
    Ui::BonDeLivraison *ui;
    t_stock stockTable;
    t_client clientTable;
    bool PRINTandVALID ;
    TableProduct *tableProduct;
    QList<RowProduct> rowProduct ;

};

#endif // BONDELIVRAISON_H
