#include "bondecommande.h"
#include "ui_bondecommande.h"

BonDeCommande::BonDeCommande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BonDeCommande)
{
    ui->setupUi(this);
}

BonDeCommande::~BonDeCommande()
{
    delete ui;
}
