#include "addstock.h"
#include "ui_addstock.h"


AddStock::AddStock(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddStock)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Product");
    ui->dateEdit_date_expiration->setDate(QDate::currentDate());
    ui->dateEdit_date_achat->setDate(QDate::currentDate());
    stocktable.setCurrentRow(-1);
    if(id > -1)
    {
        stocktable.where("id == "+QString::number(id)) ;

        ui->lineEdit_Code->setText(stocktable.getCode());
        ui->lineEdit_Designation->setText(stocktable.getDesignation());

        ui->radioButton_prix_achat_par_packet->setChecked(true);
        ui->radioButton_prix_achat_par_montant_total->setChecked(false);

        ui->spinBox_prix_achat->setValue(stocktable.getPrix_Achat());

        ui->spinBox_PV_demi_Gros->setValue(stocktable.getPrix_Vente_Demi_Gros());
        ui->spinBox_PV_Gros->setValue(stocktable.getPrix_Vente_Gros());
        ui->spinBox_PV_Detail->setValue(stocktable.getPrix_Vente_Detail());

        ui->spinBox_Quantite->setValue(stocktable.getQuantite());

        ui->dateEdit_date_achat->setDate(QDate::fromString(stocktable.getDate_Achat(), "yyyy-MM-dd"));
        ui->dateEdit_date_expiration->setDate(QDate::fromString(stocktable.getDate_Expiration(), "yyyy-MM-dd"));

    }
    ui->comboBox_categorie->setVisible(false);
    ui->label_9->setVisible(false);

}

AddStock::~AddStock()
{
    delete ui;
}

void AddStock::on_buttonBox_accepted()
{
    stocktable.setCode(ui->lineEdit_Code->text()) ;
    stocktable.setDesignation(ui->lineEdit_Designation->text());
    stocktable.setDate_Expiration(ui->dateEdit_date_expiration->date().toString("yyyy-MM-dd"));
    stocktable.setDate_Achat(ui->dateEdit_date_achat->date().toString("yyyy-MM-dd"));
    if(stocktable.currentRow() < 0)
        qDebug() << "void AddStock::on_buttonBox_accepted() stocktable.insert() : " << stocktable.insert();
    else
        qDebug() << "void AddStock::on_buttonBox_accepted() stocktable.update() : " << stocktable.update();
    close();
}

void AddStock::on_buttonBox_rejected()
{
    close();
}

void AddStock::on_spinBox_Quantite_valueChanged(int arg1)
{
    stocktable.setQuantite(arg1);
    ui->label_view->setText(toHTML());
    ReCalc();
}

void AddStock::on_spinBox_prix_achat_valueChanged(int arg1)
{
    if(ui->radioButton_prix_achat_par_montant_total->isChecked())
    {
        stocktable.setMontant_Achat(arg1);
        stocktable.setPrix_Achat(arg1 / stocktable.getQuantite());
    }
    else
    {
        stocktable.setMontant_Achat( arg1 * stocktable.getQuantite());
        stocktable.setPrix_Achat(arg1);
    }

    ui->label_view->setText(toHTML());
}

void AddStock::on_spinBox_PV_Gros_valueChanged(int arg1)
{
    stocktable.setPrix_Vente_Gros(arg1);
    ui->label_view->setText(toHTML());
}

void AddStock::on_spinBox_PV_demi_Gros_valueChanged(int arg1)
{
    stocktable.setPrix_Vente_Demi_Gros(arg1);
    ui->label_view->setText(toHTML());
}

void AddStock::on_spinBox_PV_Detail_valueChanged(int arg1)
{
    stocktable.setPrix_Vente_Detail(arg1);
    ui->label_view->setText(toHTML());
}

void AddStock::on_radioButton_prix_achat_par_packet_clicked()
{
    ReCalc();
}

void AddStock::on_radioButton_prix_achat_par_montant_total_clicked()
{
    ReCalc();
}

void AddStock::ReCalc()
{
    stocktable.setQuantite(ui->spinBox_Quantite->value());

    on_spinBox_prix_achat_valueChanged(ui->spinBox_prix_achat->value());

    on_spinBox_PV_Gros_valueChanged(ui->spinBox_PV_Gros->value());

    on_spinBox_PV_demi_Gros_valueChanged(ui->spinBox_PV_demi_Gros->value());

    on_spinBox_PV_Detail_valueChanged(ui->spinBox_PV_Detail->value());

    ui->label_view->setText(toHTML());
}

QString AddStock::toHTML()
{
    QString html ;
    html +="<html><head/><body>" ;

    html += "<p>Quantity: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getQuantite())+"</span></p>" ;
    html += "<br><hr><br>" ;
    html += "<p>Prix achat d un paquet: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getPrix_Achat())+"</span></p>" ;
    html += "<p>Montant total: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getMontant_Achat())+"</span></p>" ;
    html += "<hr><br>" ;

    html += "<p>Prix vente paquet en Gros: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getPrix_Vente_Gros())+"</span></p>" ;
    html += "<p>Prix vente paquet en Demi Gros: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getPrix_Vente_Demi_Gros())+"</span></p>" ;
    html += "<p>Prix vente paquet en Detail: <span style=\" font-size:12pt;\">"+QString::number(stocktable.getPrix_Vente_Detail())+"</span></p>" ;

    html += "<hr><br>" ;


    return html ;
}
