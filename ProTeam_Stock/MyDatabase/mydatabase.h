#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>
#include <QMetaClassInfo>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QApplication>

// TODO : trick ... :D
#include "t_client.h"
#include "t_stock.h"
#include "t_fournisseur.h"
#include "t_historique.h"
#include "t_historiquebr.h"
#include "t_historiqueDetails.h"
#include "t_historiqueFE.h"
#include "t_historiqueFL.h"


class MyDatabase : public QObject
{
    Q_OBJECT

public:
    explicit MyDatabase(QObject *parent = nullptr);
    bool initSQLITE3(QString pathDB="");
    void createTable(easyORM *obj);
    QMap<QString, QString> _schemaMap;
    bool executeQuery(QString query);
    void msgCritical(QString title, QString body);
    QStringList tables();
    QString defaultDatabasePath();

signals:

private:
    QString prepare_create(QString tableName, QStringList columnsList);
    QSqlDatabase myDatabase ;
    QString databaseType ;
};

#endif // MYDATABASE_H
