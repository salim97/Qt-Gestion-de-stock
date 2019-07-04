#ifndef ADDFOURNISSEURS_H
#define ADDFOURNISSEURS_H

#include <QDialog>
#include "t_fournisseur.h"

namespace Ui {
class AddFournisseurs;
}

class AddFournisseurs : public QDialog
{
    Q_OBJECT

public:
    explicit AddFournisseurs(QWidget *parent = 0, int id = -1);
    ~AddFournisseurs();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddFournisseurs *ui;
    t_fournisseur fournisseurTable;
};

#endif // ADDFOURNISSEURS_H
