#include "etat104versement.h"
#include "ui_etat104versement.h"

#include <mydatabase.h>

Etat104Versement::Etat104Versement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Etat104Versement)
{
    ui->setupUi(this);
}

Etat104Versement::~Etat104Versement()
{
    delete ui;
}

void Etat104Versement::init(QSqlRecord record)
{
    this->record = record ;
    ui->lineEdit_date->setText(record.value(v_historique::_04dateDocument).toString());
    ui->lineEdit_nom->setText(record.value(v_historique::_05Nom).toString());
    ui->label_total->setText(record.value(v_historique::_06total_general).toString());
    ui->label_montant_a_regle->setText(record.value(v_historique::_08Montant_A_Regler).toString());
    ui->spinBox_client_a_verse->setMaximum(record.value(v_historique::_08Montant_A_Regler).toInt());
}

void Etat104Versement::on_pushButton_regle_versement_clicked()
{

    ui->spinBox_client_a_verse->setValue(ui->label_montant_a_regle->text().toInt());
    on_pushButton_save_clicked();
}

void Etat104Versement::on_pushButton_save_clicked()
{
    returnVal = ui->spinBox_client_a_verse->value() ;
    MyDatabase myDatabase;
    {
        QString query;
        query += "update " + record.value(v_historique::_01tableName).toString();
        query += " set Montant_A_Regler = "+QString::number(
                    record.value(v_historique::_08Montant_A_Regler).toInt() - returnVal );
        query += " where id = "+record.value(v_historique::_00id).toString();
        myDatabase.executeQuery(query);
    }

    {
        QString query;
        query += "update " + record.value(v_historique::_01tableName).toString();
        query += " set Montant_Regle = "+QString::number(
                    record.value(v_historique::_07Montant_Regle).toInt() + returnVal );
        query += " where id = "+record.value(v_historique::_00id).toString();
        myDatabase.executeQuery(query);
    }
    close();
    // todo : IMPORTANT
}
