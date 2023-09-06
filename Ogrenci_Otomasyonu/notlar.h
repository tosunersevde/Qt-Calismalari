#ifndef NOTLAR_H
#define NOTLAR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class Notlar;
}

class Notlar : public QDialog
{
    Q_OBJECT

public:
    explicit Notlar(QSqlDatabase, QWidget *parent = nullptr);
    ~Notlar();

    void ogr_listele();
    void ders_listele();
    void not_listele();

private slots:

    void on_pushButton_ders_kayit_ekle_clicked();

    void on_tableView_tumogrenciler_clicked(const QModelIndex &index);

    void on_tableView_tumdersler_clicked(const QModelIndex &index);

private:
    Ui::Notlar *ui;

    QSqlQuery *sorgu_not;
    QSqlQuery *sorgu_ders;
    QSqlQuery *sorgu_ogrenci;

    QSqlQueryModel *model_not;
    QSqlQueryModel *model_ders;
    QSqlQueryModel *model_ogrenci;

};

#endif // NOTLAR_H
