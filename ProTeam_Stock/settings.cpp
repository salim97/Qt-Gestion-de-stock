#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Paramètres");

    ui->lineEdit_ADRESSE->setText(getSettings("address").toString());
    ui->lineEdit_ACTIVITE->setText(getSettings("activite").toString());
    ui->lineEdit_comp_title->setText(getSettings("comp_title").toString());
    ui->lineEdit_mail->setText(getSettings("mail").toString());
    ui->lineEdit_telephone->setText(getSettings("telephone").toString());
    ui->lineEdit_n_ai->setText(getSettings("n_ai").toString());
    ui->lineEdit_n_if->setText(getSettings("n_fi").toString());
    ui->lineEdit_n_is->setText(getSettings("n_is").toString());
    ui->lineEdit_n_rc->setText(getSettings("n_rc").toString());
    ui->spinBox_TVA->setValue(getSettings("TVA").toInt());
    ui->checkBox_print_and_valid->setChecked(getSettings("PRINTandVALID").toBool());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    setSettings("address", ui->lineEdit_ADRESSE->text());
    setSettings("activite", ui->lineEdit_ACTIVITE->text());
    setSettings("comp_title", ui->lineEdit_comp_title->text());
    setSettings("mail", ui->lineEdit_mail->text());
    setSettings("telephone", ui->lineEdit_telephone->text());
    setSettings("n_ai", ui->lineEdit_n_ai->text());
    setSettings("n_fi", ui->lineEdit_n_if->text());
    setSettings("n_is", ui->lineEdit_n_is->text());
    setSettings("n_rc", ui->lineEdit_n_rc->text());
    setSettings("TVA", ui->spinBox_TVA->value());
    setSettings("PRINTandVALID", ui->checkBox_print_and_valid->isChecked());
    close() ;
}

void Settings::on_buttonBox_rejected()
{
    close();
}
