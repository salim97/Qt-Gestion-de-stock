#ifndef MYBACKUPTOUSB_H
#define MYBACKUPTOUSB_H

#include <QDialog>

namespace Ui {
class MyBackupToUSB;
}

class MyBackupToUSB : public QDialog
{
    Q_OBJECT

public:
    explicit MyBackupToUSB(QWidget *parent = 0);
    ~MyBackupToUSB();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MyBackupToUSB *ui;
};

#endif // MYBACKUPTOUSB_H
