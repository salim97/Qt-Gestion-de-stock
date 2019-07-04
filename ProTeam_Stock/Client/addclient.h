#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>
#include "t_client.h"

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = 0, int id = -1);
    ~AddClient();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddClient *ui;
    t_client clientTable;
};

#endif // ADDCLIENT_H
