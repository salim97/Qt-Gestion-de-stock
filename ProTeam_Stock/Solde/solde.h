#ifndef SOLDE_H
#define SOLDE_H

#include <QWidget>
#include <QSqlTableModel>
#include <mydatabase.h>

namespace Ui {
class Solde;
}

class Solde : public QWidget
{
    Q_OBJECT

public:
    explicit Solde(QWidget *parent = 0);
    ~Solde();

    void calcSum();
    QString reverseQString(QString chaine);
    void refresh(){ historiqueTable.select() ; }
private slots:
    void on_radioButton_clients_clicked();

    void on_radioButton_fournisseurs_clicked();

    void on_tableView_etat104_doubleClicked(const QModelIndex &index);

private:
    Ui::Solde *ui;
    QSqlTableModel historiqueTable;
};

#endif // SOLDE_H
