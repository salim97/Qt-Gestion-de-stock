#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <rapportquotidien.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ProTeam Stock");
    historique = new Historique(this) ;
    client = new Client(this) ;
    stock = new Stock(this);
    fournisseurs = new Fournisseurs(this) ;
    loads = new Loads(this);
    solde = new Solde(this);

    ui->tabWidget->addTab(historique, QIcon(":/Assets/Images/icons/history.svg"), "Historique");
    ui->tabWidget->addTab(solde, QIcon(":/Assets/Images/icons/state-104.svg"), "Solde");
    ui->tabWidget->addTab(stock, QIcon(":/Assets/Images/icons/stock.svg"), "Stock");
    ui->tabWidget->addTab(client, QIcon(":/Assets/Images/icons/client.svg"), "Client");
    ui->tabWidget->addTab(fournisseurs, QIcon(":/Assets/Images/icons/supplier.svg"), "Fournisseurs");
    ui->tabWidget->addTab(loads, "Les Charges");



    bool ok = true ;
    int tmp = getSettings("ui->tabWidget->currentIndex()").toInt(&ok);
    if(!ok) tmp = 0 ;
    ui->tabWidget->setCurrentIndex(tmp);

//    modelEtat104.setQuery(
//"SELECT Date_Bon_De_Commande, Nom_Fournisseur, Total_General, Montant_Regle, Montant_A_Regler from t_historiqueBR ");


    ui->toolButton_facture_proforma->setVisible(false);

}

MainWindow::~MainWindow()
{
    setSettings("ui->tabWidget->currentIndex()", ui->tabWidget->currentIndex());

    delete ui;
}
/*--------------------*/
void MainWindow::on_toolButton_bonDeReception_clicked()
{
    BonDeReception bonDeReception;
    bonDeReception.exec();
}

void MainWindow::on_toolButton_facture_clicked()
{
    Facture facture;
    facture.exec();
}

void MainWindow::on_toolButton_facture_d_avoir_clicked()
{
    FactureDAvoir factureDAvoir;
    factureDAvoir.exec();
}

void MainWindow::on_toolButton_bonDeCommande_clicked()
{

}

void MainWindow::on_toolButton_bonDeLivraison_clicked()
{
    BonDeLivraison bonDeLivraison ;
    bonDeLivraison.exec();
}
/*---------------------*/


void MainWindow::on_actionParametres_triggered()
{
    Settings settings;
    settings.exec();
}

void MainWindow::on_actionBackupToUSB_triggered()
{
    MyBackupToUSB myBackupToUSB;
    myBackupToUSB.exec();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2 ) historique->refresh();
    if(index == 3 ) solde->refresh();
    if(index == 4 ) stock->refresh();
    if(index == 5 ) client->refresh();
    if(index == 6 ) fournisseurs->refresh();
    if(index == 7 ) loads->refresh();


}

void MainWindow::on_actionRapport_quotidien_triggered()
{
    RapportQuotidien rapportQuotidien ;
    rapportQuotidien.exec();
}
