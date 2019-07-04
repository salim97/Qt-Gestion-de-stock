#include "mybackuptousb.h"
#include "ui_mybackuptousb.h"
#include <QDebug>
#include <QStorageInfo>

MyBackupToUSB::MyBackupToUSB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyBackupToUSB)
{
    ui->setupUi(this);
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {

       if(storage.rootPath() == "C:/") continue ;
       ui->listWidget->addItem(storage.rootPath()+" "+  storage.name());
       QFont font = ui->listWidget->item(ui->listWidget->count()-1)->font();
       font.setPixelSize(22);

       ui->listWidget->item(ui->listWidget->count()-1)->setFont(font);


    }

}

MyBackupToUSB::~MyBackupToUSB()
{
    delete ui;
}

void MyBackupToUSB::on_buttonBox_rejected()
{
    close();
}

void MyBackupToUSB::on_buttonBox_accepted()
{
    if(ui->listWidget->currentRow() > -1)
    {
        qDebug() << ui->listWidget->currentItem()->text().split(" ")[0] ;
    }
    close();
}

void MyBackupToUSB::on_listWidget_doubleClicked(const QModelIndex &index)
{
    on_buttonBox_accepted();
}
