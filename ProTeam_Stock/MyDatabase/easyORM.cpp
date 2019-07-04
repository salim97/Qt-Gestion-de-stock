#include "easyORM.h"

#include <QCompleter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlQuery>

easyORM::easyORM()
{
    m_tableModel = new QSqlTableModel ;
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

easyORM::~easyORM()
{
    m_tableModel->clear();
    delete m_tableModel ;
    m_tableModel = nullptr;
}

void easyORM::init(QObject *obj)
{
    this->obj = obj ;
    //    qDebug() << "void easyORM::init(QObject *obj) " << obj->metaObject()->className() ;
    m_tableModel->setTable(obj->metaObject()->className());
    m_tableModel->select();
    m_databaseType = m_tableModel->database().driverName() ;
    setCurrentRow(0);
    getSchemaTable();
}

void easyORM::select()
{
    //m_tableModel->setFilter("");
    m_tableModel->select();
    m_currentRow = 0 ;
    for(int i = 0 ; i < m_tableModel->columnCount() ; i++)
        obj->setProperty(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data(),
                         m_tableModel->record(m_currentRow).value(i)) ;

//    int j = 0 ;
//    for(int i = obj->metaObject()->propertyOffset() ; i < obj->metaObject()->propertyCount(); i++, j++)
//        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(m_currentRow).value(j)) ;



}

bool easyORM::removeCurrentRow()
{
    m_tableModel->removeRow(m_currentRow) ;
    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }

    setCurrentRow(0);
    return true ;
}

bool easyORM::removeAllRows()
{
    bool ok = executeQuery(prepare_clearTable(m_tableModel->tableName()) ) ;
    setCurrentRow(0);
    return ok ;
}

void easyORM::msgCritical(QString title ,QString body)
{
    if(debug_CLI_enable)
        qDebug() << "title: "+ title << "\nboady: "+ body ;
    if(debug_GUI_enable)
        QMessageBox::critical(0,title,body);
}

QJsonObject easyORM::setCurrentRow(int index)
{
    m_currentRow = index ;

    if(index < 0 )
    {
        clearRow();
    }
    else
        for(int i = 0 ; i < m_tableModel->columnCount() ; i++)
            obj->setProperty(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data(),
                             m_tableModel->record(m_currentRow).value(i)) ;

//        for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
//        obj->setProperty(obj->metaObject()->property(i).name(), m_tableModel->record(m_currentRow).value(i-1)) ;
    return currentRowToJSON() ;
}

QString easyORM::tableName()
{
    return m_tableModel->tableName();
}

QString easyORM::parentTableName()
{
    return obj->property("_parentTable").toString();
}

QString easyORM::extraCondition()
{
    return obj->property("_extraCondition").toString().replace("\"", "");
}

void easyORM::clearRow()
{
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
    {
        if(QString(obj->metaObject()->property(i).name()).at(0) == '_')
            continue;
        if(obj->metaObject()->property(i).type() == QVariant::Int)
            obj->setProperty(obj->metaObject()->property(i).name(), 0);
        if(obj->metaObject()->property(i).type() == QVariant::String)
        {

            obj->setProperty(obj->metaObject()->property(i).name(), "");
        }

    }
}

bool easyORM::update()
{
//    int j = 1 ;
//    for(int i = obj->metaObject()->propertyOffset()+1; i < obj->metaObject()->propertyCount(); i++)
//    {
//        m_tableModel->setData(m_tableModel->index(m_currentRow, j), obj->metaObject()->property(i).read(obj));
//        j++ ;
//    }

    for(int i = 1 ; i < m_tableModel->columnCount() ; i++)
        m_tableModel->setData(m_tableModel->index(m_currentRow, i),
                              obj->property(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data()));

//        m_tableModel->record(m_currentRow).setValue(i,
//                  obj->property(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data()));

//        obj->setProperty(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data(),
//                         m_tableModel->record(m_currentRow).value(i)) ;


    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }
    return true ;
}

bool easyORM::insert()
{
    m_currentRow = m_tableModel->rowCount() ;
    m_tableModel->insertRow(m_currentRow);
    return update();
    /*
    for(int i = 1 ; i < m_tableModel->columnCount() ; i++)
        m_tableModel->setData(m_tableModel->index(m_currentRow, i),
                              obj->property(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data()));
//        m_tableModel->record(m_currentRow).setValue(i,
//                  obj->property(m_tableModel->record(m_currentRow).fieldName(i).toLatin1().data()));

//    int j = 1 ;
    //    for(int i = obj->metaObject()->propertyOffset()+1; i < obj->metaObject()->propertyCount(); i++)
//    {
//        m_tableModel->setData(m_tableModel->index(m_currentRow, j), obj->metaObject()->property(i).read(obj));
//        j++ ;
//    }

    if( !m_tableModel->submitAll() )
    {
        qDebug() << "insertion erreur: " << m_tableModel->lastError().text() ;
        return false ;
    }
    return true ;
    */

}

bool easyORM::where(QString condition)
{
    m_tableModel->setFilter(condition);
    bool ok = m_tableModel->select();
    if(!ok)
        msgCritical("bool easyORM::where(QString condition)", m_tableModel->lastError().text());
    setCurrentRow(0);
    return ok ;
}

bool easyORM::whereid(int id)
{
    return where("id == "+QString::number(id));
}

int easyORM::rowCount()
{
    return m_tableModel->rowCount();
}

QJsonObject easyORM::currentRowToJSON()
{
    QJsonObject json;
    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); i++)
    {
        json.insert(QString(obj->metaObject()->property(i).name()),
                    QJsonValue::fromVariant(obj->metaObject()->property(i).read(obj)));
    }
    QJsonDocument doc(json);
    return json ;
}

bool easyORM::executeQuery(QString query)
{
    QSqlQuery cmd ;
    bool ok = cmd.exec(query);
    if ( !ok ) msgCritical("_executeQuery", query+"\n"+cmd.lastError().text());
    return ok ;
}

QString easyORM::prepare_create(QString tableName, QStringList columnsList)
{
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
                returnValue += QString(columnsList[i]).split(" ")[0] + " FROM " + parentTableName() + extraCondition() ;

                break ;
            }
            returnValue += QString(columnsList[i]).split(" ")[0] + ", " ;
        }

    }

    return returnValue ;
}

QString easyORM::prepare_dropTable(QString tableName)
{
    return "" ; // TODO
}

QString easyORM::prepare_deleteItem(QString tableName, QString id)
{
    return "DELETE FROM "+tableName+" WHERE id == "+id ; // TODO
}

QString easyORM::prepare_clearTable(QString tableName)
{
    if(m_databaseType == "QSQLITE")
        return "DELETE FROM "+ tableName +" ; " ;

    if(m_databaseType == "QMYSQL")
        return "TRUNCATE "+ tableName +" ;" ;
    return "" ;
}

QString easyORM::getSchemaTable()
{
    QString tableName;
    QStringList columnsList ;
    tableName = obj->metaObject()->className() ;
    QString tmp ;

    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); ++i)
    {
        // TODO: replace qt type with sqlite type
        tmp = obj->metaObject()->property(i).read(obj).typeName();
        if(QString(obj->metaObject()->property(i).name()) == "id" )
        {
            columnsList << "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE";
            continue ;
        }
        if(QString(obj->metaObject()->property(i).name()).at(0) == '_')
            continue;

        tmp.replace("QString", "TEXT");
        tmp.replace("char", "CHARACTER(1)");
        tmp.replace("int", "INTEGER");
        tmp.replace("float", "FLOAT");
        tmp.replace("double", "DOUBLE");
        tmp.replace("QDate", "DATE");
        tmp.replace("QDateTime", "DATETIME");
        tmp.replace("bool", "BOOLEAN");

        columnsList << QString(obj->metaObject()->property(i).name()) +" "+tmp;
        m_columnsList <<    QString(obj->metaObject()->property(i).name());
        m_columnsTypes << tmp ;

    }
    //m_columnsTypes.removeFirst();
    //m_columnsList.removeFirst();
    return prepare_create(tableName, columnsList) ;
}

void easyORM::createTable()
{
    QString tableName;
    QStringList cl ;
    tableName = obj->metaObject()->className() ;
    QString tmp ;

    for(int i = obj->metaObject()->propertyOffset(); i < obj->metaObject()->propertyCount(); ++i)
    {
        // TODO: replace qt type with sqlite type
        tmp = obj->metaObject()->property(i).read(obj).typeName();
        tmp.replace("QString", "TEXT");
        tmp.replace("char", "CHARACTER(1)");
        tmp.replace("int", "INTEGER");
        tmp.replace("float", "FLOAT");
        tmp.replace("double", "DOUBLE");
        tmp.replace("QDate", "DATE");
        tmp.replace("QDateTime", "DATETIME");
        tmp.replace("bool", "BOOLEAN");
        if(QString(obj->metaObject()->property(i).name()).at(0) == '_')
            continue;
        cl << QString(obj->metaObject()->property(i).name()) +" "+tmp;
        m_columnsList <<    QString(obj->metaObject()->property(i).name());
        m_columnsTypes << tmp ;

    }

    QString schema = prepare_create(tableName, cl) ;
    if(!executeQuery(schema))
        qDebug() << "err: executeQuery(schema) ";
    _schemaMap.insert(tableName, schema);

}

QStringList easyORM::getColumn(int index)
{
    QStringList list ;
    for(int i = 0 ; i < m_tableModel->rowCount() ; i++)
    {
        list << m_tableModel->record(i).value(index).toString() ;
    }
    return list ;
}

void easyORM::enableAutoComplete(QComboBox *cb)
{
    QStringList sl ;
    for ( int i = 0 ; i < cb->count() ; i++ )
        sl << cb->itemText(i);

    QCompleter *cmpt = new QCompleter(sl, this);
    cmpt->setCompletionMode(QCompleter::PopupCompletion);
    cmpt->setCaseSensitivity(Qt::CaseInsensitive);
    cb->setCompleter(cmpt);
}

void easyORM::tableViewConfigVisibleColumns(QTableView *tableview)
{
    for( int i = 0 ; i < m_tableModel->columnCount() ; i++ )
    {
        if(obj->property(m_tableModel->record(0).fieldName(i).toLatin1().data()).isValid())
        {
            if(obj->property(QString("_"+m_tableModel->record(0).fieldName(i)).toLatin1().data()).isValid())
                tableview->hideColumn(i);
            else
                tableview->showColumn(i);
        }
        else
            tableview->hideColumn(i);
    }
}

