#include "historique.h"
#include "ui_historique.h"

Historique::Historique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Historique)
{
    ui->setupUi(this);

    historiqueTable = new t_historique;
    historiqueTable2 = new t_historique;
    historiqueDetailsTable = new t_historiqueDetails;
    historiqueBRTable = new t_historiqueBR ;
    historiqueFETable = new t_historiqueFE;
    historiqueFLTable = new t_historiqueFL;

    initHistoriqueView();

    QList<int> currentSizes;

    currentSizes = ui->splitter->sizes() ;
    currentSizes[0] = getSettings("splitterX").toInt() ;
    currentSizes[1] = getSettings("splitterY").toInt() ;
    ui->splitter->setSizes(currentSizes);

    currentSizes[0] = getSettings("splitter2X").toInt() ;
    currentSizes[1] = getSettings("splitter2Y").toInt() ;
    ui->splitter_2->setSizes(currentSizes);

    currentSizes[0] = getSettings("splitter3X").toInt() ;
    currentSizes[1] = getSettings("splitter3Y").toInt() ;
    ui->splitter_3->setSizes(currentSizes);
    ui->toolButton_print->setDisabled(true);
    ui->tableView_detail->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_extra->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_historique->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

Historique::~Historique()
{
    QList<int> currentSizes;
    currentSizes = ui->splitter->sizes() ;
    setSettings("splitterX", currentSizes[0]);
    setSettings("splitterY", currentSizes[1]);

    currentSizes = ui->splitter_2->sizes() ;
    setSettings("splitter2X", currentSizes[0]);
    setSettings("splitter2Y", currentSizes[1]);

    currentSizes = ui->splitter_3->sizes() ;
    setSettings("splitter3X", currentSizes[0]);
    setSettings("splitter3Y", currentSizes[1]);

    delete ui;
    delete historiqueTable;
    delete historiqueTable2;
    delete historiqueDetailsTable;
    delete historiqueBRTable;
    delete historiqueFETable;
    delete historiqueFLTable;
}

void Historique::initHistoriqueView()
{
    QString tableName ;
    if(ui->radioButton_BR->isChecked())
        tableName = historiqueBRTable->tableName() ;
    if(ui->radioButton_FL->isChecked())
        tableName = historiqueFLTable->tableName() ;
    if(ui->radioButton_FR->isChecked())
        tableName = historiqueFETable->tableName() ;

    model.setQuery("SELECT DISTINCT dateDocument FROM "+historiqueTable->tableName()
                   +" WHERE tableName LIKE '"+tableName+"' ORDER BY dateDocument DESC");
    ui->tableView_historique->setModel(&model);

    ui->tableView_detail->setModel(nullptr);
    ui->tableView_extra->setModel(nullptr);
    ui->label_extra->setText("...");
    ui->toolButton_print->setDisabled(true);
}

void Historique::on_tableView_historique_clicked(const QModelIndex &index)
{
//    historiqueTable->setCurrentRow(index.row());
    QString dateDocument = model.record(index.row()).value("dateDocument").toDate().toString("yyyy-MM-dd") ;
    QString tableName;
    if(ui->radioButton_BR->isChecked())
        tableName = historiqueBRTable->tableName();

    if(ui->radioButton_FL->isChecked())
        tableName = historiqueFLTable->tableName();

    if(ui->radioButton_FR->isChecked())
        tableName = historiqueFETable->tableName();

    historiqueTable2->where("tableName LIKE '"+tableName
                            +"' AND dateDocument LIKE '"+dateDocument+"'") ;
    historiqueTable2->select();
    ui->tableView_extra->setModel(historiqueTable2->toModel());

    ui->tableView_extra->hideColumn(1);
    ui->tableView_extra->hideColumn(2);
    ui->tableView_detail->setModel(nullptr);
    ui->label_extra->setText("...");
}

void Historique::on_tableView_extra_clicked(const QModelIndex &index)
{
    historiqueTable2->setCurrentRow(index.row());

    if(historiqueTable2->gettableName() == historiqueBRTable->tableName())
    {
        historiqueDetailsTable->where("idH == "+QString::number(historiqueTable2->getid()));
        ui->tableView_detail->setModel(historiqueDetailsTable->toModel());

        historiqueBRTable->where("idH == "+QString::number(historiqueTable2->getid()));
        QString html ;
        html += "<p>Nom Fournisseur: <span style=\" font-size:12pt;\">"+historiqueBRTable->getNom_Fournisseur()+"</span></p>" ;
        html += "<p>Numero Bon De Commande: <span style=\" font-size:12pt;\">"+historiqueBRTable->getNumero_Bon_De_Commande()+"</span></p>" ;
        html += "<p>Date Bon De Commande: <span style=\" font-size:12pt;\">"+historiqueBRTable->getDate().toString()+"</span></p>" ;
        html += "<p>Total General: <span style=\" font-size:12pt;\">"+QString::number(historiqueBRTable->getTotal_General())+"</span></p>" ;
        html += "<p>Montant A Regler: <span style=\" font-size:12pt;\">"+QString::number(historiqueBRTable->getMontant_A_Regler())+"</span></p>" ;
        html += "<p>Montant Regle: <span style=\" font-size:12pt;\">"+QString::number(historiqueBRTable->getMontant_Regle()) +"</span></p>" ;

        ui->label_extra->setText(html);

    }

    if(historiqueTable2->gettableName() == historiqueFETable->tableName())
    {
        historiqueDetailsTable->where("idH == "+QString::number(historiqueTable2->getid()));
        ui->tableView_detail->setModel(historiqueDetailsTable->toModel());

        historiqueFETable->where("idH == "+QString::number(historiqueTable2->getid()));
        QString text ;
        text += "Nom Client: " + historiqueFETable->getNom_Client() + "\n" ;
        text += "Numero Bon De Commande: " + historiqueFETable->getNumero_Bon_De_Commande() + "\n" ;
        text += "Date Bon De Commande: " + historiqueFETable->getDate().toString() + "\n" ;
        text += "Total H.T: " + QString::number(historiqueFETable->getMontant_H_T()) + "\n" ;
        text += "Total T.V.A: " + QString::number(historiqueFETable->getMontant_T_V_A()) + "\n" ;
        text += "Total Timbre: " + QString::number(historiqueFETable->getMontant_Timbre()) + "\n" ;
        text += "Total General: " + QString::number(historiqueFETable->getTotal_General()) + "\n" ;
        text += "Montant A Regler: " + QString::number(historiqueFETable->getMontant_A_Regler()) + "\n" ;
        text += "Montant Regle: " + QString::number(historiqueFETable->getMontant_Regle()) + "\n" ;
        ui->label_extra->setText(text);
    }

    if(historiqueTable2->gettableName() == historiqueFLTable->tableName())
    {
        historiqueDetailsTable->where("idH == "+QString::number(historiqueTable2->getid()));
        ui->tableView_detail->setModel(historiqueDetailsTable->toModel());

        historiqueFLTable->where("idH == "+QString::number(historiqueTable2->getid()));
        QString text ;
        text += "Nom Client: " + historiqueFLTable->getNom_Client() + "\n" ;
        text += "Numero Bon De Commande: " + historiqueFLTable->getNumero_Bon_De_Commande() + "\n" ;
        text += "Date Bon De Commande: " + historiqueFLTable->getDate().toString() + "\n" ;
        text += "Total General: " + QString::number(historiqueFLTable->getTotal_General()) + "\n" ;
        text += "Montant A Regler: " + QString::number(historiqueFLTable->getMontant_A_Regler()) + "\n" ;
        text += "Montant Regle: " + QString::number(historiqueFLTable->getMontant_Regle()) + "\n" ;
        ui->label_extra->setText(text);
    }


    ui->tableView_detail->hideColumn(0);
    ui->tableView_detail->hideColumn(1);
    ui->tableView_detail->hideColumn(2);
    ui->tableView_detail->hideColumn(2);
    ui->toolButton_print->setEnabled(true);

}

void Historique::on_toolButton_print_clicked()
{
    QList<RowProduct> rowProducts ;
    for(int i = 0 ; i < historiqueDetailsTable->rowCount() ; i++ )
    {
        historiqueDetailsTable->setCurrentRow(i);

        RowProduct tmp ;
        tmp.code = historiqueDetailsTable->getCode();
        tmp.designation = historiqueDetailsTable->getDesignation();
        tmp.quantite = historiqueDetailsTable->getQuantite();
        tmp.prix = historiqueDetailsTable->getPrix();
        tmp.montant = historiqueDetailsTable->getMontant();

        rowProducts.append(tmp);
    }

    if(ui->radioButton_BR->isChecked())
    {
        BonDeReception bonDeLivraison;
        bonDeLivraison.init(rowProducts, historiqueBRTable);
    }

    if(ui->radioButton_FL->isChecked())
    {
        BonDeLivraison bonDeLivraison;
        bonDeLivraison.init(rowProducts, historiqueFLTable);
    }

    if(ui->radioButton_FR->isChecked())
    {
        Facture facture;
        facture.init(rowProducts, historiqueFETable);
    }
}

