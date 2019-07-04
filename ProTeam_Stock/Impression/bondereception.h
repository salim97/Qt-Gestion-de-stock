#ifndef BONDERECEPTION_H
#define BONDERECEPTION_H

#include <QDialog>
#include <QDebug>
#include <myparentobject.h>

#include "addfournisseurs.h"
#include "addstock.h"
#include "t_stock.h"
#include "t_fournisseur.h"
#include "t_historique.h"
#include "t_historiqueDetails.h"
#include "t_historiquebr.h"
#include "tableproduct.h"

namespace Ui {
class BonDeReception;
}

class BonDeReception : public QDialog, public MyParentObject
{
    Q_OBJECT

public:
    explicit BonDeReception(QWidget *parent = 0);
    ~BonDeReception();

    void fillGUI();
    void pitie(int row, int column, QString data);
    void init(QList<RowProduct> rowProduct, t_historiqueBR *historiqueBR);
    void printer();
public slots:
    void calcSum(int sum);
private slots:
    void on_toolButton_add_fournisseur_clicked();

    void on_toolButton_add_product_clicked();

    void on_toolButton_clear_clicked();

    void on_toolButton_add_to_table_clicked();

    void on_pushButton_annuler_clicked();

    void on_pushButton_confirmer_clicked();


    void on_comboBox_product_currentIndexChanged(int index);

    void on_pushButton_imprimer_clicked();

    void on_spinBox_client_a_verse_valueChanged(int arg1);

private:
    Ui::BonDeReception *ui;
    t_stock stockTable;
    t_fournisseur fournisseurTable;
    TableProduct *tableProduct;
    bool PRINTandVALID ;
};

#endif // BONDERECEPTION_H
