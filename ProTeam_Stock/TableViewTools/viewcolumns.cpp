#include "viewcolumns.h"
#include "ui_viewcolumns.h"

#include <QDebug>

//enumEmployes _enumEmployes ;

ViewColumns::ViewColumns(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewColumns)
{
    ui->setupUi(this);

    /*
    for ( int i = 0 ; i <_enumEmployes.columns.count() ; i++ )
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData( Qt::DisplayRole, _enumEmployes.columns[i] );
        item->setData( Qt::CheckStateRole, Qt::Checked );
        ui->listWidget->addItem( item );
    }
    */

}

ViewColumns::~ViewColumns()
{
    delete ui;
}

void ViewColumns::init(QSqlTableModel *&model)
{
    QString column ;
    int columnCount = model->columnCount();
    for( int i = 1 ; i < columnCount ; i++ )
    {
        column = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        QListWidgetItem *item = new QListWidgetItem;
        item->setData( Qt::DisplayRole, column );
        item->setData( Qt::CheckStateRole, Qt::Checked );
        ui->listWidget->addItem( item );
    }
}

void ViewColumns::init(QStringList columns)
{
    for( int i = 0 ; i < columns.length() ; i++ )
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData( Qt::DisplayRole, columns[i] );
        item->setData( Qt::CheckStateRole, Qt::Checked );
        ui->listWidget->addItem( item );
    }
}

void ViewColumns::on_pushButton_Cancel_clicked()
{
    close();
}

void ViewColumns::on_pushButton_ok_clicked()
{
    for ( int i = 0 ; i < ui->listWidget->count() ; i++ )
    {
        if( ui->listWidget->item(i)->checkState() == Qt::CheckState::Unchecked )
            columnsToHide << i+1;
    }
    close();
}


void ViewColumns::on_pushButton_Unselect_All_clicked()
{
    for ( int i = 0 ; i < ui->listWidget->count() ; i++ )
    {
        ui->listWidget->item(i)->setCheckState(Qt::CheckState::Unchecked);
    }
}
