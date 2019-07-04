#include "addload.h"
#include "ui_addload.h"

AddLoad::AddLoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLoad)
{
    ui->setupUi(this);
    loadtable.select();

    ui->dateEdit_date->setDate(QDate::currentDate());
}

AddLoad::~AddLoad()
{
    delete ui;
}

void AddLoad::on_buttonBox_rejected()
{
    close();
}

void AddLoad::on_buttonBox_accepted()
{
    loadtable.setDate(ui->dateEdit_date->date().toString("yyyy-MM-dd"));
    loadtable.setLIBELLE(ui->lineEdit_libelle->text());
    loadtable.setDEPENSES(ui->spinBox_depenses->value());
    qDebug() << Q_FUNC_INFO << loadtable.insert();

    close();
}
