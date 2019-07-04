#ifndef ADDLOAD_H
#define ADDLOAD_H

#include <QDialog>
#include <t_loads.h>

namespace Ui {
class AddLoad;
}

class AddLoad : public QDialog
{
    Q_OBJECT

public:
    explicit AddLoad(QWidget *parent = 0);
    ~AddLoad();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AddLoad *ui;
    t_loads loadtable;

};

#endif // ADDLOAD_H
