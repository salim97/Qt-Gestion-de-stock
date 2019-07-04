#ifndef FACTURE_H
#define FACTURE_H

#include <QDialog>
#include <t_stock.h>
#include <t_client.h>
#include <t_historiqueFE.h>
#include "myparentobject.h"
#include "tableproduct.h"

namespace Ui {
class Facture;
}

class Facture : public QDialog, public MyParentObject
{
    Q_OBJECT

public:
    explicit Facture(QWidget *parent = 0);
    ~Facture();

    void fillGUI();
    void calcPrice();
    void init(QList<RowProduct> rowProduct, t_historiqueFE *historiqueFE);
    void printer();
private slots:
    void calcSum(int sum);

    void on_toolButton_clear_clicked();

    void on_toolButton_add_to_table_clicked();

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
    Ui::Facture *ui;
    t_stock stockTable;
    t_client clientTable;
    QList<RowProduct> rowProduct ;
    TableProduct *tableProduct;
    double tva ;
    bool PRINTandVALID ;
};

#endif // FACTURE_H
