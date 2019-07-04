#include "addproduct.h"
#include "stock.h"
#include "ui_stock.h"

Stock::Stock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stock)
{
    ui->setupUi(this);
    initAction();

    stockTable = new v_stock() ;
    productTable = new v_product();

    ui->tableView_stock->setModel(stockTable->toModel());
    stockTable->tableViewConfigVisibleColumns(ui->tableView_stock);
    ui->widget_stock->setTableView(ui->tableView_stock);
    ui->widget_stock->setModel(stockTable);

    ui->tableView_product->setModel(productTable->toModel());
    productTable->tableViewConfigVisibleColumns(ui->tableView_product);
    ui->widget_product->setTableView(ui->tableView_product);
    ui->widget_product->setModel(productTable);

    ui->tableView_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_product->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->stackedWidget->setCurrentIndex(0);
}

Stock::~Stock()
{
    delete ui;
    delete stockTable;
    delete productTable;
}

void Stock::on_toolButton_new_product_clicked()
{
//    AddStock addStock ;
//    addStock.exec();
//    stockTable->select();
    AddProduct addproduct;
    addproduct.exec();
    productTable->select();
    ui->stackedWidget->setCurrentIndex(0);
}

void Stock::initAction()
{
    // init widget action
    QAction *ajoute, *modifie;
    ajoute = new QAction(ui->toolButton_new_product->text(), this);
    modifie = new QAction("Modifier", this);

    //Icon
    ajoute->setIcon(ui->toolButton_new_product->icon());
    modifie->setIcon(QIcon(":/icon/icon/Edit Column-96.png"));


    // on click
    connect(ajoute, SIGNAL(triggered(bool)), this, SLOT(on_toolButton_new_product_clicked()));
    connect(modifie, &QAction::triggered, [this]() {
            on_tableView_product_doubleClicked(ui->tableView_stock->currentIndex()); });

    // init table with action
    ui->tableView_stock->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView_stock->addAction(ajoute);
    ui->tableView_stock->addAction(modifie);

    ui->widget_stock->initAction(ui->tableView_stock);
    ui->widget_product->initAction(ui->tableView_product);

}

void Stock::on_toolButton_product_clicked()
{
    productTable->select();
    ui->stackedWidget->setCurrentIndex(0);
}

void Stock::on_toolButton_stock_clicked()
{
    stockTable->select();
    ui->stackedWidget->setCurrentIndex(1);
}

void Stock::on_tableView_product_doubleClicked(const QModelIndex &index)
{
    productTable->setCurrentRow(index.row());
    AddProduct addproduct(this, productTable->getid());
    addproduct.exec();
    productTable->select();
}

void Stock::on_tableView_stock_doubleClicked(const QModelIndex &index)
{
    stockTable->setCurrentRow(index.row());
    AddStock addStock(this, stockTable->getid());
    addStock.exec();
    stockTable->select();
}
