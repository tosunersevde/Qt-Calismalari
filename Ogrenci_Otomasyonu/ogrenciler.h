#ifndef OGRENCILER_H
#define OGRENCILER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class Ogrenciler;
}

class Ogrenciler : public QDialog
{
    Q_OBJECT

public:
    explicit Ogrenciler(QSqlDatabase, QWidget *parent = nullptr);
    ~Ogrenciler();
    void ogr_listele();

private slots:
    void on_tableView_ogrenciler_clicked(const QModelIndex &index);

    void on_pushButton_ogr_kayit_clicked();

    void on_pushButton_ogr_sil_clicked();

    void on_pushButton_ogr_guncelle_clicked();

private:
    Ui::Ogrenciler *ui;

    QSqlQuery *sorgu_ogrenci;

    QSqlQueryModel *model_ogrenci;


};

#endif // OGRENCILER_H
