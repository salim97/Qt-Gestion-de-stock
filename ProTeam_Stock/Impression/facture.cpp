#include "facture.h"
#include "tableproduct.h"
#include "ui_facture.h"

#include <addstock.h>
#include <addclient.h>
#include <t_historique.h>
#include <t_historiquedetails.h>
#include <t_historiqueFL.h>
#include <qtrpt.h>
#include <t_historiqueFE.h>
#include "myparentobject.h"

Facture::Facture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Facture)
{
    ui->setupUi(this);
    tableProduct = new TableProduct(ui->tableWidget, this);
    connect(tableProduct, SIGNAL(montantTotalChanged(int)), this, SLOT(calcSum(int)));
    setWindowTitle("Facture de Vente");

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

    tva = getSettings("TVA").toDouble() / 100;
    PRINTandVALID = getSettings("PRINTandVALID").toBool() ;

}

Facture::~Facture()
{
    delete ui;
}

void Facture::init(QList<RowProduct> rowProduct, t_historiqueFE *historiqueFE)
{
      qDebug() << Q_FUNC_INFO ;
    tableProduct->rowProducts = rowProduct;
    tableProduct->refresh();
    clientTable.whereid(historiqueFE->getidC());
    ui->comboBox_client->setCurrentIndex(0);
    ui->dateEdit_date_de_commande->setDate(QDate(historiqueFE->getDate()));
    ui->lineEdit_numero_Bon->setText(historiqueFE->getNumero_Bon_De_Commande());

    ui->label_total->setText(QString::number(historiqueFE->getTotal_General()));
    ui->label_montant_a_regle->setText(QString::number(historiqueFE->getMontant_A_Regler()));
    ui->spinBox_client_a_verse->setValue(historiqueFE->getMontant_Regle());

    ui->label_montant_HT->setText(QString::number(historiqueFE->getMontant_H_T()));
    ui->label_montant_TVA->setText(QString::number(historiqueFE->getMontant_T_V_A()));

    printer();
}

void Facture::on_toolButton_clear_clicked()
{
    ui->comboBox_product->setCurrentIndex(-1);
    ui->spinBox_quantite->setValue(0);
}

void Facture::on_toolButton_add_to_table_clicked()
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

void Facture::calcPrice()
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

void Facture::calcSum(int sum)
{
    int prixTotal = sum ;
    ui->label_total->setText(QString::number(prixTotal));
    ui->label_montant_a_regle->setText(QString::number(prixTotal));
    ui->spinBox_client_a_verse->setMaximum(prixTotal*10);

    ui->label_montant_HT->setText(QString::number(sum - (int)(sum*tva)));
//    ui->label_montant_timbre->setText("0");
    ui->label_montant_TVA->setText(QString::number((int)(sum*tva)));
    on_toolButton_clear_clicked();
}

void Facture::on_toolButton_add_product_clicked()
{
    AddStock addStock;
    addStock.exec();
    fillGUI();
}

void Facture::on_toolButton_add_client_clicked()
{
    AddClient addclient;
    addclient.exec();
    fillGUI();
}

void Facture::fillGUI()
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

void Facture::on_comboBox_product_currentIndexChanged(int index)
{
    if(index > -1 )
    {
        stockTable.setCurrentRow(index);
        ui->spinBox_quantite->setMaximum(stockTable.getQuantite());
        ui->spinBox_quantite->setValue(0);
        ui->spinBox_quantite->setMinimum(0);
        ui->toolButton_add_to_table->setEnabled(true);

    }
    else
    {
         ui->spinBox_quantite->setMaximum(0);
         ui->spinBox_quantite->setValue(0);
        ui->spinBox_quantite->setMinimum(0);
         ui->toolButton_add_to_table->setEnabled(false);
    }
}

void Facture::on_comboBox_client_currentIndexChanged(int index)
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

void Facture::on_comboBox_client_type_currentIndexChanged(int index)
{
    calcPrice();
}

void Facture::on_spinBox_client_a_verse_valueChanged(int arg1)
{
    ui->label_montant_a_regle->setText(QString::number(
                                            ui->label_total->text().toInt() - arg1
                                           ));
}

void Facture::on_pushButton_annuler_clicked()
{
    close();
}

void Facture::on_pushButton_confirmer_clicked()
{

    t_historique historiqueTable ;
    t_historiqueDetails detailTable ;
    t_historiqueFE feTable ;

    historiqueTable.select();
    historiqueTable.setdateDocument(ui->dateEdit->date()) ;
    historiqueTable.settableName(feTable.tableName());
    historiqueTable.insert();

    historiqueTable.select(); // TODO : do wee nedd it ?
    historiqueTable.setCurrentRow(historiqueTable.rowCount()-1);
    int lastID = historiqueTable.getid() ;

    feTable.select();
    feTable.setidH(lastID);
    clientTable.setCurrentRow(ui->comboBox_client->currentIndex()) ;
    feTable.setidC(clientTable.getid());
    feTable.setNom_Client(clientTable.getNom());
    feTable.setDate(ui->dateEdit_date_de_commande->date());
    feTable.setNumero_Bon_De_Commande(ui->lineEdit_numero_Bon->text());
    feTable.setTotal_General(ui->label_total->text().toInt());
    feTable.setMontant_A_Regler(ui->label_montant_a_regle->text().toInt());
    feTable.setMontant_Regle(ui->spinBox_client_a_verse->value());
    feTable.setMontant_H_T(ui->label_montant_HT->text().toInt());
    feTable.setMontant_T_V_A(ui->label_montant_TVA->text().toInt());

    feTable.insert();


    QList<RowProduct> rowProducts = tableProduct->rowProducts;
    detailTable.select();
    for(int i = 0 ; i < rowProducts.length() ; i++ )
    {
        detailTable.setidP(rowProducts.at(i).id);
        detailTable.setidH(lastID);

        detailTable.setCode(rowProducts.at(i).code);
        detailTable.setDesignation(rowProducts.at(i).designation);
        detailTable.setQuantite(rowProducts.at(i).quantite);
        detailTable.setPrix(rowProducts.at(i).prix);
        detailTable.setMontant(rowProducts.at(i).montant);

        detailTable.insert(); // TODO : timing ....
        stockTable.setCurrentRow(rowProducts.at(i)._tmp1);
        stockTable.setQuantite(stockTable.getQuantite() - detailTable.getQuantite() ) ;
        stockTable.setMontant_Achat( stockTable.getQuantite() * stockTable.getPrix_Achat());

        stockTable.update();
    }

    close();
}

void Facture::on_pushButton_imprimer_clicked()
{
    printer();

    if(PRINTandVALID)
        on_pushButton_confirmer_clicked();
}

void Facture::printer()
{

    int rows = ui->tableWidget->rowCount();
    int currentRow = 0 ;

    QtRPT *report = new QtRPT(this) ;
//    report->loadReport("c:/Archive/GITHUB/SUDO-DEV/ProTeam_Stock/Templates/BonDeReception.xml");
    report->loadReport(":/Templates/Facture.xml");
    report->recordCount.append(rows);
    connect(report, &QtRPT::setValue, [&](int recNo,
            QString paramName, QVariant &paramValue, const int reportPage){
        if(paramName == "NAME") paramValue = "Facture de Vente" ;

        if(paramName == "COMP_TITLE") paramValue = getSettings("comp_title") ;
        if(paramName == "COMP_ACTIVITY") paramValue = getSettings("activite") ;
        if(paramName == "COMP_ADRESSE") paramValue = getSettings("address") ;
        if(paramName == "COMP_Tel") paramValue = getSettings("telephone") ;
        if(paramName == "COMP_R.C") paramValue = getSettings("n_rc") ;
        if(paramName == "COMP_A.I") paramValue = getSettings("n_ai") ;
        if(paramName == "COMP_FISCAL") paramValue = getSettings("n_if") ;
        if(paramName == "COMP_I.S") paramValue = getSettings("n_is") ;

        if(paramName == "currentDATE") paramValue = QDate::currentDate().toString() ;

        clientTable.setCurrentRow(ui->comboBox_client->currentIndex()) ;
        if(paramName == "NOM") paramValue = clientTable.getNom() ;
        if(paramName == "ADRESSE") paramValue = clientTable.getAdresse() ;
        if(paramName == "LOCALITE") paramValue = clientTable.getLocalite() ;
        if(paramName == "R.C") paramValue = clientTable.getNumero_RC() ;
        if(paramName == "FISCAL") paramValue = clientTable.getNumero_Fiscal() ;
        if(paramName == "A.I") paramValue = clientTable.getNumero_Art_IMPO() ;
        if(paramName == "I.S") paramValue = clientTable.getNumero_IS() ;

        if(paramName == "BDC") paramValue = ui->dateEdit_date_de_commande->text() ;
        if(paramName == "BDL") paramValue = ui->lineEdit_numero_Bon->text() ;


//        if(paramName == "NN") paramValue = recNo+1 ;
        if (paramName == "DESIGNATION") {
            if (ui->tableWidget->item(recNo,RowProduct::_02designation) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_02designation)->text() ;
        }
        if (paramName == "QUANTITE") {
            if (ui->tableWidget->item(recNo,RowProduct::_03quantite) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_03quantite)->text() ;
        }
        if (paramName == "PRIX_UNIT_H_T") {
            if (ui->tableWidget->item(recNo,RowProduct::_04prix) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_04prix)->text() ;
        }
        if (paramName == "MONTANT_UNIT_HT") {
            if (ui->tableWidget->item(recNo,RowProduct::_05montant) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_05montant)->text() ;
       }
        if (paramName == "TVA") {
            paramValue = QString::number(tva*100)+"%";
        }

        if(paramName == "MONTANT_HT" ) paramValue = ui->label_montant_HT->text() ;
        if(paramName == "MONTANT_TVA") paramValue = ui->label_montant_TVA->text() ;
        if(paramName == "MONTANT_TTC") paramValue = ui->label_total->text() ;
        if(paramName == "NET_A_PAYER") paramValue = ui->label_total->text() ;

        if(paramName == "MONEY_LETTERS") {
//            MyParentObject khra;
//            paramValue = khra.spellLetter(ui->label_total->text()) + " DA";
//            qDebug() << khra.spellLetter(ui->label_total->text()) ;
            paramValue = MyParentObject::result(ui->label_total->text().toInt())+" Dinar";

        }

    });

    report->printExec();
}




