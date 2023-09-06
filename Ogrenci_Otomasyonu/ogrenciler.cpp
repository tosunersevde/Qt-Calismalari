#include "ogrenciler.h"
#include "ui_ogrenciler.h"

Ogrenciler::Ogrenciler(QSqlDatabase database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ogrenciler)
{
    ui->setupUi(this);

    sorgu_ogrenci = new QSqlQuery(database);
    ogr_listele();
}

Ogrenciler::~Ogrenciler()
{
    delete ui;
}

void Ogrenciler::ogr_listele()
{
    sorgu_ogrenci->prepare("select * from ogrenciler");
    if(!sorgu_ogrenci->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_ogrenci->lastError().text(),"Ok");
        return;
    }
    model_ogrenci = new QSqlQueryModel();
    model_ogrenci->setQuery(*sorgu_ogrenci);
    ui->tableView_ogrenciler->setModel(model_ogrenci);
}



void Ogrenciler::on_tableView_ogrenciler_clicked(const QModelIndex &index)
{
    ui->lineEdit_ogrenci_no->setText(model_ogrenci->index(index.row(),0).data().toString());
    ui->lineEdit_ogrenci_ad->setText(model_ogrenci->index(index.row(),1).data().toString());
    ui->lineEdit_ogrenci_soyad->setText(model_ogrenci->index(index.row(),2).data().toString());
}


void Ogrenciler::on_pushButton_ogr_kayit_clicked()
{
    if(ui->lineEdit_ogrenci_ad->text()=="" or ui->lineEdit_ogrenci_soyad->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ogrenci->prepare("insert into ogrenciler values (:ogr_no,:ogr_ad,:ogr_soyad)");
        sorgu_ogrenci->bindValue(":ogr_ad",ui->lineEdit_ogrenci_ad->text());
        sorgu_ogrenci->bindValue(":ogr_soyad",ui->lineEdit_ogrenci_soyad->text());
        if (sorgu_ogrenci->exec())
            QMessageBox::information(this,"Kayit Ekleme","Kayıt Basarı ile Eklendi!");
        else
            qDebug() << sorgu_ogrenci->lastError().text();
        ogr_listele();
    }
}


void Ogrenciler::on_pushButton_ogr_sil_clicked()
{
    if(ui->lineEdit_ogrenci_ad->text()=="" or ui->lineEdit_ogrenci_soyad->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ogrenci->prepare("select * from notlar where ogr_no=?");
        sorgu_ogrenci->addBindValue(ui->lineEdit_ogrenci_no->text().toInt());
        if(!sorgu_ogrenci->exec())
            QMessageBox::critical(this,"Hata",sorgu_ogrenci->lastError().text());
        int kayit_sayi=0;
        while(sorgu_ogrenci->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu ogrenci silinemez! Bu ogrencinin ustune tanimlanmis dersler vardir!");
        }
        else
        {
            sorgu_ogrenci->prepare("delete from ogrenciler where ogr_no= (:ogr_no)");
            sorgu_ogrenci->bindValue(":ogr_no",ui->lineEdit_ogrenci_no->text().toInt());
            if (sorgu_ogrenci->exec())
                QMessageBox::information(this,"Kayit Silme","Kayıt Basarı ile Silindi!");
            else
                qDebug() << sorgu_ogrenci->lastError().text();
        }
    }
    ogr_listele();
}


void Ogrenciler::on_pushButton_ogr_guncelle_clicked()
{
    if(ui->lineEdit_ogrenci_ad->text()=="" or ui->lineEdit_ogrenci_soyad->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ogrenci->prepare("select * from notlar where ogr_no=?");
        sorgu_ogrenci->addBindValue(ui->lineEdit_ogrenci_no->text().toInt());
        if(!sorgu_ogrenci->exec())
            QMessageBox::critical(this,"Hata",sorgu_ogrenci->lastError().text());
        int kayit_sayi=0;
        while(sorgu_ogrenci->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu ogrenci guncellenemez! Bu ogrencinin ustune tanimlanmis dersler vardir!");
        }
        else
        {
            sorgu_ogrenci->prepare("update ogrenciler set ogr_ad=?, ogr_soyad=? where ogr_no=?");
            sorgu_ogrenci->addBindValue(ui->lineEdit_ogrenci_ad->text());
            sorgu_ogrenci->addBindValue(ui->lineEdit_ogrenci_soyad->text());
            sorgu_ogrenci->addBindValue(ui->lineEdit_ogrenci_no->text().toInt());
            if (sorgu_ogrenci->exec())
                QMessageBox::information(this,"Kayit Guncelleme","Kayıt Basarı ile Guncellendi!");
            else
                qDebug() << sorgu_ogrenci->lastError().text();
        }
    }
    ogr_listele();
}

