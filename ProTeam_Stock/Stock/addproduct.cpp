#include "addproduct.h"
#include "ui_addproduct.h"

AddProduct::AddProduct(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddProduct)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Product");

    productTable.setCurrentRow(-1);
    if(id > -1)
    {
        productTable.where("id == "+QString::number(id)) ;
        ui->lineEdit_Code->setText(productTable.getCode());
        ui->lineEdit_Designation->setText(productTable.getDesignation());

        ui->spinBox_PV_demi_Gros->setValue(productTable.getPrix_Vente_Demi_Gros());
        ui->spinBox_PV_Gros->setValue(productTable.getPrix_Vente_Gros());
        ui->spinBox_PV_Detail->setValue(productTable.getPrix_Vente_Detail());

    }
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_buttonBox_rejected()
{
    close();
}

void AddProduct::on_buttonBox_accepted()
{
    productTable.setCode(ui->lineEdit_Code->text()) ;
    productTable.setDesignation(ui->lineEdit_Designation->text());
    productTable.setPrix_Vente_Demi_Gros(ui->spinBox_PV_demi_Gros->value());
    productTable.setPrix_Vente_Detail(ui->spinBox_PV_Detail->value());
    productTable.setPrix_Vente_Gros(ui->spinBox_PV_Gros->value());
    if(productTable.currentRow() < 0)
        qDebug() << Q_FUNC_INFO << productTable.insertChild();
    else
        qDebug() << Q_FUNC_INFO << productTable.updateChild();

    close();
}
