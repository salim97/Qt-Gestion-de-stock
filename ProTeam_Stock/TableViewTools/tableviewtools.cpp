#include "tableviewtools.h"
#include "ui_tableviewtools.h"
#include "filter.h"
#include "viewcolumns.h"

#include <QMenu>
#include <QSqlField>
#include <QSqlRecord>

TableViewTools::TableViewTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableViewTools)
{
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
}


TableViewTools::~TableViewTools()
{
    delete ui;
}

void TableViewTools::setModel(QSqlRelationalTableModel *&model)
{   //deprecated
    myModel = model ;
}

void TableViewTools::setModel(QSqlTableModel *model, QStringList columnsList, QStringList typesList)
{
    myModel = model ;
    this->columnsList = columnsList ;
    this->typesList   = typesList ;
}

void TableViewTools::setModel(easyORM *orm)
{
    myModel = orm->toModel() ;
    this->columnsList = orm->columnsList() ;
    this->typesList   = orm->columnsTypes() ;

    m_orm = orm ;
}

void TableViewTools::setTableView(QTableView *&tableView)
{
    myTableView = tableView;
}

void TableViewTools::initAction(QTableView *&tableView)
{
    // init widget action
    QAction  *supprime, *search, *view, *refresh;
    supprime = new QAction(ui->toolButton_suppr->text(), this);
    search = new QAction(ui->toolButton_Filter->text(), this);
    view = new QAction(ui->toolButton_view->text(), this);
    refresh = new QAction(ui->toolButton_refresh->text(), this);
    QMenu *seperator = new QMenu(this) ;
    //Icon
    supprime->setIcon(ui->toolButton_suppr->icon());
    search->setIcon(ui->toolButton_Filter->icon());
    view->setIcon(ui->toolButton_view->icon());
    refresh->setIcon(ui->toolButton_refresh->icon());

    // on click
    connect(supprime, SIGNAL(triggered(bool)),  this, SLOT(on_toolButton_suppr_clicked()));
    connect(search, SIGNAL(triggered(bool)),    this, SLOT(on_toolButton_Filter_clicked()));
    connect(view, SIGNAL(triggered(bool)),      this, SLOT(on_toolButton_view_clicked()));
    connect(refresh, SIGNAL(triggered(bool)),      this, SLOT(on_toolButton_refresh_clicked()));


    // init table with action
    tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    tableView->addAction(seperator->addSeparator());
    tableView->addAction(refresh);
    tableView->addAction(search);
    tableView->addAction(view);
    tableView->addAction(supprime);
}

bool TableViewTools::msgQuestion(QString title, QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(body);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      return true ;
    }

    return false ;
}

void TableViewTools::on_toolButton_Filter_clicked()
{
    Filter _Filter ;
    _Filter.init(myModel, columnsList, typesList);
    _Filter.exec();
}

void TableViewTools::on_toolButton_suppr_clicked()
{
    int currentRow = myTableView->currentIndex().row() ;
    if( currentRow == -1 ) return ;

    if(!msgQuestion("Attention!","êtes-vous sûr de vouloir supprimer ?"))
        return ;
    if(m_orm != nullptr && !m_orm->parentTableName().isEmpty())
    {
        QString id = myModel->record(currentRow).value("id").toString();
        m_orm->executeQuery(m_orm->prepare_deleteItem(m_orm->parentTableName(), id));
    }
    else
    {
        //old
        myModel->removeRow(currentRow);
        myModel->submitAll();
    }
    myModel->select();
}

void TableViewTools::on_toolButton_view_clicked()
{
    //TODO open dialog and show him list of check box for view columns true false then you know what to do
    // costume table view
    ViewColumns viewcolumns;
//    viewcolumns.init(myModel);
    viewcolumns.init(columnsList);
    viewcolumns.exec();
    for ( int i = 1 ; i < myModel->columnCount() ; i++)
        myTableView->showColumn(i);
    for ( int i = 0 ; i < viewcolumns.columnsToHide.length() ; i++)
    {
        myTableView->hideColumn(viewcolumns.columnsToHide[i]);
    }
}

void TableViewTools::on_toolButton_Export_clicked()
{

}

void TableViewTools::on_toolButton_Import_clicked()
{

}

void TableViewTools::on_toolButton_resizeColumnsToContents_clicked()
{
    return ;
    myTableView->resizeColumnsToContents();
}

void TableViewTools::on_toolButton_clean_table_clicked()
{
    return ;
    myModel->query().exec("TRUNCATE "+myModel->tableName()) ;
    myModel->select();
}

void TableViewTools::on_toolButton_refresh_clicked()
{
    myModel->setFilter("");
    myModel->select();

}



