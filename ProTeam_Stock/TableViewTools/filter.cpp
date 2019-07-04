#include "filter.h"
#include "ui_filter.h"


#include <QSqlTableModel>
#include <QDebug>

Filter::Filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
    ui->dateEdit_First->setVisible(false);
}

Filter::~Filter()
{
    delete ui;
}

void Filter::init(QSqlTableModel *&model, QStringList columnsList, QStringList typesList)
{
    myModel = model ;
    this->columnsList = columnsList;
    this->typesList = typesList ;
     ui->comboBox_Type->addItems(columnsList);
     if(columnsList.contains("Designation"))
         ui->comboBox_Type->setCurrentIndex(columnsList.indexOf("Designation", 0));
     else   if(columnsList.contains("Nom"))
         ui->comboBox_Type->setCurrentIndex(columnsList.indexOf("Nom", 0));
     else
         ui->comboBox_Type->setCurrentIndex(0);
 /*
    QStringList temp ;
    int columnCount = myModel->columnCount();
    for( int i = 0 ; i < columnCount ; i++ )
        temp << myModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();

    ui->comboBox_Type->addItems(temp);
    ui->comboBox_Type->setCurrentIndex(1);
    */
}

void Filter::initDate(QString firstDate, QString lastDate)
{
    ui->dateEdit_First->setDate(QDate::fromString(lastDate,"yyyy-MM-dd"));
    ui->dateEdit_Second->setDate(QDate::fromString(firstDate,"yyyy-MM-dd"));
}

void Filter::on_comboBox_Date_Condition_currentIndexChanged(int index)
{
    if ( index == 5 )
    {
        bool temp = true ;
        ui->dateEdit_First->setVisible(temp);
        ui->dateEdit_Second->setVisible(temp);
    }
    else
    {
        ui->dateEdit_First->setVisible(false);
    }
}

void Filter::on_pushButton_Cancel_clicked()
{
    close();
}

void Filter::on_pushButton_OK_clicked()
{
    int index = ui->comboBox_Type->currentIndex() ;
    //QString columnName = ui->comboBox_Type->currentText();
    QString columnName = columnsList[index];
    if ( typesList[index] == "INTEGER" )
    {
        QString value = ui->spinBox_find->text() ;
        if ( value.isEmpty() ) { close() ; return ; }
        filterQuery = columnName + " == '"+ value + "'" ;
        qDebug() << filterQuery ;
    }

    if ( typesList[index] == "TEXT" )
    {
        QString value = ui->lineEdit_find->text() ;
        if ( value.isEmpty() ) { close() ; return ; }
        filterQuery = columnName + " Like '%"+ value + "%'" ;
    }
    QString temp = typesList[index];
    if ( temp.contains("DATE")  )
    {
        if ( ui->comboBox_Date_Condition->currentIndex() == 5 )
        {
            if ( ui->dateEdit_First->text().isEmpty() ) { close() ; return ; }
            filterQuery = columnName + between() ;
        }
        else
        {
            QString value = ui->dateEdit_Second->dateTime().toString("yyyy-MM-dd") ;
            if ( value.isEmpty() ) { close() ; return ; }
            if(ui->comboBox_Date_Condition->currentText() == "==")
                filterQuery = columnName + " LIKE '%"+ value + "%'" ;
            else
                filterQuery = columnName + " "+ ui->comboBox_Date_Condition->currentText() +" '"+ value + "'" ;
        }
    }

    if( !myModel->filter().isEmpty() )
        myModel->setFilter(filterQuery + " AND " + myModel->filter());
    else
         myModel->setFilter(filterQuery);
qDebug() << filterQuery ;
    myModel->select();

    close();
}

QString Filter::between()
{
    QString query ;

    QString value1 = ui->dateEdit_First->dateTime().toString("yyyy-MM-dd") ;
    QString value2 = ui->dateEdit_Second->dateTime().toString("yyyy-MM-dd") ;

    QString t1 = value1 ;
    QString t2 = value2 ;

    int temp1 = t1.replace("-","").toInt() ;
    int temp2 = t2.replace("-","").toInt() ;

    if ( temp1 < temp2 )
    {
        query = " BETWEEN '"+ value1 +"' AND '"+ value2 +"'" ;
    }
    else
    {
        query = " BETWEEN '"+ value2 +"' AND '"+ value1 +"'" ;
    }

    return query ;
}

void Filter::on_comboBox_Type_currentIndexChanged(int index)
{
    qDebug() << columnsList[index] << typesList[index] ;
    if ( typesList[index] == "TEXT" ) ui->stackedWidget->setCurrentIndex(0);
//    if ( typesList[index] == "DATE" ) ui->stackedWidget->setCurrentIndex(1);
    QString temp = typesList[index];
    if ( temp.contains("DATE")  ) ui->stackedWidget->setCurrentIndex(1);

    if ( typesList[index] == "INTEGER" ) ui->stackedWidget->setCurrentIndex(2);
}
