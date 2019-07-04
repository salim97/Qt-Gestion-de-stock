#ifndef CHEKLA_H
#define CHEKLA_H

#include <QDialog>

namespace Ui {
class Chekla;
}

class Chekla : public QDialog
{
    Q_OBJECT

public:
    explicit Chekla(QWidget *parent = 0);
    ~Chekla();

private:
    Ui::Chekla *ui;
};

#endif // CHEKLA_H
