#ifndef FACTUREDAVOIR_H
#define FACTUREDAVOIR_H

#include <QDialog>

namespace Ui {
class FactureDAvoir;
}

class FactureDAvoir : public QDialog
{
    Q_OBJECT

public:
    explicit FactureDAvoir(QWidget *parent = 0);
    ~FactureDAvoir();

private:
    Ui::FactureDAvoir *ui;
};

#endif // FACTUREDAVOIR_H
