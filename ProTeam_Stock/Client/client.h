#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <myparentobject.h>
#include "addclient.h"
#include "t_client.h"

namespace Ui {
class Client;
}

class Client : public QWidget, public MyParentObject
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    void refresh(){ logTable.select() ; clientTable->select();}
    void initAction();
private slots:
    void on_toolButton_new_client_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_stackedWidget_currentChanged(int arg1);

    void on_toolButton_back_clicked();

    void on_tableView_log_doubleClicked(const QModelIndex &index);

private:
    Ui::Client *ui;
    t_client *clientTable;
    QSqlTableModel logTable;
};

#endif // CLIENT_H
