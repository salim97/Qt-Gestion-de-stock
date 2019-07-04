#include "bondereception.h"
#include "ui_bondereception.h"

#include <QCompleter>
#include <qtrpt.h>
#include "myparentobject.h"


BonDeReception::BonDeReception(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BonDeReception)
{
    ui->setupUi(this);
    setWindowTitle("Bon De Réception");

    tableProduct = new TableProduct(ui->tableWidget, this);
    connect(tableProduct, SIGNAL(montantTotalChanged(int)), this, SLOT(calcSum(int)));

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


    PRINTandVALID = getSettings("PRINTandVALID").toBool() ;

}

BonDeReception::~BonDeReception()
{
    delete ui;
}

void BonDeReception::init(QList<RowProduct> rowProduct, t_historiqueBR *historiqueBR)
{
    tableProduct->rowProducts = rowProduct;
    tableProduct->refresh();
    fournisseurTable.whereid(historiqueBR->getidF());
    ui->comboBox_fournisseur->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate(historiqueBR->getDate()));
    ui->lineEdit_numero_Bon->setText(historiqueBR->getNumero_Bon_De_Commande());

    ui->label_total->setText(QString::number(historiqueBR->getTotal_General()));
    ui->label_montant_a_regle->setText(QString::number(historiqueBR->getMontant_A_Regler()));
    ui->spinBox_client_a_verse->setValue(historiqueBR->getMontant_Regle());

    printer();
}

void BonDeReception::fillGUI()
{
    fournisseurTable.select();
    ui->comboBox_fournisseur->clear();
    ui->comboBox_fournisseur->addItems(fournisseurTable.getColumn(2));
    fournisseurTable.enableAutoComplete(ui->comboBox_fournisseur);
    ui->comboBox_fournisseur->setCurrentIndex(-1);

    stockTable.select();
    ui->comboBox_product->clear();
    ui->comboBox_product->addItems(stockTable.getColumn(2));
    stockTable.enableAutoComplete(ui->comboBox_product);
    ui->comboBox_product->setCurrentIndex(-1);
}

void BonDeReception::on_toolButton_add_fournisseur_clicked()
{
    AddFournisseurs addFournisseurs;
    addFournisseurs.exec();
    fillGUI();
}

void BonDeReception::on_toolButton_add_product_clicked()
{
    AddStock addStock;
    addStock.exec();
    fillGUI();
}

void BonDeReception::on_toolButton_clear_clicked()
{
    ui->comboBox_product->setCurrentIndex(-1);
    ui->spinBox_quantite->setValue(0);
    ui->spinBox_prix->setValue(0);
}

void BonDeReception::on_toolButton_add_to_table_clicked()
{
    if(ui->comboBox_product->currentIndex() <  0)
    {
        qDebug() << "void BonDeReception::on_toolButton_add_to_table_clicked() " << "error" ;
        return;
    }

    stockTable.setCurrentRow(ui->comboBox_product->currentIndex());

//    int row = ui->tableWidget->rowCount()   ;
//    ui->tableWidget->setRowCount(row+1);

//    pitie(row, 0, QString::number(stockTable.getid()));
//    pitie(row, 1, stockTable.getCode());
//    pitie(row, 3, stockTable.getDesignation());
//    pitie(row, 4, ui->spinBox_quantite->text());
//    pitie(row, 5, ui->spinBox_prix->text());
//    pitie(row, 6, QString::number(ui->spinBox_prix->value() * ui->spinBox_quantite->value()));
//    pitie(row, 7, QString::number(stockTable.currentRow()));

    RowProduct row ;
    row.id = stockTable.getid();
    row.code = stockTable.getCode();
    row.designation = stockTable.getDesignation();
    row.quantite = ui->spinBox_quantite->value();
    row.prix = ui->spinBox_prix->value() ;
    row.montant = ui->spinBox_prix->value() * ui->spinBox_quantite->value();
    row._tmp1 = stockTable.currentRow() ;
    tableProduct->add(row);
    on_toolButton_clear_clicked();

//    int sum = 0 ;
//    for(int i = 0 ; i < ui->tableWidget->rowCount() ; i++ )
//    {
//        sum += ui->tableWidget->item(i, 6)->text().toInt() ;
//    }
//    ui->label_total->setText(QString::number(sum));
//    ui->label_montant_a_regle->setText(QString::number(sum));
//    ui->spinBox_client_a_verse->setMaximum(sum);
//    on_toolButton_clear_clicked();
}

void BonDeReception::calcSum(int sum)
{
    ui->label_total->setText(QString::number(sum));
    ui->label_montant_a_regle->setText(QString::number(sum));
    ui->spinBox_client_a_verse->setMaximum(sum*10);
    on_toolButton_clear_clicked();
}

void BonDeReception::pitie(int row, int column, QString data)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(data);
    ui->tableWidget->setItem(row, column, item);
}

void BonDeReception::on_pushButton_annuler_clicked()
{
    close();
}

void BonDeReception::on_comboBox_product_currentIndexChanged(int index)
{
    if(index > -1 )
        ui->toolButton_add_to_table->setEnabled(true);
    else
    {
        ui->toolButton_add_to_table->setEnabled(false);
    }
}

void BonDeReception::on_spinBox_client_a_verse_valueChanged(int arg1)
{
    ui->label_montant_a_regle->setText(QString::number(
                                            ui->label_total->text().toInt() - arg1
                                           ));
}

void BonDeReception::on_pushButton_imprimer_clicked()
{
    printer();
    if(PRINTandVALID)
        on_pushButton_confirmer_clicked();
}

void BonDeReception::on_pushButton_confirmer_clicked()
{
    t_historique historiqueTable ;
    t_historiqueDetails detailTable ;
    t_historiqueBR brTable ;

    historiqueTable.select();
    historiqueTable.setdateDocument(ui->dateEdit->date()) ;
    historiqueTable.settableName(brTable.tableName());
    historiqueTable.insert();

    historiqueTable.select(); // TODO : do wee nedd it ?
    historiqueTable.setCurrentRow(historiqueTable.rowCount()-1);
    int lastID = historiqueTable.getid() ;

    brTable.select();
    brTable.setidH(lastID);
    fournisseurTable.setCurrentRow(ui->comboBox_fournisseur->currentIndex()) ;
    brTable.setidF(fournisseurTable.getid());
    brTable.setNom_Fournisseur(fournisseurTable.getNom());
    brTable.setDate(ui->dateEdit_date_de_commande->date());
    brTable.setNumero_Bon_De_Commande(ui->lineEdit_numero_Bon->text());
    brTable.setTotal_General(ui->label_total->text().toInt());
    brTable.setMontant_A_Regler(ui->label_montant_a_regle->text().toInt());
    brTable.setMontant_Regle(ui->spinBox_client_a_verse->value());
    brTable.insert();

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
        stockTable.setQuantite(stockTable.getQuantite() + detailTable.getQuantite() ) ;
        stockTable.setMontant_Achat( stockTable.getQuantite() * stockTable.getPrix_Achat());

        stockTable.update();
    }

//    detailTable.select();
//    for(int i = 0 ; i < ui->tableWidget->rowCount() ; i++ )
//    {
//        detailTable.setidP(ui->tableWidget->item(i, 0)->text().toInt());
//        detailTable.setidH(lastID);

//        detailTable.setCode(ui->tableWidget->item(i, 1)->text());
//        detailTable.setCategorie(ui->tableWidget->item(i, 2)->text());
//        detailTable.setDesignation(ui->tableWidget->item(i, 3)->text());
//        detailTable.setQuantite(ui->tableWidget->item(i, 4)->text().toInt());
//        detailTable.setPrix(ui->tableWidget->item(i, 5)->text().toInt());
//        detailTable.setMontant(ui->tableWidget->item(i, 6)->text().toInt());

//        detailTable.insert(); // TODO : timing ....
//        stockTable.setCurrentRow(ui->tableWidget->item(i, 7)->text().toInt());
//        stockTable.setQuantite(stockTable.getQuantite() + detailTable.getQuantite() ) ;
//        stockTable.setPrix_Achat( detailTable.getPrix() ) ;
//        stockTable.setMontant_Achat( stockTable.getQuantite() * stockTable.getPrix_Achat());

//        stockTable.update();
//    }


    close();
}

void BonDeReception::printer()
{
    int rows = ui->tableWidget->rowCount();
    int currentRow = 0 ;

    QtRPT *report = new QtRPT(this) ;
//    report->loadReport("c:/Archive/GITHUB/SUDO-DEV/ProTeam_Stock/Templates/BonDeReception.xml");
    report->loadReport(":/Templates/BonDeReception.xml");
    report->recordCount.append(rows);
    connect(report, &QtRPT::setValue, [&](int recNo,
            QString paramName, QVariant &paramValue, const int reportPage){
        if(paramName == "NAME") paramValue = "Bon De Réception" ;
        if(paramName == "COMP_TITLE") paramValue = getSettings("comp_title") ;
        if(paramName == "ADDRESS") paramValue = getSettings("address") ;
        if(paramName == "CAPITAL") paramValue = getSettings("capital_social") ;
        if(paramName == "NRC") paramValue = getSettings("n_rc") ;
        if(paramName == "NAI") paramValue = getSettings("n_ai") ;
        if(paramName == "NIF") paramValue = getSettings("n_if") ;
        if(paramName == "NIS") paramValue = getSettings("n_is") ;

        if(paramName == "DATE") paramValue = QDate::currentDate().toString() ;
        //if(paramName == "NUMBER") paramValue = "TODO ..." ;

        fournisseurTable.setCurrentRow(ui->comboBox_fournisseur->currentIndex()) ;
        if(paramName == "NAME_USER") paramValue = fournisseurTable.getNom() ;
        if(paramName == "ADDRESS_USER") paramValue = fournisseurTable.getAdresse() ;
        if(paramName == "TEL_FAX_USER") paramValue = fournisseurTable.getTelephone() ;
        if(paramName == "NIF_USER") paramValue = fournisseurTable.getNumero_Fiscal() ;
        if(paramName == "NRC_USER") paramValue = fournisseurTable.getNumero_RC() ;
        if(paramName == "NAI_USER") paramValue = fournisseurTable.getNumero_Art_IMPO() ;

        if(paramName == "DATE_BC") paramValue = ui->dateEdit_date_de_commande->text() ;
        if(paramName == "N_BC") paramValue = ui->lineEdit_numero_Bon->text() ;


        if(paramName == "NN") paramValue = recNo+1 ;
        if (paramName == "Code") {
            if (ui->tableWidget->item(recNo,RowProduct::_01code) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_01code)->text();
        }
        if (paramName == "designation") {
            if (ui->tableWidget->item(recNo,RowProduct::_02designation) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_02designation)->text();
        }
        if (paramName == "quantite") {
            if (ui->tableWidget->item(recNo,RowProduct::_03quantite) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_03quantite)->text();
        }
        if (paramName == "prixTTC") {
            if (ui->tableWidget->item(recNo,RowProduct::_04prix) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_04prix)->text();
        }
        if (paramName == "Montant") {
            if (ui->tableWidget->item(recNo,RowProduct::_05montant) == 0) return;
            paramValue = ui->tableWidget->item(recNo,RowProduct::_05montant)->text();
        }

        if(paramName == "MONEY_TOTAL") paramValue = ui->label_total->text() ;


    });
    report->printExec();

}
