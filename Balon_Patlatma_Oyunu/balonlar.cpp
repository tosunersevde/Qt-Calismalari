#include "balonlar.h"

balonlar::balonlar(QWidget *parrent):QPushButton(parrent)
{
    tiklandi_mi=false;
    connect(this,&QPushButton::clicked,this,&balonlar::patlat);
}

void balonlar::patlat()
{
    tiklandi_mi=true;
}
