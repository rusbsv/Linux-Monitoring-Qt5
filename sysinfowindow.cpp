#include "sysinfowindow.h"
#include "ui_sysinfowindow.h"


SysInfoWindow::SysInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysInfoWindow)
{
    ui->setupUi(this);


    QFile ver("/proc/version"); //подключаем системные файлы
    QFile cpuinf("/proc/cpuinfo");
    QFile parts("/proc/partitions");

    //проверяем доступ на чтение
    if (!ver.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!cpuinf.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!parts.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    //назначаем поток чтения
    QTextStream in(&ver);
    QString line = in.readLine(); //читаем строку
    ui->textEdit->setText(line);//выводим в интерфейс
    QTextStream in3(&parts);//аналогично для остальных файлов, выводим всю информацию в них:
    line = in3.readAll();
    ui->textEdit->append("\n\nИнформация о разделах в системе:\n\n"+line);
    QTextStream in2(&cpuinf);
    line = in2.readAll();
    ui->textEdit->append("\n\nИнформация о CPU:\n\n"+line);

}

SysInfoWindow::~SysInfoWindow()
{
    delete ui;
}
