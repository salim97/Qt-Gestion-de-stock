#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "myparentobject.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog, public MyParentObject
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
