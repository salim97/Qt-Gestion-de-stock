#include "addload.h"
#include "loads.h"
#include "ui_loads.h"

Loads::Loads(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loads)
{
    ui->setupUi(this);
    initAction();

    loadsTable = new t_loads();
    ui->tableView->setModel(loadsTable->toModel());
    ui->widget->setModel(loadsTable);
    ui->widget->setTableView(ui->tableView);

    loadsTable->tableViewConfigVisibleColumns(ui->tableView);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Loads::~Loads()
{
    delete ui;
    delete loadsTable ;
}

void Loads::on_toolButton_new_charge_clicked()
{
    AddLoad ad;
    ad.exec();
    loadsTable->select();
}

void Loads::initAction()
{

    // init widget action
    QAction  *ajoute, *modifie;
    ajoute = new QAction(ui->toolButton_new_charge->text(), this);
    modifie = new QAction("Modifier", this);

    //Icon
    ajoute->setIcon(ui->toolButton_new_charge->icon());
    modifie->setIcon(QIcon(":/icon/icon/Edit Column-96.png"));

    // on click
    connect(ajoute, SIGNAL(triggered(bool)), this, SLOT(on_toolButton_new_charge_clicked()));
    connect(modifie, &QAction::triggered, [this]() {
            on_tableView_doubleClicked(ui->tableView->currentIndex()); });

    // init table with action
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ajoute);
    ui->tableView->addAction(modifie);

    ui->widget->initAction(ui->tableView);

}

void Loads::on_tableView_doubleClicked(const QModelIndex &index)
{

}
