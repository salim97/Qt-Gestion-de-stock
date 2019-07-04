#ifndef BONDECOMMANDE_H
#define BONDECOMMANDE_H

#include <QDialog>

namespace Ui {
class BonDeCommande;
}

class BonDeCommande : public QDialog
{
    Q_OBJECT

public:
    explicit BonDeCommande(QWidget *parent = 0);
    ~BonDeCommande();

private:
    Ui::BonDeCommande *ui;
};

#endif // BONDECOMMANDE_H
