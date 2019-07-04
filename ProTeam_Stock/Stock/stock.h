#ifndef STOCK_H
#define STOCK_H

#include <QWidget>
#include <myparentobject.h>
#include <v_product.h>
#include <v_stock.h>
#include "t_stock.h"
#include "addstock.h"

namespace Ui {
class Stock;
}

class Stock : public QWidget, public MyParentObject
{
    Q_OBJECT

public:
    explicit Stock(QWidget *parent = 0);
    ~Stock();

    void initAction();
    void refresh(){stockTable->select(); }
private slots:

    void on_toolButton_new_product_clicked();

    void on_toolButton_product_clicked();

    void on_toolButton_stock_clicked();

    void on_tableView_product_doubleClicked(const QModelIndex &index);

    void on_tableView_stock_doubleClicked(const QModelIndex &index);

private:
    Ui::Stock *ui;
    v_stock *stockTable;
    v_product *productTable ;
};

#endif // STOCK_H
