#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ogrenci_islem_clicked();

    void on_pushButton_ders_islem_clicked();

    void on_pushButton_not_islem_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    /*QLabel *label_ogr;
    QLabel *label_ders;
    QLabel *label_not;

    QPixmap ogr_resim;
    QPixmap ders_resim;
    QPixmap not_resim;*/
};
#endif // MAINWINDOW_H
