#ifndef DERSLER_H
#define DERSLER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class Dersler;
}

class Dersler : public QDialog
{
    Q_OBJECT

public:
    explicit Dersler(QSqlDatabase, QWidget *parent = nullptr);
    ~Dersler();
    void ders_listele();
    void not_listele();

private slots:
    void on_pushButton_ders_kayit_clicked();

    void on_pushButton_ders_guncelle_clicked();

    void on_pushButton_ders_sil_clicked();

    void on_tableView_dersler_clicked(const QModelIndex &index);

private:
    Ui::Dersler *ui;

    QSqlQuery *sorgu_ders;

    QSqlQueryModel *model_ders;
    QSqlQueryModel *model_not;
};

#endif // DERSLER_H
