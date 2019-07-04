#ifndef RAPPORTQUOTIDIEN_H
#define RAPPORTQUOTIDIEN_H

#include <QDialog>
#include <v_daily.h>

namespace Ui {
class RapportQuotidien;
}

class RapportQuotidien : public QDialog
{
    Q_OBJECT

public:
    explicit RapportQuotidien(QWidget *parent = 0);
    ~RapportQuotidien();

private slots:
    void on_pushButton_annuler_clicked();

    void on_pushButton_confirmer_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::RapportQuotidien *ui;
    QSqlTableModel dialyTable;
};

#endif // RAPPORTQUOTIDIEN_H
