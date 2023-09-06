#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet("background-color: rgb(210,210,210);");

    QPixmap arkaplan_resim(":/resources/images/arkaplan.jpg");
    arkaplan_resim = arkaplan_resim.scaled(this->size(),Qt::IgnoreAspectRatio);

    QPalette arkaplan_renk;
    arkaplan_renk.setBrush(QPalette::Window,arkaplan_resim);
    this->setPalette(arkaplan_renk);

    QTimer *timer1 = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QTimer *timer3 = new QTimer(this);
    QTimer *timer4 = new QTimer(this);

    timer1->start(2000);
    timer2->start(300);
    timer3->start(1000);
    timer4->start(1000);

    connect(timer1,&QTimer::timeout,this,&MainWindow::balon_olustur);
    connect(timer2,&QTimer::timeout,this,&MainWindow::balon_kaydir);
    connect(timer3,&QTimer::timeout,this,&MainWindow::gecen_sure);
    connect(timer4,&QTimer::timeout,this,&MainWindow::balon_kaybet);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::balon_olustur()
{
    int randrenk,randkonum, ekran_genislik;
    ekran_genislik = this->width()-50;

    randkonum = rand()%(ekran_genislik-50)+50;

    randrenk = rand()%(6);

    balonlar *balon = new balonlar(this);
    balon->setGeometry(randkonum,80,50,50);

    yeni_balonlar.push_back(balon);

    for(int i=0;i<=randrenk;i++)
    {
        balon->setStyleSheet("border-image: url(:/resources/images/"+QString::number(randrenk)+".jpg);");
    }
    balon->show();
}

void MainWindow::balon_kaydir()
{
    int balon_sayi = yeni_balonlar.size();
    for(int i=0;i<balon_sayi;i++)
    {
        if(yeni_balonlar[i]->tiklandi_mi==true)
        {
            vurulan_balonlar++;
            ui->label_vurulan_balonlar->setText(QString::number(vurulan_balonlar));
            yeni_balonlar[i]->setStyleSheet("border-image : url(:/resources/images/patlama.jpg)");
            patlayan_balonlar.push_back(yeni_balonlar[i]);
            yeni_balonlar.remove(i);
            balon_olustur();
        }
        else
        {
            yeni_balonlar[i]->setGeometry(yeni_balonlar[i]->x(),yeni_balonlar[i]->y()+20,yeni_balonlar[i]->width(),yeni_balonlar[i]->height());
            if(yeni_balonlar[i]->y()==this->height())
            kacan_balonlar++;
            ui->label_kacan_balonlar->setText(QString::number(kacan_balonlar));
        }
    }
}

void MainWindow::gecen_sure()
{
    sure++;
    ui->label_sure->setText(QString::number(sure));
}

void MainWindow::balon_kaybet()
{
    for(int i=0;i<vurulan_balonlar;i++)
    {
        patlayan_balonlar[i]->setVisible(false);
    }

}
