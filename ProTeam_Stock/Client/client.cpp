#include "client.h"
#include "ui_client.h"

#include <etat104versement.h>
#include <v_historique.h>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    initAction();

    clientTable = new t_client() ;
    clientTable->select();
    ui->tableView->setModel(clientTable->toModel());

    ui->widget->setTableView(ui->tableView);
//    ui->widget->setModel(clientTable->toModel(), clientTable->columnsList(), clientTable->columnsList());
    ui->widget->setModel(clientTable);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList hiddenlist = getSettings("Client_tableView").toStringList();
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

Client::~Client()
{
    QStringList hiddenlist ;
    for(int i = 0 ; i < ui->tableView->model()->columnCount() ; i++)
        if(ui->tableView->isColumnHidden(i))
            hiddenlist << QString::number(i) ;
    setSettings("Client_tableView", hiddenlist);

    delete ui;
     delete clientTable ;
}

void Client::on_toolButton_new_client_clicked()
{
    AddClient addClient;
    addClient.exec();
    clientTable->select();
}

void Client::on_tableView_doubleClicked(const QModelIndex &index)
{
    clientTable->setCurrentRow(index.row());
//    AddClient addClient(this, clientTable->getid());
//    addClient.exec();
//    clientTable->select();

     logTable.setFilter("idP == "+QString::number(clientTable->getid())
                       +" AND personneTable LIKE '"+clientTable->tableName()+"'");
    logTable.select();
    ui->stackedWidget->setCurrentIndex(1);
}

void Client::initAction()
{

    // init widget action
    QAction  *ajoute, *modifie;
    ajoute = new QAction(ui->toolButton_new_client->text(), this);
    modifie = new QAction("Modifier", this);

    //Icon
    ajoute->setIcon(ui->toolButton_new_client->icon());
    modifie->setIcon(QIcon(":/icon/icon/Edit Column-96.png"));

    // on click
    connect(ajoute, SIGNAL(triggered(bool)), this, SLOT(on_toolButton_new_client_clicked()));
    connect(modifie, &QAction::triggered, [this]() {
            on_tableView_doubleClicked(ui->tableView->currentIndex()); });

    // init table with action
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ajoute);
    ui->tableView->addAction(modifie);

    ui->widget->initAction(ui->tableView);

}

void Client::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 0 )
        ui->toolButton_back->setVisible(false);
    else
         ui->toolButton_back->setVisible(true);
}

void Client::on_toolButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Client::on_tableView_log_doubleClicked(const QModelIndex &index)
{
    Etat104Versement etat104Versement;
    etat104Versement.init(logTable.record(index.row()));

    etat104Versement.exec();
    logTable.select();
}
