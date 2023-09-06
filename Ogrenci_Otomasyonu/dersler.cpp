#include "dersler.h"
#include "ui_dersler.h"

Dersler::Dersler(QSqlDatabase database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dersler)
{
    ui->setupUi(this);

    sorgu_ders = new QSqlQuery(database);
    ders_listele();
    //not_listele();
}

Dersler::~Dersler()
{
    delete ui;
}

void Dersler::ders_listele()
{
    sorgu_ders->prepare("select * from dersler");
    if(!sorgu_ders->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_ders->lastError().text(),"Ok");
        return;
    }
    model_ders = new QSqlQueryModel();
    model_ders->setQuery(*sorgu_ders);
    ui->tableView_dersler->setModel(model_ders);
}

void Dersler::not_listele()
{
    sorgu_ders->prepare("select * from notlar where ders_kodu=?");
    sorgu_ders->addBindValue(ui->lineEdit_ders_kodu->text().toInt());
    if(!sorgu_ders->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu_ders->lastError().text(),"Ok");
        return;
    }
    model_not = new QSqlQueryModel();
    model_not->setQuery(*sorgu_ders);
    ui->tableView_secilenders_ogr->setModel(model_not);
}

void Dersler::on_pushButton_ders_kayit_clicked()
{
    if(ui->lineEdit_ders_kodu->text()=="" or ui->lineEdit_ders_adi->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ders->prepare("select * from dersler where ders_kodu=?");
        sorgu_ders->addBindValue(ui->lineEdit_ders_kodu->text().toInt());
        if(!sorgu_ders->exec())
            QMessageBox::critical(this,"Hata",sorgu_ders->lastError().text());
        int kayit_sayi=0;
        while(sorgu_ders->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu kodda baska bir ders vardir! Farkli kodda ders ekleyiniz!");
        }
        else
        {
            sorgu_ders->prepare("insert into dersler values (:ders_kodu,:ders_adi)");
            sorgu_ders->bindValue(":ders_kodu",ui->lineEdit_ders_kodu->text().toInt());
            sorgu_ders->bindValue(":ders_adi",ui->lineEdit_ders_adi->text());
            if (sorgu_ders->exec())
                QMessageBox::information(this,"Ders Ekleme","Ders Basarı ile Eklendi!");
            else
                qDebug() << sorgu_ders->lastError().text();
        }
    }
    ders_listele();
}


void Dersler::on_pushButton_ders_guncelle_clicked()
{
    if(ui->lineEdit_ders_kodu->text()=="" or ui->lineEdit_ders_adi->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ders->prepare("select * from notlar where ders_kodu=?");
        sorgu_ders->addBindValue(ui->lineEdit_ders_kodu->text().toInt());
        if(!sorgu_ders->exec())
            QMessageBox::critical(this,"Hata",sorgu_ders->lastError().text());
        int kayit_sayi=0;
        while(sorgu_ders->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu ders guncellenemez! Bu dersin ustune tanimlanmis ogrenciler vardir!");
        }
        else
        {
            sorgu_ders->prepare("update dersler set ders_kodu=(:ders_kodu), ders_adi=(:ders_adi) where ders_kodu= (:ders_kodu)");
            sorgu_ders->bindValue(":ders_kodu",ui->lineEdit_ders_kodu->text().toInt());
            sorgu_ders->bindValue(":ders_adi",ui->lineEdit_ders_adi->text());
            if (sorgu_ders->exec())
                QMessageBox::information(this,"Ders Guncelleme","Ders Basarı ile Guncellendi!");
            else
                qDebug() << sorgu_ders->lastError().text();
        }
    }
    ders_listele();
}


void Dersler::on_pushButton_ders_sil_clicked()
{
    if(ui->lineEdit_ders_kodu->text()=="" or ui->lineEdit_ders_adi->text()=="")
        QMessageBox::critical(this,"Hata","Gerekli alanlari doldurunuz!");
    else
    {
        sorgu_ders->prepare("select * from notlar where ders_kodu=?");
        sorgu_ders->addBindValue(ui->lineEdit_ders_kodu->text().toInt());
        if(!sorgu_ders->exec())
            QMessageBox::critical(this,"Hata",sorgu_ders->lastError().text());
        int kayit_sayi=0;
        while(sorgu_ders->next())
        {
            kayit_sayi++;
        }
        if(kayit_sayi>0)
        {
            QMessageBox::information(this,"Hata","Bu ders silinemez! Bu derse kayitli ogrenciler vardir!");
        }
        else
        {
            sorgu_ders->prepare("delete from dersler where ders_kodu= (:ders_kodu)");
            sorgu_ders->bindValue(":ders_kodu",ui->lineEdit_ders_kodu->text().toInt());
            if (sorgu_ders->exec())
                QMessageBox::information(this,"Ders Silme","Ders Basarı ile Silindi!");
            else
                qDebug() << sorgu_ders->lastError().text();
        }
    }
    ders_listele();
}


void Dersler::on_tableView_dersler_clicked(const QModelIndex &index)
{
    ui->lineEdit_ders_kodu->setText(model_ders->index(index.row(),0).data().toString());
    ui->lineEdit_ders_adi->setText(model_ders->index(index.row(),1).data().toString());

    not_listele();
}

