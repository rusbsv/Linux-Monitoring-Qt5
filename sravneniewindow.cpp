#include "sravneniewindow.h"
#include "ui_sravneniewindow.h"
#include <QDebug>


SravnenieWindow::SravnenieWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::SravnenieWindow)
{
    ui->setupUi(this);//установка формы графического интерфейса
    tmr = new QTimer(this); //создание объекта таймера
    tmr->setInterval(1000); //интервал обновления графиков (1 секунда)


    //создание поля для заголовка графика:
    ui->widget->plotLayout()->insertRow(0);
    //вывод заголовка
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Сравнение показателей", QFont("sans", 8, QFont::Bold)));
    //добавить график на виджет
    ui->widget->addGraph();
    //задать управление графиком мышью
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    tmr->start(); // Запускаем таймер, задает интервал отрисовки (1 секунда)
    sravnActive = 1; //флаг активности графиков сравнительного мониторинга

    ui->checkBox_1->setChecked(1); //по-умолчанию активирован первый чекбокс

    connect(tmr, &QTimer::timeout, this, &SravnenieWindow::updateTik); //слот, раз в секунду вызывает updateTik
}

SravnenieWindow::~SravnenieWindow()
{
    delete ui;
}

void SravnenieWindow::updateTik(){ //обновляем график ежесекундно
    //проверяем, какие чекбоксы отмечены, и ДОБАВЛЯЕМ соответствующие графики
    if(sravnActive)
    {
        if(ui->checkBox_1->isChecked()){ //если активен чекбокс для 1го графика
            ui->widget->addGraph(); // добавляем график на виджет
            updateGraphic(*x0, *y0, "red", 0); //задаем вектора для отрисовки, цвет линии - красный, номер графика - 0
        }

        if(ui->checkBox_2->isChecked()){// аналогично для каждого:
            ui->widget->addGraph();
            updateGraphic(*x1, *y1, "indigo", 1);
        }

        if(ui->checkBox_3->isChecked()){
            ui->widget->addGraph();
            updateGraphic(*x2, *y2, "yellow", 2);
        }

        if(ui->checkBox_4->isChecked()){
            ui->widget->addGraph();
            updateGraphic(*x3, *y3, "red", 3);
        }

        if(ui->checkBox_5->isChecked()){
            ui->widget->addGraph();
            updateGraphic(*x4, *y4, "blue", 4);
        }

        if(ui->checkBox_6->isChecked()){
            ui->widget->addGraph();
            updateGraphic(*x5, *y5, "orange", 5);
        }

        if(ui->checkBox_7->isChecked()){
            ui->widget->addGraph();
            updateGraphic(*x6, *y6, "green", 6);
        }


        if(ui->checkBox_9->isChecked()){
//            ui->widget->addGraph();
//            updateGraphic(*xLog, *yLog, "black", 8);
        }
    }
}

void SravnenieWindow::updateGraphic(QVector<double> &x, QVector<double> &y, QString color, int i)
{ // перерисовываем графики. функция принимает на вход : вектор Х, вектор У, цвет линии, номер графика

        ui->widget->graph()->setPen(QPen(QColor(color))); //задание цвета, переданного как аргумент в функцию
        ui->widget->graph()->setData(x, y); //задание данных графика
        ui->widget->graph()->rescaleAxes(true); //перемасштабирование осей под входные данные
        ui->widget->yAxis->setRangeLower(0); //минимальный уровень оси У
        ui->widget->replot(); // перерисовка графика

}


void SravnenieWindow::on_pushButtonStartSravn_clicked() //нажата кнопка старта мониторинга
{
    sravnActive = 1; // флаг активности мониторов в окне сравнения
}

void SravnenieWindow::on_pushButtonStopSravn_clicked() //нажата кнопка остановить мониторинг
{
    sravnActive = 0; //сбрасываем флаг
}

void SravnenieWindow::on_pushButtonLoad_clicked() //загрузить график из лог-файла
{
    QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "~/", "*.log"); //системный диалог открытия файла

    QFile file(fileName);//подключаем файл, проверяем на чтение
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString title = file.readLine();//вынимаем заголовок
        QVector<double> xs, ys;
        while(!file.atEnd()){// заполняем значения векторов Х и У, пока файл не закончится
            QString str = file.readLine(); //читаем строку файла
            QStringList lst = str.split(" "); //Х и У разделены пробелом на строке
            xs.append(lst[0].toDouble()); //заносим эти значения
            ys.append(lst[1].toDouble());
        }
       xLog = &xs;
       yLog = &ys;
       ui->widget->addGraph(); //аналогично строим график для данных из лог-файла
       ui->checkBox_9->setChecked(1);
       ui->checkBox_9->setText(title); //заголовок из файла записываем рядом с новым чек-боксом
       ui->checkBox_9->setEnabled(1);
       updateGraphic(*xLog, *yLog, "black", 8); //передаем вектора для отрисовки графика, цвет линии, номер графика
    }

}

void SravnenieWindow::on_pushButtonClose_clicked()//если нажата Выход
{
    this->close(); //закрываем окно сравнений графиков
}

void SravnenieWindow::on_pushButtonSaveJPG_clicked() //сохранение сравнительного графика в jpg
{
    //saveJpg(const QString &fileName, int width, int height, double scale, int quality);
    QString fileName = QFileDialog::getSaveFileName(0, "Save Dialog", "~/", "*.jpg");
    QFile file(fileName+".jpg");

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << file.errorString();
    } else {
        ui->widget->saveJpg(fileName+".jpg");
    }
}

void SravnenieWindow::on_pushButtonSaveTXT_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Open Dialog", "~/", "*.log");
}

void SravnenieWindow::on_pushButtonSavePDF_clicked()//сохранение сравнительного графика в pdf
{
    //savePdf(const QString &fileName, bool noCosmeticPen, int width, int height, const QString &pdfCreator, const QString &pdfTitle);
    QString fileName = QFileDialog::getSaveFileName(0, "Save Dialog", "~/", "*.pdf");
    QFile file(fileName+".pdf");

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << file.errorString();
    } else {
        ui->widget->savePdf(fileName+".pdf");
    }
}
