#include "tableproduct.h"

#include <QAction>

TableProduct::TableProduct(QTableWidget *tablewidget, QObject *parent) : QObject(parent)
{
    this->tableWidget = tablewidget;
    tablewidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "id"
                      << "Code" << "Designation"<< "Quantite"<< "Prix"<< "Montant");
    tablewidget->hideColumn(0);
    initAction();
    connect(tablewidget, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
}

void TableProduct::add(RowProduct rp)
{
    rowProducts.append(rp);
    refresh();
    //    int rowCount = rowProducts.length();
//    tableWidget->setRowCount(rowCount);
//    int i = rowCount-1 ;
//    pitie(i, 0, rp.id);
//    pitie(i, 1, rp.code);
//    pitie(i, 2, rp.designation);
//    pitie(i, 3, rp.quantite);
//    pitie(i, 4, rp.prix);
//    pitie(i, 5, rp.montant);

}

void TableProduct::removeAt(int index)
{
    rowProducts.removeAt(index);
    refresh();
}

RowProduct TableProduct::at(int index)
{

}

void TableProduct::pitie(int row, int column, QVariant data)
{
    tableWidget->setItem(row, column, new QTableWidgetItem(data.toString()));
}

void TableProduct::refresh()
{
    skip = true;
    montantTotal = 0 ;
    int rowCount = rowProducts.length();
    tableWidget->setRowCount(rowCount);
//    ui->tableWidget->insertRow(rowCount+1);
    for( int i = 0 ; i < rowCount ; i++ )
    {
        pitie(i, RowProduct::_00id, rowProducts.at(i).id);
        pitie(i, RowProduct::_01code, rowProducts.at(i).code);
        pitie(i, RowProduct::_02designation, rowProducts.at(i).designation);
        pitie(i, RowProduct::_03quantite, rowProducts.at(i).quantite);
        pitie(i, RowProduct::_04prix, rowProducts.at(i).prix);
        pitie(i, RowProduct::_05montant, rowProducts.at(i).montant);
        rowProducts[i].calc();
        montantTotal += rowProducts[i].montant ;
    }
    setMontantTotal(montantTotal);
    skip = false;
}

void TableProduct::initAction()
{
    // init widget action
    QAction  *supprime;
    supprime = new QAction("Suppr", this);
    //Icon
    supprime->setIcon(QIcon(":/icon/icon/Delete-96.png"));
    // on click
    connect(supprime, &QAction::triggered, [this]() {
            removeAt(tableWidget->currentIndex().row()); });


    // init table with action
    tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    tableWidget->addAction(supprime);
}

int TableProduct::getMontantTotal() const
{
    return montantTotal;
}

void TableProduct::setMontantTotal(int value)
{
    emit montantTotalChanged(value);
    montantTotal = value;
}

void TableProduct::cellChanged(int x, int y)
{
    if(skip) return ;
    if( y == RowProduct::_01code) rowProducts[x].code = tableWidget->item(x, 1)->text();
    if( y == RowProduct::_02designation) rowProducts[x].designation = tableWidget->item(x, 2)->text();
    if( y == RowProduct::_03quantite) rowProducts[x].quantite = tableWidget->item(x, 3)->text().toInt();
    if( y == RowProduct::_04prix) rowProducts[x].prix = tableWidget->item(x, 4)->text().toInt();
    if( y == RowProduct::_05montant) rowProducts[x].montant = tableWidget->item(x, 5)->text().toInt();
    rowProducts[x].calc();
    refresh();
}

