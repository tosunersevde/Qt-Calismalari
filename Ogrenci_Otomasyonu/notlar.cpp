#include "notlar.h"
#include "ui_notlar.h"

Notlar::Notlar(QSqlDatabase database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notlar)
{
    ui->setupUi(this);

    sorgu_not = new QSqlQuery(database);
    sorgu_ders = new QSqlQuery(database);
    sorgu_ogrenci = new QSqlQuery(database);

    ogr_listele();
    ders_listele();
    not_listele();
}

Notlar::~Notlar()
{
    delete ui;
}

void Notlar::ogr_listele()
{
    sorgu_ogrenci->prepare("select * from ogrenciler");
    if(!sorgu_ogrenci->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_ogrenci->lastError().text(),"Ok");
        return;
    }
    model_ogrenci = new QSqlQueryModel();
    model_ogrenci->setQuery(*sorgu_ogrenci);
    ui->tableView_tumogrenciler->setModel(model_ogrenci);
}

void Notlar::ders_listele()
{
    sorgu_ders->prepare("select * from dersler");
    if(!sorgu_ders->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_ders->lastError().text(),"Ok");
        return;
    }
    model_ders = new QSqlQueryModel();
    model_ders->setQuery(*sorgu_ders);
    ui->tableView_tumdersler->setModel(model_ders);
}

void Notlar::not_listele()
{
    sorgu_not->prepare("select * from notlar");
    if(!sorgu_not->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_not->lastError().text(),"Ok");
        return;
    }
    model_not = new QSqlQueryModel();
    model_not->setQuery(*sorgu_not);
    ui->tableView_ogr_ders_not->setModel(model_not);
}


void Notlar::on_pushButton_ders_kayit_ekle_clicked()
{
    int vize_not,final_not,gecmenotu;

    if(ui->lineEdit_ogr_no->text()=="" or ui->lineEdit_derskodu->text()==""  or ui->lineEdit_vizenot->text()=="" or ui->lineEdit_vizenot->text()=="")
    {
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    }
    else
    {
        sorgu_not->prepare("select * from notlar where ogr_no=? and ders_kodu=?");
        sorgu_not->addBindValue(ui->lineEdit_ogr_no->text().toInt());
        sorgu_not->addBindValue(ui->lineEdit_derskodu->text().toInt());
        if(!sorgu_not->exec())
            QMessageBox::critical(this,"Hata",sorgu_ders->lastError().text());
        int kayit_sayi=0;
        while(sorgu_not->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu ogrenci uzerinde bu ders zaten tanımlı!");
        }
        else
        {
            vize_not = ui->lineEdit_vizenot->text().toInt();
            final_not = ui->lineEdit_finalnot->text().toInt();
            gecmenotu = (vize_not * 0.4) + (final_not * 0.6);

            sorgu_not->prepare("insert into notlar(ogr_no,ders_kodu,vize_not,final_not,gecme_notu) values(?,?,?,?,?)");
            sorgu_not->addBindValue(ui->lineEdit_ogr_no->text());
            sorgu_not->addBindValue(ui->lineEdit_derskodu->text().toInt());
            sorgu_not->addBindValue(ui->lineEdit_vizenot->text().toInt());
            sorgu_not->addBindValue(ui->lineEdit_finalnot->text().toInt());
            sorgu_not->addBindValue(gecmenotu);
            if (sorgu_not->exec())
                QMessageBox::information(this,"Kayit Ekleme","Kayıt Basarı ile Eklendi!");
            else
                qDebug() << sorgu_not->lastError().text();
        }
    }
    not_listele();
}


void Notlar::on_tableView_tumogrenciler_clicked(const QModelIndex &index)
{
    ui->lineEdit_ogr_no->setText(model_ogrenci->index(index.row(),0).data().toString());
}


void Notlar::on_tableView_tumdersler_clicked(const QModelIndex &index)
{
    ui->lineEdit_derskodu->setText(model_ders->index(index.row(),0).data().toString());
}

