#include "chekla.h"
#include "ui_chekla.h"

Chekla::Chekla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chekla)
{
    ui->setupUi(this);
}

Chekla::~Chekla()
{
    delete ui;
}
