#include "mydatabase.h"


MyDatabase::MyDatabase(QObject *parent) : QObject(parent)
{

}

QString MyDatabase::defaultDatabasePath()
{
    QString databaseName = "database.db";
    QString databasePath = QDir::toNativeSeparators(QApplication::applicationDirPath()).replace("\\","/") +"/";
    return databasePath + databaseName;
}


bool MyDatabase::initSQLITE3(QString pathDB)
{
    if(pathDB.isEmpty())
    {
        databaseType = "QSQLITE" ;
        pathDB = defaultDatabasePath() ;
    }



    bool check = QSqlDatabase::isDriverAvailable(databaseType) ;
    if( !check ) msgCritical("Error", databaseType+" is not availabe");

    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName(pathDB);

    bool ok = myDatabase.open();
    if ( !ok ) msgCritical("Error", myDatabase.lastError().text());
    return ok ;
}

QStringList MyDatabase::tables()
{
    return myDatabase.tables() ;
}

void MyDatabase::createTable(easyORM *obj)
{


//    QStringList columnsList ;
//    tableName = obj->metaObject()->className() ;
//    QString tmp ;

//    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); ++i)
//    {
//        // TODO: replace qt type with sqlite type
//        tmp = obj->metaObject()->property(i).read(obj).typeName();
//        // TODO : fix this exception
//        if(QString(obj->metaObject()->property(i).name()) == "id" )
//        {
//            columnsList << "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE";
//            continue ;
//        }

//        tmp.replace("QString", "TEXT");
//        tmp.replace("char", "CHARACTER(1)");
//        tmp.replace("int", "INTEGER");
//        tmp.replace("float", "FLOAT");
//        tmp.replace("double", "DOUBLE");
//        tmp.replace("QDate", "DATE");
//        tmp.replace("QDateTime", "DATETIME");
//        tmp.replace("bool", "BOOLEAN");

//        if(QString(obj->metaObject()->property(i).name()).at(0) == '_')
//            continue;
//        columnsList << QString(obj->metaObject()->property(i).name()) +" "+tmp;

//    }

    QString tableName = obj->tableName();
//    QString schema = prepare_create(tableName, columnsList) ;
    QString schema = obj->getSchemaTable() ;

    // no need ...
    // add uniq id for each row .. case of SQLITE3
   // schema.replace("(","(id integer primary key autoincrement not null,"); // // TODO : replace this
    if(!executeQuery(schema))
        qDebug() << "err: executeQuery(schema) ";
    _schemaMap.insert(tableName, schema);

}

QString MyDatabase::prepare_create(QString tableName, QStringList columnsList)
{
//    QString returnValue = "CREATE TABLE IF NOT EXISTS "+ tableName +"(";
//    int n = columnsList.length() ;
//    for ( int i = 0 ; i < n ; i++ )
//    {
//        if ( i == n-1 )
//        {
//            returnValue += columnsList[i] + "); " ;
//            break ;
//        }
//        returnValue += columnsList[i] + ", " ;
//    }
//    return returnValue ;

    QString returnValue;
    if(tableName.startsWith("t_"))
    {
        returnValue = "CREATE TABLE IF NOT EXISTS "+ tableName +"(";

        int n = columnsList.length() ;
        for ( int i = 0 ; i < n ; i++ )
        {
            if ( i == n-1 )
            {
                returnValue += columnsList[i] + "); " ;
                break ;
            }
            returnValue += columnsList[i] + ", " ;
        }
    }

    if(tableName.startsWith("v_"))
    {
        returnValue = "CREATE VIEW IF NOT EXISTS "+ tableName +" AS SELECT ";

        int n = columnsList.length() ;
        for ( int i = 0 ; i < n ; i++ )
        {
            if ( i == n-1 )
            {
                returnValue += QString(columnsList[i]).split(" ")[0] + " FROM " + tableName.replace("v_", "t_") ;

                break ;
            }
            returnValue += QString(columnsList[i]).split(" ")[0] + ", " ;
        }

    }

    return returnValue ;
}

bool MyDatabase::executeQuery(QString query)
{
    QSqlQuery cmd ;
    bool ok = cmd.exec(query);
    if ( !ok ) msgCritical("_executeQuery", query+"\n"+cmd.lastError().text());
    return ok ;
}

void MyDatabase::msgCritical(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox::critical(0,title,body);

}
