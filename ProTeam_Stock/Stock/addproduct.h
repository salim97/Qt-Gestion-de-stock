#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include <v_product.h>

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = 0, int id = -1);
    ~AddProduct();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AddProduct *ui;
    v_product productTable;

};

#endif // ADDPRODUCT_H
