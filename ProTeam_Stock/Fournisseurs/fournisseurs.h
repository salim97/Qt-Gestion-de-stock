#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QWidget>
#include <myparentobject.h>
#include "addfournisseurs.h"
#include "t_fournisseur.h"

namespace Ui {
class Fournisseurs;
}

class Fournisseurs : public QWidget, public MyParentObject
{
    Q_OBJECT

public:
    explicit Fournisseurs(QWidget *parent = 0);
    ~Fournisseurs();

    void initAction();
     void refresh(){ }
private slots:
    void on_toolButton_new_fournisseur_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_log_doubleClicked(const QModelIndex &index);

    void on_toolButton_back_clicked();

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::Fournisseurs *ui;
    t_fournisseur *fournisseurTable;
    QSqlTableModel logTable;
};

#endif // FOURNISSEURS_H
