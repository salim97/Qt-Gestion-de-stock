#include "bondelivraison.h"
#include "ui_bondelivraison.h"

#include <addclient.h>
#include <addstock.h>
#include <myparentobject.h>
#include <qtrpt.h>
#include <t_historique.h>
#include <t_historiqueFE.h>
#include <t_historiqueFL.h>
#include <t_historiquedetails.h>

BonDeLivraison::BonDeLivraison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BonDeLivraison)
{
    ui->setupUi(this);
    tableProduct = new TableProduct(ui->tableWidget, this);
    connect(tableProduct, SIGNAL(montantTotalChanged(int)), this, SLOT(calcSum(int)));

    setWindowTitle("Bon De Livraison");

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_date_de_commande->setDate(QDate::currentDate());
    ui->comboBox_product->setFocus();
    ui->pushButton_annuler->setDefault(false);
    ui->pushButton_annuler->setAutoDefault(false);

    ui->pushButton_confirmer->setDefault(false);
    ui->pushButton_confirmer->setAutoDefault(false);

    ui->pushButton_imprimer->setDefault(false);
    ui->pushButton_imprimer->setAutoDefault(false);

    fillGUI();
    ui->toolButton_add_to_table->setEnabled(false);

    ui->tableWidget->setColumnHidden(0, true);
    ui->tableWidget->setColumnHidden(7, true);

    PRINTandVALID = getSettings("PRINTandVALID").toBool() ;

}

BonDeLivraison::~BonDeLivraison()
{
    delete ui;
}

void BonDeLivraison::init(QList<RowProduct> rowProduct, t_historiqueFL *historiqueFL)
{
    tableProduct->rowProducts = rowProduct;
    tableProduct->refresh();
    clientTable.whereid(historiqueFL->getidC());
    ui->comboBox_client->setCurrentIndex(0);
    ui->dateEdit_date_de_commande->setDate(QDate(historiqueFL->getDate()));
    ui->lineEdit_numero_Bon->setText(historiqueFL->getNumero_Bon_De_Commande());

    ui->label_total->setText(QString::number(historiqueFL->getTotal_General()));
    ui->label_montant_a_regle->setText(QString::number(historiqueFL->getMontant_A_Regler()));
    ui->spinBox_client_a_verse->setValue(historiqueFL->getMontant_Regle());


    printer();
}

void BonDeLivraison::on_toolButton_add_to_table_clicked()
{
    if(ui->comboBox_client->currentIndex() < 0)
    {
        MyParentObject myparentobject;
        myparentobject.msgCritical("error", "Sélectionner un client");
        return ;
    }
    if(ui->comboBox_product->currentIndex() <  0)
    {
        qDebug() << "void BonDeReception::on_toolButton_add_to_table_clicked() " << "error" ;
        return;
    }

    stockTable.setCurrentRow(ui->comboBox_product->currentIndex());


    RowProduct row ;
    row.id = stockTable.getid();
    row.code = stockTable.getCode();
    row.designation = stockTable.getDesignation();
    row.quantite = ui->spinBox_quantite->value();
    row.prix = 0 ;
    row.montant = 0 ;
    row._tmp1 = stockTable.currentRow() ;

    tableProduct->add(row);
    calcPrice();
    on_toolButton_clear_clicked();

}

void BonDeLivraison::calcPrice()
{
    qDebug() << Q_FUNC_INFO ;
    rowProduct = tableProduct->rowProducts ;
    int prix ;
    for(int i = 0 ; i < rowProduct.length() ; i++ )
    {
        stockTable.setCurrentRow(rowProduct[i]._tmp1);
        if(ui->comboBox_client_type->currentText() == "Gros")      prix = stockTable.getPrix_Vente_Gros();
        if(ui->comboBox_client_type->currentText() == "Demi Gros") prix = stockTable.getPrix_Vente_Demi_Gros();
        if(ui->comboBox_client_type->currentText() == "Detail")    prix = stockTable.getPrix_Vente_Detail();

        rowProduct[i].prix = prix ;
        rowProduct[i].calc();
    }
    tableProduct->refresh(rowProduct);
}

void BonDeLivraison::calcSum(int sum)
{
    int prixTotal = sum ;
    ui->label_total->setText(QString::number(prixTotal));
    ui->label_montant_a_regle->setText(QString::number(prixTotal));
    ui->spinBox_client_a_verse->setMaximum(prixTotal*10);

    on_toolButton_clear_clicked();
}

void BonDeLivraison::on_toolButton_clear_clicked()
{
    ui->comboBox_product->setCurrentIndex(-1);
    ui->spinBox_quantite->setValue(0);
}

void BonDeLivraison::on_toolButton_add_product_clicked()
{
    AddStock addStock;
    addStock.exec();
    fillGUI();
}

void BonDeLivraison::on_toolButton_add_client_clicked()
{
    AddClient addclient;
    addclient.exec();
    fillGUI();
}

void BonDeLivraison::fillGUI()
{
    clientTable.select();
    ui->comboBox_client->clear();
    ui->comboBox_client->addItems(clientTable.getColumn(2));
    clientTable.enableAutoComplete(ui->comboBox_client);
    ui->comboBox_client->setCurrentIndex(-1);

    stockTable.select();
    ui->comboBox_product->clear();
    ui->comboBox_product->addItems(stockTable.getColumn(2));
    stockTable.enableAutoComplete(ui->comboBox_product);
    ui->comboBox_product->setCurrentIndex(-1);
}

void BonDeLivraison::pitie(int row, int column, QString data)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(data);
    ui->tableWidget->setItem(row, column, item);
}

void BonDeLivraison::on_comboBox_product_currentIndexChanged(int index)
{
    if(index > -1 )
    {
        stockTable.setCurrentRow(index);
        ui->spinBox_quantite->setMaximum(stockTable.getQuantite());
        ui->toolButton_add_to_table->setEnabled(true);
    }
    else
    {
        ui->toolButton_add_to_table->setEnabled(false);
    }
}

void BonDeLivraison::on_comboBox_client_currentIndexChanged(int index)
{
    if(index > -1 )
    {
        ui->comboBox_client_type->setVisible(true);
        ui->label_client_type->setVisible(true);
        clientTable.setCurrentRow(index);
        if(clientTable.getType() == "Detail")
            ui->comboBox_client_type->setCurrentIndex(0);

        if(clientTable.getType() == "Demi Gros")
            ui->comboBox_client_type->setCurrentIndex(1);

        if(clientTable.getType() == "Gros")
            ui->comboBox_client_type->setCurrentIndex(2);

    }
    else
    {
        ui->comboBox_client_type->setVisible(false);
        ui->label_client_type->setVisible(false);
    }

}

void BonDeLivraison::on_comboBox_client_type_currentIndexChanged(int index)
{
     calcPrice();
}

void BonDeLivraison::on_spinBox_client_a_verse_valueChanged(int arg1)
{
    ui->label_montant_a_regle->setText(QString::number(
                                            ui->label_total->text().toInt() - arg1
                                           ));
}

void BonDeLivraison::on_pushButton_annuler_clicked()
{
    close();
}

void BonDeLivraison::on_pushButton_confirmer_clicked()
{
    t_historique historiqueTable ;
    t_historiqueDetails detailTable ;
    t_historiqueFL flTable ;

    historiqueTable.select();
    historiqueTable.setdateDocument(ui->dateEdit->date()) ;
    historiqueTable.settableName(flTable.tableName());
    historiqueTable.insert();

    historiqueTable.select(); // TODO : do wee nedd it ?
    historiqueTable.setCurrentRow(historiqueTable.rowCount()-1);
    int lastID = historiqueTable.getid() ;

    flTable.select();
    flTable.setidH(lastID);
    clientTable.setCurrentRow(ui->comboBox_client->currentIndex()) ;
    flTable.setidC(clientTable.getid());
    flTable.setNom_Client(clientTable.getNom());
    flTable.setDate(ui->dateEdit_date_de_commande->date());
    flTable.setNumero_Bon_De_Commande(ui->lineEdit_numero_Bon->text());
    flTable.setTotal_General(ui->label_total->text().toInt());
    flTable.setMontant_A_Regler(ui->label_montant_a_regle->text().toInt());
    flTable.setMontant_Regle(ui->spinBox_client_a_verse->value());
//    feTable.setMontant_H_T(ui->label_montant_HT->text().toInt());
//    feTable.setMontant_Timbre(ui->label_montant_timbre->text().toInt());
//    feTable.setMontant_T_V_A(ui->label_montant_TVA->text().toInt());

    flTable.insert();

    detailTable.select();
    for(int i = 0 ; i < ui->tableWidget->rowCount() ; i++ )
    {
        detailTable.setidP(ui->tableWidget->item(i, 0)->text().toInt());
        detailTable.setidH(lastID);

        detailTable.setCode(ui->tableWidget->item(i, 1)->text());
        detailTable.setDesignation(ui->tableWidget->item(i, 3)->text());
        detailTable.setQuantite(ui->tableWidget->item(i, 4)->text().toInt());
        detailTable.setPrix(ui->tableWidget->item(i, 5)->text().toInt());
        detailTable.setMontant(ui->tableWidget->item(i, 6)->text().toInt());

        detailTable.insert(); // TODO : timing ....
        stockTable.setCurrentRow(ui->tableWidget->item(i, 7)->text().toInt());
        stockTable.setQuantite(stockTable.getQuantite() - detailTable.getQuantite() ) ;
        stockTable.setMontant_Achat( stockTable.getQuantite() * stockTable.getPrix_Achat());

        stockTable.update();
    }


    close();
}

void BonDeLivraison::on_pushButton_imprimer_clicked()
{
    printer();

    if(PRINTandVALID)
        on_pushButton_confirmer_clicked();
}

void BonDeLivraison::printer()
{
    int rows = ui->tableWidget->rowCount();
    int currentRow = 0 ;

    QtRPT *report = new QtRPT(this) ;
//    report->loadReport("c:/Archive/GITHUB/SUDO-DEV/ProTeam_Stock/Templates/BonDeReception.xml");
    report->loadReport(":/Templates/BonDeLivraison.xml");
    report->recordCount.append(rows);
    connect(report, &QtRPT::setValue, [&](int recNo,
            QString paramName, QVariant &paramValue, const int reportPage){
        if(paramName == "NAME") paramValue = "Bon De Livraison" ;

        if(paramName == "COMP_TITLE") paramValue = getSettings("comp_title") ;
        if(paramName == "ADDRESS") paramValue = getSettings("address") ;
        if(paramName == "CAPITAL") paramValue = getSettings("capital_social") ;
        if(paramName == "NRC") paramValue = getSettings("n_rc") ;
        if(paramName == "NAI") paramValue = getSettings("n_ai") ;
        if(paramName == "NIF") paramValue = getSettings("n_if") ;
        if(paramName == "NIS") paramValue = getSettings("n_is") ;

        if(paramName == "DATE") paramValue = QDate::currentDate().toString() ;
        if(paramName == "NUMBER") paramValue = "TODO ..." ;

        clientTable.setCurrentRow(ui->comboBox_client->currentIndex()) ;
        if(paramName == "NAME_USER") paramValue = clientTable.getNom() ;
        if(paramName == "ADDRESS_USER") paramValue = clientTable.getAdresse() ;
        if(paramName == "TEL_FAX_USER") paramValue = clientTable.getTelephone() ;
        if(paramName == "NIF_USER") paramValue = clientTable.getNumero_Fiscal() ;
        if(paramName == "NRC_USER") paramValue = clientTable.getNumero_RC() ;
        if(paramName == "NAI_USER") paramValue = clientTable.getNumero_Art_IMPO() ;

        if(paramName == "DATE_BC") paramValue = ui->dateEdit_date_de_commande->text() ;
        if(paramName == "N_BC") paramValue = ui->lineEdit_numero_Bon->text() ;


        if(paramName == "NN") paramValue = recNo+1 ;
        if (paramName == "Code") {
            if (ui->tableWidget->item(recNo,1) == 0) return;
            paramValue = ui->tableWidget->item(recNo,1)->text();
        }
        if (paramName == "designation") {
            if (ui->tableWidget->item(recNo,3) == 0) return;
            paramValue = ui->tableWidget->item(recNo,3)->text();
        }
        if (paramName == "quantite") {
            if (ui->tableWidget->item(recNo,4) == 0) return;
            paramValue = ui->tableWidget->item(recNo,4)->text();
        }
        if (paramName == "prixTTC") {
            if (ui->tableWidget->item(recNo,5) == 0) return;
            paramValue = ui->tableWidget->item(recNo,5)->text();
        }
        if (paramName == "Montant") {
            if (ui->tableWidget->item(recNo,6) == 0) return;
            paramValue = ui->tableWidget->item(recNo,6)->text();
        }

        if(paramName == "MONEY_TOTAL") paramValue = ui->label_total->text() ;
//        if(paramName == "MONEY_HT") paramValue = ui->label_montant_HT->text() ;
//        if(paramName == "MONEY_TVA") paramValue = ui->label_montant_TVA->text() ;
//        if(paramName == "MONEY_TIMBRE") paramValue = ui->label_montant_timbre->text() ;

        if(paramName == "MONEY_LETTERS") {
            MyParentObject khra;
            paramValue = khra.spellLetter(ui->label_total->text()) + " DA";
            qDebug() << khra.spellLetter(ui->label_total->text()) ;
        }

    });
    report->printExec();
}
