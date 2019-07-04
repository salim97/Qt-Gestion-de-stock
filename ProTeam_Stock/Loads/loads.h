#ifndef LOADS_H
#define LOADS_H

#include <QWidget>
#include <t_loads.h>

namespace Ui {
class Loads;
}

class Loads : public QWidget
{
    Q_OBJECT

public:
    explicit Loads(QWidget *parent = 0);
    ~Loads();

    void initAction();
     void refresh(){ loadsTable->select();}
private slots:
    void on_toolButton_new_charge_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::Loads *ui;
    t_loads *loadsTable;
};

#endif // LOADS_H
