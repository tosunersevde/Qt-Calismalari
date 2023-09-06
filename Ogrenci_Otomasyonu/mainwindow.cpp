#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ogrenciler.h"
#include "dersler.h"
#include "notlar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database.setDatabaseName("C:/Users/tosun/OneDrive/Belgeler/QtProjects/20010011044_Odev2/Database.db");
    if(!database.open())
    {
        ui->statusbar->showMessage("Veri Tabanina Baglanilamadi!");
    }
    else
    {
        ui->statusbar->showMessage("Veri Tabanina Baglanildi!");
    }

    ui->pushButton_ogr->setStyleSheet("border-image:url(:/resources/images/ogr.jpg)");
    ui->pushButton_ders->setStyleSheet("border-image:url(:/resources/images/ders.jpg)");
    ui->pushButton_not->setStyleSheet("border-image:url(:/resources/images/notlar.jpg)");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ogrenci_islem_clicked()
{
    Ogrenciler *ogrenciler = new Ogrenciler(database,this);
    ogrenciler->show();
}


void MainWindow::on_pushButton_ders_islem_clicked()
{
    Dersler *dersler = new Dersler(database,this);
    dersler->show();
}


void MainWindow::on_pushButton_not_islem_clicked()
{
    Notlar *notlar = new Notlar(database,this);
    notlar->show();
}

