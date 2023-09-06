#ifndef BALONLAR_H
#define BALONLAR_H

#include <QPushButton>
#include <QTimer>

class balonlar : public QPushButton
{
    Q_OBJECT
public:
    balonlar(QWidget *parrent=0);
    bool tiklandi_mi;

public slots:
    void patlat();
};

#endif // BALONLAR_H
