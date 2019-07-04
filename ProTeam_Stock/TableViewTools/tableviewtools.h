#ifndef TABLEVIEWTOOLS_H
#define TABLEVIEWTOOLS_H

#include <QWidget>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include <QDebug>
#include <QGridLayout>
#include <QVariant>
#include <qtableview.h>

#include "mydatabase.h"

#include "filter.h"
#include "viewcolumns.h"

namespace Ui {
class tableViewTools;
}

class TableViewTools : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewTools(QWidget *parent = 0);
    ~TableViewTools();
    void setModel(QSqlRelationalTableModel *&model);
    void setModel(QSqlTableModel *model, QStringList columnsList, QStringList typesList);
    void setTableView(QTableView *&tableView);
    bool msgQuestion(QString title, QString body);

    void initAction(QTableView *&tableView);
    void setModel(easyORM *orm);
public slots:
    void on_toolButton_Filter_clicked();

    void on_toolButton_suppr_clicked();

    void on_toolButton_view_clicked();

    void on_toolButton_Export_clicked();

    void on_toolButton_Import_clicked();

    void on_toolButton_resizeColumnsToContents_clicked();

    void on_toolButton_clean_table_clicked();

    void on_toolButton_refresh_clicked();


private:
    Ui::tableViewTools *ui;
    QSqlTableModel *myModel ;
    QTableView *myTableView;
    QStringList columnsList, typesList ;
     easyORM *m_orm = nullptr;
};

#endif // TABLEVIEWTOOLS_H
