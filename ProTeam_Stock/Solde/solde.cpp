#include "etat104versement.h"
#include "solde.h"
#include "ui_solde.h"

#include <v_historique.h>

Solde::Solde(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Solde)
{
    ui->setupUi(this);
    historiqueTable.setTable("v_historique");
    historiqueTable.select();
    ui->tableView_etat104->setModel(&historiqueTable);

    ui->tableView_etat104->setEditTriggers(QAbstractItemView::NoEditTriggers);
    on_radioButton_clients_clicked();
    ui->tableView_etat104->hideColumn(0);
    ui->tableView_etat104->hideColumn(1);
    ui->tableView_etat104->hideColumn(2);
    ui->tableView_etat104->hideColumn(3);

}

Solde::~Solde()
{
    delete ui;
}

void Solde::on_radioButton_fournisseurs_clicked()
{
   historiqueTable.setFilter("personneTable == 't_fournisseur'");
   historiqueTable.select();
    calcSum();

}

void Solde::on_radioButton_clients_clicked()
{
    historiqueTable.setFilter("personneTable == 't_client'");
    historiqueTable.select();
    calcSum();
}

void Solde::calcSum()
{
    int sum = 0 ;
    for(int i = 0 ; i < historiqueTable.rowCount() ; i++)
    {
        sum += historiqueTable.record(i).value(v_historique::_08Montant_A_Regler).toInt();
    }
    QString total = QString::number(sum);
    int j = 0 ;
    QString newTotal ;
    for(int i = total.length() -1 ; i >= 0 ; i--)
    {
        j++;
        if( j % 3 == 0)
            newTotal += total.at(i) + ' ';
        else
            newTotal += total.at(i) ;
    }
    total = reverseQString(newTotal);
    ui->label_total->setText(total);
}
QString Solde::reverseQString(QString chaine)
{
    QString inversee;

    for (QString::iterator it = chaine.begin(); it != chaine.end(); ++it)
        inversee.push_front(*it);

    return inversee;
}

void Solde::on_tableView_etat104_doubleClicked(const QModelIndex &index)
{

    Etat104Versement etat104Versement;
    etat104Versement.init(historiqueTable.record(index.row()));

    etat104Versement.exec();
    historiqueTable.select();
    calcSum();
}
