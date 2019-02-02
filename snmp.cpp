#include "snmp.h"
#include "ui_snmp.h"

SNMP::SNMP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SNMP)
{
    ui->setupUi(this);

    QFile snmp("/proc/net/snmp"); //подключаем системные файлы для парсинга
    QFile snmp6("/proc/net/snmp6");

    //пытаемся открыть их для чтения:
    if (!snmp.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!snmp6.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&snmp); //поток вывода
    QString line = in.readLine();//читаем строку
    ui->textEdit->setText(line); //выводим на текстовое поле
    QTextStream in1(&snmp6);// и для второго файла
    line = in1.readAll(); //читаем его весь
    ui->textEdit->append("\n\nИнформация о SNMP 6:\n\n"+line); //выводим
}

SNMP::~SNMP()
{
    delete ui;
}
