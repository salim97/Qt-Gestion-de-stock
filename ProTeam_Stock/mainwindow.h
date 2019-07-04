#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <historique.h>
#include <loads.h>
#include <QInputDialog>
#include <solde.h>

#include "client.h"
#include "stock.h"
#include "fournisseurs.h"
#include "mydatabase.h"
#include "myparentobject.h"
#include "etat104versement.h"
#include "settings.h"
#include "mybackuptousb.h"
#include <QStorageInfo>
#include "bondereception.h"
#include "facture.h"
#include <bondelivraison.h>
#include <facturedavoir.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public MyParentObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initHistoriqueView();

private slots:
    void on_toolButton_bonDeReception_clicked();

    void on_toolButton_facture_clicked();

    void on_toolButton_bonDeCommande_clicked();

    void on_actionQuiter_triggered() { close(); }

    void on_actionParametres_triggered();

    void on_toolButton_bonDeLivraison_clicked();

    void on_toolButton_facture_d_avoir_clicked();

    void on_actionBackupToUSB_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_actionRapport_quotidien_triggered();

private:
    Ui::MainWindow *ui;
    Historique *historique;
    Client *client;
    Stock *stock ;
    Fournisseurs *fournisseurs;
    Loads *loads ;
    Solde *solde ;

    QSqlQueryModel modelEtat104;

};

#endif // MAINWINDOW_H
