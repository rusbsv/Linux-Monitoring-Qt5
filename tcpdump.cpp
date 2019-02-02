#include "tcpdump.h"
#include "ui_tcpdump.h"

TCPDUMP::TCPDUMP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TCPDUMP)
{
    ui->setupUi(this);

    proc = new QProcess(this);//создаем новый процесс
    connect(proc, &QProcess::readyReadStandardOutput, this, &TCPDUMP::setStdout); //слот для обновления интерфейса из потока вывода в реальном времени

    arg << "-q" << "c"; //передаем аргументы q - краткий вывод, с - завершать поток после вывода информации
    proc->start("tcpdump"); //запускаем утилиту

}

TCPDUMP::~TCPDUMP()
{
    delete ui;
}

void TCPDUMP::setStdout() //функция, обновляющая интерфейс
{
    byteOut = proc->readAllStandardOutput(); //перехватываем вывод с консоли
    strOut = QTextCodec::codecForMib(106)->toUnicode(byteOut); //перекодируем
    ui->textEdit->append(strOut); //выводим в текстовое поле
}
