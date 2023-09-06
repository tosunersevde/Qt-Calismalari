#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include "balonlar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int kacan_balonlar=0;
    int vurulan_balonlar=0;
    int sure=0;

public slots:
    void balon_olustur();

    void balon_kaydir();

    void gecen_sure();

    void balon_kaybet();


private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QList<balonlar*>yeni_balonlar;

    QList<balonlar*>patlayan_balonlar;


};
#endif // MAINWINDOW_H
