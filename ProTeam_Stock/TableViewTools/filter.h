#ifndef FILTER_H
#define FILTER_H

#include <QDialog>
#include <QSqlTableModel>
#include "mydatabase.h"

namespace Ui {
class Filter;
}

class Filter : public QDialog//, public myParentObject
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = 0);
    ~Filter();


    void init(QSqlTableModel *&model, QStringList columnsList, QStringList typesList);
    void initDate(QString firstDate, QString lastDate);
private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

    void on_comboBox_Date_Condition_currentIndexChanged(int index);

    void on_comboBox_Type_currentIndexChanged(int index);

private:
    Ui::Filter *ui;
    QSqlTableModel *myModel;
    QStringList columnsList, typesList ;
    QString filterQuery ;
    QString between();
};

#endif // FILTER_H
