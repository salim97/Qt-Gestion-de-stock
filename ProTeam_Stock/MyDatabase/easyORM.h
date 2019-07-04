#ifndef EASYORM_H
#define EASYORM_H

#include <QJsonObject>
#include <QObject>

#include <QDebug>
#include <QMetaClassInfo>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QComboBox>
#include <QTableView>

#include "mypropertyhelper.h"

#define debug_CLI_enable true
#define debug_GUI_enable true
//TODO ; accualy you can pass  this, parent to qobject to benefite of auto delete

class easyORM: public QObject
{
    Q_OBJECT
public:
     easyORM();
    ~easyORM();

    void init(QObject *obj) ;

    void clearRow();
    QString getSchemaTable();
    void tableViewConfigVisibleColumns(QTableView *tableview);
    QString extraCondition();
    static bool executeQuery(QString query);
    // prepare text query for depency of database MYSQl vs SQLITE3
    QString prepare_create(QString tableName, QStringList columnsList);
    QString prepare_dropTable(QString tableName);
    static QString prepare_deleteItem(QString tableName, QString id);
    QString prepare_clearTable(QString tableName);

    static void msgCritical(QString title, QString body);


    bool removeCurrentRow();
    bool removeAllRows();
    QJsonObject setCurrentRow(int index);
    QString tableName() ;
    QString parentTableName();

    void select();
    virtual bool update();
    virtual bool insert();
    bool where(QString condition);
    bool whereid(int id);
    int rowCount() ;
    QJsonObject currentRowToJSON();

    void createTable();

    QStringList getColumn(int index) ;
    QSqlTableModel *toModel() {return m_tableModel; }
    QStringList columnsList() {return m_columnsList; }
    QStringList columnsTypes(){return m_columnsTypes; }
    int currentRow() { return m_currentRow ;}
    void enableAutoComplete(QComboBox *cb);
signals:
    void beforeInsert();
    void afterInsert();
    void beforeSelect();
    void afterSelect();

private:
    QSqlTableModel *m_tableModel ;
    QStringList m_columnsList, m_columnsTypes ;
    QObject *obj ;
    int m_currentRow = -1;
    QString m_databaseType ;
    QMap<QString, QString> _schemaMap;
};

#endif // EASYORM_H
