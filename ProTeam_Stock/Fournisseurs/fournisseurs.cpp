#include "fournisseurs.h"
#include "ui_fournisseurs.h"

#include <etat104versement.h>

Fournisseurs::Fournisseurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fournisseurs)
{
    ui->setupUi(this);
    initAction();

    fournisseurTable = new t_fournisseur() ;
    fournisseurTable->select();
    ui->tableView->setModel(fournisseurTable->toModel());

    ui->widget->setTableView(ui->tableView);
//    ui->widget->setModel(fournisseurTable->toModel(), fournisseurTable->columnsList(), fournisseurTable->columnsList());
    ui->widget->setModel(fournisseurTable);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList hiddenlist = getSettings("Fournisseurs_tableView").toStringList();
    foreach (QString item, hiddenlist) {
        ui->tableView->hideColumn(item.toInt());
    }

    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton_back->setVisible(false);

    logTable.setTable(v_historique::tableName());
    ui->tableView_log->setModel(&logTable);
    ui->tableView_log->hideColumn(0);
    ui->tableView_log->hideColumn(1);
    ui->tableView_log->hideColumn(2);
    ui->tableView_log->hideColumn(3);
    ui->tableView_log->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Fournisseurs::~Fournisseurs()
{
    QStringList hiddenlist ;
    for(int i = 0 ; i < ui->tableView->model()->columnCount() ; i++)
        if(ui->tableView->isColumnHidden(i))
            hiddenlist << QString::number(i) ;
    setSettings("Fournisseurs_tableView", hiddenlist);

    delete ui;
    delete fournisseurTable ;
}

void Fournisseurs::on_toolButton_new_fournisseur_clicked()
{
    AddFournisseurs addFournisseurs;
    addFournisseurs.exec();
    fournisseurTable->select();
}

void Fournisseurs::on_tableView_doubleClicked(const QModelIndex &index)
{
    fournisseurTable->setCurrentRow(index.row());
//    AddFournisseurs addFournisseurs(this, fournisseurTable->getid());
//    addFournisseurs.exec();
//    fournisseurTable->select();
    logTable.setFilter("idP == "+QString::number(fournisseurTable->getid())
                      +" AND personneTable LIKE '"+fournisseurTable->tableName()+"'");
   logTable.select();
   ui->stackedWidget->setCurrentIndex(1);
}

void Fournisseurs::initAction()
{
    // init widget action
    QAction  *ajoute, *modifie;
    ajoute = new QAction(ui->toolButton_new_fournisseur->text(), this);
    modifie = new QAction("Modifier", this);

    //Icon
    ajoute->setIcon(ui->toolButton_new_fournisseur->icon());
    modifie->setIcon(QIcon(":/icon/icon/Edit Column-96.png"));

    // on click
    connect(ajoute, SIGNAL(triggered(bool)), this, SLOT(on_toolButton_new_fournisseur_clicked()));
    connect(modifie, &QAction::triggered, [this]() {
            on_tableView_doubleClicked(ui->tableView->currentIndex()); });

    // init table with action
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ajoute);
    ui->tableView->addAction(modifie);

    ui->widget->initAction(ui->tableView);
}


void Fournisseurs::on_tableView_log_doubleClicked(const QModelIndex &index)
{
    Etat104Versement etat104Versement;
    etat104Versement.init(logTable.record(index.row()));

    etat104Versement.exec();
    logTable.select();
}

void Fournisseurs::on_toolButton_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void Fournisseurs::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 0 )
        ui->toolButton_back->setVisible(false);
    else
         ui->toolButton_back->setVisible(true);
}
