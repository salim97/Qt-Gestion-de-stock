#include "addclient.h"
#include "ui_addclient.h"

AddClient::AddClient(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Client");

    clientTable.setCurrentRow(-1);
    if(id > -1)
    {
        clientTable.where("id == "+QString::number(id)) ;

        ui->lineEdit_Code_2->setText(clientTable.getCode());
        ui->lineEdit_Nom_2->setText(clientTable.getNom());

        ui->lineEdit_Adresse->setText(clientTable.getAdresse());
        ui->lineEdit_Localite->setText(clientTable.getLocalite());
        for(int i = 0 ; i  < ui->comboBox_Wilaya->count() ; i++ )
            if(ui->comboBox_Wilaya->itemText(i) == clientTable.getWilaya())
                ui->comboBox_Wilaya->setCurrentIndex(i);

        if(clientTable.getType() == "Detail")    ui->comboBox_type->setCurrentIndex(0);
        if(clientTable.getType() == "Demi Gros") ui->comboBox_type->setCurrentIndex(1);
        if(clientTable.getType() == "Gros")      ui->comboBox_type->setCurrentIndex(2);


        ui->lineEdit_Art_IMPO->setText(clientTable.getNumero_Art_IMPO());
        ui->lineEdit_Fiscal->setText(clientTable.getNumero_Fiscal());
        ui->lineEdit_RC->setText(clientTable.getNumero_RC());

        ui->lineEdit_E_Mail->setText(clientTable.getEmail());
        ui->lineEdit_Telephone->setText(clientTable.getTelephone());

    }
}

AddClient::~AddClient()
{
    delete ui;
}

void AddClient::on_buttonBox_accepted()
{
    clientTable.setCode(ui->lineEdit_Code_2->text());
    clientTable.setNom(ui->lineEdit_Nom_2->text());


    clientTable.setAdresse(ui->lineEdit_Adresse->text());
    clientTable.setLocalite(ui->lineEdit_Localite->text());
    clientTable.setWilaya(ui->comboBox_Wilaya->currentText());

    clientTable.setNumero_Art_IMPO(ui->lineEdit_Art_IMPO->text());
    clientTable.setNumero_Fiscal(ui->lineEdit_Fiscal->text());
    clientTable.setNumero_RC(ui->lineEdit_RC->text());

    clientTable.setEmail(ui->lineEdit_E_Mail->text());
    clientTable.setTelephone(ui->lineEdit_Telephone->text());
    clientTable.setType(ui->comboBox_type->currentText());

    if(clientTable.currentRow() < 0)
        clientTable.insert() ;
    else
        clientTable.update() ;

    close();
}

void AddClient::on_buttonBox_rejected()
{
    close();
}
