#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QWidget>
#include <myparentobject.h>
#include <t_historique.h>
#include <t_historiqueFE.h>
#include <t_historiqueFL.h>
#include <t_historiquebr.h>
#include <t_historiquedetails.h>
#include "bondereception.h"
#include "facture.h"
#include <bondelivraison.h>
#include <facturedavoir.h>

namespace Ui {
class Historique;
}

class Historique : public QWidget, public MyParentObject
{
    Q_OBJECT

public:
    explicit Historique(QWidget *parent = 0);
    ~Historique();

    void initHistoriqueView();
    void refresh(){ }

private slots:
    void on_tableView_historique_clicked(const QModelIndex &index);

    void on_tableView_extra_clicked(const QModelIndex &index);

    void on_radioButton_BR_clicked() { initHistoriqueView(); }

    void on_radioButton_FL_clicked() { initHistoriqueView(); }

    void on_radioButton_FR_clicked() { initHistoriqueView(); }

    void on_toolButton_print_clicked();

private:
    Ui::Historique *ui;
    QSqlQueryModel model;
    t_historique *historiqueTable;
    t_historique *historiqueTable2;
    t_historiqueDetails *historiqueDetailsTable;
    t_historiqueBR *historiqueBRTable;
    t_historiqueFE *historiqueFETable;
    t_historiqueFL *historiqueFLTable ;
};

#endif // HISTORIQUE_H
