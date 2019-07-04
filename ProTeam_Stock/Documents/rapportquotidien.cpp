#include "rapportquotidien.h"
#include "ui_rapportquotidien.h"

RapportQuotidien::RapportQuotidien(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RapportQuotidien)
{
    ui->setupUi(this);
    ui->checkBox_regroup_by_article->setVisible(false);
    ui->dateEdit->setDate(QDate::currentDate());

    dialyTable.setTable(v_dialy::tableName());
    dialyTable.setFilter("dateDocument LIKE '"+ui->dateEdit->date().toString("yyyy-MM-dd")+"'");
    dialyTable.select();
    ui->tableView->setModel(&dialyTable);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(v_dialy::_00id);
    ui->tableView->hideColumn(v_dialy::_01idH);
    ui->tableView->hideColumn(v_dialy::_02idP);



    /*
     *     var reqString = "
                        SELECT
                            product.id, product.code , product.name ,bill.date,
                            "+modif_1+",
                            CASE bill.type WHEN 'bon_de_reception'  THEN  stock_record.price
                            ELSE NULL END AS price_buy,
                            CASE bill.type WHEN 'bon_de_reception'  THEN  NULL
                            ELSE stock_record.price END AS price_sell,
                            CASE bill.type WHEN 'bon_de_reception'  THEN 'Entrer'
                            ELSE 'Sortie' END AS type,
                            "+modif_2+" as money
                        FROM bill,product,stock_record
                        WHERE stock_record.id_product=product.id
                            AND stock_record.id_bill=bill.id
                            AND (bill.type='bon_de_livraison' OR bill.type='facture' AND bill.delivred=1 OR bill.type='bon_de_reception')
                            AND bill.date='"+formatDate(date.text)+"'"+modif_3;
                Req.requete(productsModel, reqString);
*/
}

RapportQuotidien::~RapportQuotidien()
{
    delete ui;
}

void RapportQuotidien::on_pushButton_annuler_clicked()
{
    close();
}

void RapportQuotidien::on_pushButton_confirmer_clicked()
{
    close();
}

void RapportQuotidien::on_pushButton_refresh_clicked()
{
    dialyTable.setFilter("dateDocument LIKE '"+ui->dateEdit->date().toString("yyyy-MM-dd")+"'");
    dialyTable.select();


}
