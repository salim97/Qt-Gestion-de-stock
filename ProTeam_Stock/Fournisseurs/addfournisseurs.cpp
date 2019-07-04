#include "addfournisseurs.h"
#include "ui_addfournisseurs.h"

AddFournisseurs::AddFournisseurs(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddFournisseurs)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Fournisseur");
    fournisseurTable.setCurrentRow(-1);
    if(id > -1)
    {
        fournisseurTable.where("id == "+QString::number(id)) ;

        ui->lineEdit_Code->setText(fournisseurTable.getCode());
        ui->lineEdit_Nom->setText(fournisseurTable.getNom());
        ui->lineEdit_Adresse->setText(fournisseurTable.getAdresse());
        ui->lineEdit_Localite->setText(fournisseurTable.getLocalite());
        for(int i = 0 ; i  < ui->comboBox_Wilaya->count() ; i++ )
            if(ui->comboBox_Wilaya->itemText(i) == fournisseurTable.getWilaya())
                ui->comboBox_Wilaya->setCurrentIndex(i);

        ui->lineEdit_Art_IMPO->setText(fournisseurTable.getNumero_Art_IMPO());
        ui->lineEdit_Fiscal->setText(fournisseurTable.getNumero_Fiscal());
        ui->lineEdit_RC->setText(fournisseurTable.getNumero_RC());

        ui->lineEdit_E_Mail->setText(fournisseurTable.getEmail());
        ui->lineEdit_Telephone->setText(fournisseurTable.getTelephone());
        ui->lineEdit_Fax->setText(fournisseurTable.getFax());

    }
}

AddFournisseurs::~AddFournisseurs()
{
    delete ui;
}

void AddFournisseurs::on_buttonBox_accepted()
{
    fournisseurTable.setCode(ui->lineEdit_Code->text());
    fournisseurTable.setNom(ui->lineEdit_Nom->text());


    fournisseurTable.setAdresse(ui->lineEdit_Adresse->text());
    fournisseurTable.setLocalite(ui->lineEdit_Localite->text());
    fournisseurTable.setWilaya(ui->comboBox_Wilaya->currentText());

    fournisseurTable.setNumero_Art_IMPO(ui->lineEdit_Art_IMPO->text());
    fournisseurTable.setNumero_Fiscal(ui->lineEdit_Fiscal->text());
    fournisseurTable.setNumero_RC(ui->lineEdit_RC->text());

    fournisseurTable.setEmail(ui->lineEdit_E_Mail->text());
    fournisseurTable.setTelephone(ui->lineEdit_Telephone->text());
    fournisseurTable.setFax(ui->lineEdit_Fax->text());
    if(fournisseurTable.currentRow() < 0)
        fournisseurTable.insert() ;
    else
        fournisseurTable.update() ;

    close() ;
}

void AddFournisseurs::on_buttonBox_rejected()
{
    close() ;
}
