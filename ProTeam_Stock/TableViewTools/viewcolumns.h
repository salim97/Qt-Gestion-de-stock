#ifndef VIEWCOLUMNS_H
#define VIEWCOLUMNS_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
class ViewColumns;
}

class ViewColumns : public QDialog//, public myParentObject
{
    Q_OBJECT

public:
    explicit ViewColumns(QWidget *parent = 0);
    ~ViewColumns();
    QList<int> columnsToHide ;
    void init(QSqlTableModel *&model);
    void init(QStringList columns);
private slots:

    void on_pushButton_Cancel_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_Unselect_All_clicked();

private:
    Ui::ViewColumns *ui;
};

#endif // VIEWCOLUMNS_H
