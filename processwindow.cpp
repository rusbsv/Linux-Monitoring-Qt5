#include "processwindow.h"
#include "ui_processwindow.h"

ProcessWindow::ProcessWindow(QWidget *parent) : //аналогично, как и в прошлых классах
    QDialog(parent),
    ui(new Ui::ProcessWindow)
{
    ui->setupUi(this);
    proc = new QProcess(this);

    tmr = new QTimer(this); //создаем объект таймера
    tmr->setInterval(1000); //интервал обновления
    i = 0;

    connect(tmr, &QTimer::timeout, this, &ProcessWindow::updateP); //слот, вызыввающий каждую секунду функцию updateP

    tmr->start(); // Запускаем таймер
}

ProcessWindow::~ProcessWindow()
{
    delete ui;
}

void ProcessWindow::updateP(){ //

    arg << "axu"; //аргументы команды ps
    proc->start("ps", arg); //  в консоли стартует утилита ps с заданными параметрами
    proc->waitForFinished(); //ждем, когда утилита выполнится
    byteOut = (proc->readAllStandardOutput()); //меняем кодировку стандартног потока вывода:
    strOut = QTextCodec::codecForMib(106)->toUnicode(byteOut);

    ui->textEdit->setText(strOut); //выводим текст из стандартного потока вывода в окно, в поле для текста
    i++;
}
