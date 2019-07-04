#include "facturedavoir.h"
#include "ui_facturedavoir.h"

FactureDAvoir::FactureDAvoir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactureDAvoir)
{
    ui->setupUi(this);
}

FactureDAvoir::~FactureDAvoir()
{
    delete ui;
}
