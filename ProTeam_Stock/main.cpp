#include "mainwindow.h"
#include <QApplication>
#include <mydatabase.h>
#include <t_loads.h>
#include <v_stock.h>
#include <v_historique.h>
#include <v_daily.h>

void fillDatabase();
bool fileExists(QString path);

bool isDatabaseEmpty = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyDatabase myDatabase;
    isDatabaseEmpty = !fileExists(myDatabase.defaultDatabasePath()) ;
    if(!myDatabase.initSQLITE3())
        return 1 ;

    t_client client;
    t_fournisseur fourniseur ;
    t_stock stock ;
    t_historique historique;
    t_historiqueBR historiqueBR ;
    t_historiqueDetails historiqueDetails ;
    t_historiqueFE historiqueFE ;
    t_historiqueFL historiqueFL ;
    t_loads loads;

    v_stock vstock;
    v_product vproduct;

    myDatabase.createTable(&vstock);
    myDatabase.createTable(&vproduct);
    myDatabase.createTable(&stock);

    myDatabase.createTable(&fourniseur);
    myDatabase.createTable(&client);
    myDatabase.createTable(&loads);

    myDatabase.createTable(&historique);
    myDatabase.createTable(&historiqueBR);
    myDatabase.createTable(&historiqueDetails);
    myDatabase.createTable(&historiqueFE);
    myDatabase.createTable(&historiqueFL);
    qDebug() << myDatabase.executeQuery(v_historique::getQuery()) ;
    qDebug() << myDatabase.executeQuery(v_dialy::getQuery()) ;

    qDebug() << myDatabase.tables();
    if(isDatabaseEmpty)
        fillDatabase();
    MainWindow w;
    w.show();

    return a.exec();
}

void fillDatabase()
{
    t_stock stock;
    stock.select();

    stock.setDesignation("produit 01");
    stock.setQuantite(100);
    stock.setPrix_Achat(1500);
    stock.setPrix_Vente_Demi_Gros(1600);
    stock.setPrix_Vente_Gros(1600);
    stock.setPrix_Vente_Detail(1600);
    stock.setDate_Achat(QDate::currentDate().toString("yyyy-MM-dd"));
    stock.setDate_Expiration(QDate::currentDate().toString("yyyy-MM-dd"));
    stock.insert();

    stock.setDesignation("produit 02");
    stock.setQuantite(80);
    stock.setPrix_Achat(1300);
    stock.setPrix_Vente_Demi_Gros(1400);
    stock.setPrix_Vente_Gros(1400);
    stock.setPrix_Vente_Detail(1400);
    stock.setDate_Achat(QDate::currentDate().toString("yyyy-MM-dd"));
    stock.setDate_Expiration("2019-02-10");
    stock.insert();

    stock.setDesignation("produit 03");
    stock.setQuantite(60);
    stock.setPrix_Achat(1100);
    stock.setPrix_Vente_Demi_Gros(1200);
    stock.setPrix_Vente_Gros(1200);
    stock.setPrix_Vente_Detail(1200);
    stock.setDate_Achat(QDate::currentDate().toString("yyyy-MM-dd"));
    stock.setDate_Expiration("2019-02-09");
    stock.insert();

    stock.setDesignation("produit 04");
    stock.setQuantite(0);
    stock.setPrix_Achat(1500);
    stock.setPrix_Vente_Demi_Gros(1600);
    stock.setPrix_Vente_Gros(1600);
    stock.setPrix_Vente_Detail(1600);
    stock.setDate_Achat(QDate::currentDate().toString("yyyy-MM-dd"));
    stock.setDate_Expiration("2019-02-08");
    stock.insert();

    t_fournisseur fournisseurs;
    fournisseurs.select();
    fournisseurs.setNom("jilali");
    fournisseurs.insert();

    t_client client;
    client.select();
    client.setNom("hamida");
    client.insert();

}

bool fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
