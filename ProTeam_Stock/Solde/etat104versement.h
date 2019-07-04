#ifndef ETAT104VERSEMENT_H
#define ETAT104VERSEMENT_H

#include <QDialog>
#include <v_historique.h>

namespace Ui {
class Etat104Versement;
}

class Etat104Versement : public QDialog
{
    Q_OBJECT

public:
    explicit Etat104Versement(QWidget *parent = 0);
    ~Etat104Versement();

    void init(QSqlRecord record);
    int returnVal = 0 ;
private slots:
    void on_pushButton_regle_versement_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::Etat104Versement *ui;
    QSqlRecord record;
};

#endif // ETAT104VERSEMENT_H
