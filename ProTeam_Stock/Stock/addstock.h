#ifndef ADDSTOCK_H
#define ADDSTOCK_H

#include <QDialog>
#include "t_stock.h"

namespace Ui {
class AddStock;
}

class AddStock : public QDialog
{
    Q_OBJECT

public:
    explicit AddStock(QWidget *parent = 0, int id = -1);
    ~AddStock();

    QString toHTML();
    void ReCalc();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_spinBox_Quantite_valueChanged(int arg1);

    void on_spinBox_prix_achat_valueChanged(int arg1);

    void on_spinBox_PV_Gros_valueChanged(int arg1);

    void on_spinBox_PV_demi_Gros_valueChanged(int arg1);

    void on_spinBox_PV_Detail_valueChanged(int arg1);

    void on_radioButton_prix_achat_par_packet_clicked();

    void on_radioButton_prix_achat_par_montant_total_clicked();

private:
    Ui::AddStock *ui;
    t_stock stocktable ;
};

#endif // ADDSTOCK_H
