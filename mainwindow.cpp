#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), //наследование от QMainWindow, отвечающего за элементы интерфейса окна
    ui(new Ui::MainWindow) //создание объекта формы интерфейса, который подключается из mainwindow.ui
{
    ui->setupUi(this); //устанавливаем интерфейс окна, размеры окна 1080 на 720
    setFixedSize(1080, 720);

    tmr = new QTimer(this); //создание объекта-таймера для обновление графиков
    tmr->setInterval(1000); //интервал обновления графиков (1 секунда)

    tik = 0; // номер текущего "тика" для таймера
    on_pushButtonStartAll_clicked(); //при открытии программы стартуем все мониторы

    //настройки графиков

    QPen pen; // цвет графиков
    pen.setColor("red");

    //для графика загрузки CPU
    //Поле для заголовка графика:
    ui->widgetCPU->plotLayout()->insertRow(0);
    //Добавление заголовка на поле:
    ui->widgetCPU->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetCPU, "CPU, загрузка в %", QFont("sans", 8, QFont::Bold)));
    //Добавление графика
    ui->widgetCPU->addGraph();
    //установка цвета
    ui->widgetCPU->graph()->setPen(pen);
    //задаем перетаскивание и зуммирование колесом мыши
    ui->widgetCPU->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика ОЗУ
    ui->widgetRAM->plotLayout()->insertRow(0);
    ui->widgetRAM->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetRAM, "Использование ОЗУ, Гб", QFont("sans", 8, QFont::Bold)));
    ui->widgetRAM->addGraph();
    ui->widgetRAM->graph()->setPen(pen);
    ui->widgetRAM->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика дисковых операций ввода/вывода
    ui->widgetDisk->plotLayout()->insertRow(0);
    ui->widgetDisk->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetDisk, "Использование диска, кол-во операций I/O", QFont("sans", 8, QFont::Bold)));
    ui->widgetDisk->addGraph();
    ui->widgetDisk->graph()->setPen(pen);
    ui->widgetDisk->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика сети 1
    ui->widgetNet->plotLayout()->insertRow(0);
    ui->widgetNet->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetNet, "Сетевой интерфейс, прием Кб/сек", QFont("sans", 8, QFont::Bold)));
    ui->widgetNet->addGraph();
    ui->widgetNet->graph()->setPen(pen);
    ui->widgetNet->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика сети 2
    ui->widgetNet2->plotLayout()->insertRow(0);
    ui->widgetNet2->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetNet2, "Сетевой интерфейс, отправка Кб/сек", QFont("sans", 8, QFont::Bold)));
    ui->widgetNet2->addGraph();
    ui->widgetNet2->graph()->setPen(pen);
    ui->widgetNet2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика активных процессов
    ui->widgetProcess->plotLayout()->insertRow(0);
    ui->widgetProcess->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetProcess, "Процессы в системе, кол-во активных", QFont("sans", 8, QFont::Bold)));
    ui->widgetProcess->addGraph();
    ui->widgetProcess->graph()->setPen(pen);
    ui->widgetProcess->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика исользования подкачки
    ui->widgetSWAP->plotLayout()->insertRow(0);
    ui->widgetSWAP->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetSWAP, "Использование файла подкачки, Гб", QFont("sans", 8, QFont::Bold)));
    ui->widgetSWAP->addGraph();
    ui->widgetSWAP->graph()->setPen(pen);
    ui->widgetSWAP->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика сети 3
    ui->widgetTCP->plotLayout()->insertRow(0);
    ui->widgetTCP->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetTCP, "Сетевой интерфейс, пакетов получ.", QFont("sans", 8, QFont::Bold)));
    ui->widgetTCP->addGraph();
    ui->widgetTCP->graph()->setPen(pen);
    ui->widgetTCP->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //для графика сети 4
    ui->widgetTCP2->plotLayout()->insertRow(0);
    ui->widgetTCP2->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widgetTCP2, "Сетевой интерфейс, пакетов отправ.", QFont("sans", 8, QFont::Bold)));
    ui->widgetTCP2->addGraph();
    ui->widgetTCP2->graph()->setPen(pen);
    ui->widgetTCP2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);


    //ЗАПОЛНЯЕМ ПОЛЕ ВЫБОРА СЕТЕВЫХ ИНТЕРФЕЙСОВ:
    QFile netInt("/proc/net/dev");
    if (!netInt.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&netInt);//поток чтения файла
    in.readLine();
    in.readLine(); //пропускаем заголовок таблицы
    QString netInterface = in.readAll(); //читаем файл
    QStringList netInterfacesList = netInterface.split('\n'); //делим файл по переносам строки
    for(int i = 0; i < netInterfacesList.length(); i++){ ui->listWidget->addItem(netInterfacesList[i]);} //проходимся по строкам с сетевыми интерфейфсами, выводим каждую
    ui->listWidget->setSpacing(2);//задание списка вывода
    ui->listWidget->setItemSelected(0, 1);//выбор сетевого интерфейса по-умолчанию


    tmr->start(); // Запускаем таймер, задает интервал мониторинга и отрисовки (1 секунда)

    //дале - слоты, реагирующие на каждый сигнал таймера, и запускающие функцию мониторинга ситемы:
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateTik); // инкрементитровать таймер на 1
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateCPU); //обновить мониторинговые данные для ЦП
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateRAM); //для ОЗУ
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateDisk); //для диска
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateNet); //для 4-х графиков сетевые интерфейсы
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateProcess); //для активных процессов
    connect(tmr, &QTimer::timeout, this, &MainWindow::updateSWAP); //для использования подкачки

}

MainWindow::~MainWindow() //деструктор главного окна, при закрытии
{
    delete ui;
}

void MainWindow::updateTik(){ //инкриментируем таймер
    tik++; //на 1 тик
}

void MainWindow::updateCPU() //обновление статистики ЦП
{
    if(cpuMonitorActive){//если флаг мониторинг включен

        QFile cpu("/proc/loadavg"); //открываем файл /proc/loadavg
        if (!cpu.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&cpu); //передаем файл на поток вывода
        QString line = in.readLine(); //пропускаем первую строку

        y0.append((line.left(line.indexOf(' '))).toDouble() * 100); //для оси y графика парсим из файла текущую загрузку процессора, домножаем на 100, чтобы в %
        x0.append((double)tik); //на ось x графика добавляем текущий тик (секунд прошло со старта мониторинга)

//        qDebug() << x0 << y0;  //отладочный вывод в консоль

        ui->widgetCPU->graph()->setData(x0, y0); //задаем на графике собранные данные
        ui->widgetCPU->graph()->rescaleAxes(true); //перемасштабируем оси под обновленные параметры
        ui->widgetCPU->yAxis->setRangeLower(0); //установим минимальные значения оси y
        ui->widgetCPU->replot(); //перерисовка графика
    }
}

void MainWindow::updateRAM() //обновить статистику по ОЗУ
{
    if(ramMonitorActive){ //если мониторинг включен

        QFile mem("/proc/meminfo"); //открываем файл
        if (!mem.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&mem); //организуем поток вывода
        QString temp, temp2; //вспомогательные переменные
        int memtotal, memfree; //пременные для сохранения
        in >> temp >> memtotal;//сканируем  объем общей ОЗУ
        in >> temp >> temp >> memfree;//объем свободной

        y1.append((double)((memtotal-memfree)/1024/1024)); //вычитаем из общего объема ОЗУ объем свободной, делим для приведения к Гб, заносим в y
        x1.append((double)tik); //заносим номер секунды отсчета

//        qDebug() << x1 << memfree;

        ui->widgetRAM->graph()->setData(x1, y1);//аналогично, как и на первом графике - задаем данные
        ui->widgetRAM->graph()->rescaleAxes(true); //перемасштабируем оси
        ui->widgetRAM->yAxis->setRangeLower(0); //минимальное значение y
        ui->widgetRAM->replot();//перерисовка графика
    }
}

void MainWindow::updateDisk() //аналогично, обновление статистики по диску
{
    if(diskMonitorActive){ //проверка активности монитора

        QFile disk("/proc/diskstats"); //подключаем файл
        if (!disk.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&disk); //поток вывода
        QString line = in.readLine(); //пропускаем первую строку
        while(!line.contains(" sda")){ //ищем, встречается ли буквы диска "sda" в строке, перебираем строки пока не встретится
            line = in.readLine();
        }
        QString iospeed = line.section(' ', 11, -1).split(' ')[9];//12 колонка файла /proc/stat, в которой содержится количество текущих операций ввода/вывода
        y2.append(iospeed.toDouble()); //добавляем значение в вектора
        x2.append((double)tik);

//        qDebug() << line << iospeed << y2;

        ui->widgetDisk->graph()->setData(x2, y2);//и обновляем графики
        ui->widgetDisk->graph()->rescaleAxes(true);
        ui->widgetDisk->yAxis->setRangeLower(0);
        ui->widgetDisk->replot();
    }
}

void MainWindow::updateNet() //обновление статистики сетевых интерфейсов
{
    if(netMonitorActive){ //проверка активности монитора

        QFile net("/proc/net/dev"); //подключаем файл
        if (!net.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&net);//поток вывода
        QString temp, netInterface;//вспомогат.переменная
        double receiveB, receiveP, transmitB, transmitP; // принято-передано байтов/пакетов по сетевому устройству
        in.readLine();
        in.readLine(); //пропускаем заголовок таблицы
        //сохраняем в переменные имя сетевого интерфейса, прием байт, прием пакетов, передача байт, передача пакетов
        in >> netInterface  >> receiveB >> receiveP >> temp >> temp >> temp >> temp >> temp >> temp >> transmitB >> transmitP;

        if(receiveBytes.isEmpty()) receiveBytes.append(receiveB);  //если вектор полученных байт - пуст (т.е. только что запустили мониторинг) то занести первое  значение
        if(transmitBytes.isEmpty()) transmitBytes.append(transmitB); //если вектор переданных байт - пуст, то аналогично

        x3.append((double)tik);// добавляем текущую секунду со старта мониторов в вектор x
        y3.append((receiveB - receiveBytes.last())/1024); // вектор у = разность между текущим количеством принятых байт и сек.назад = скорость приема
        receiveBytes.append(receiveB);

//        qDebug() << netInterface << receiveB << y3 << transmitB << y7;

        //обновляем графики сети:
        ui->widgetNet->graph()->setData(x3, y3);
        ui->widgetNet->graph()->rescaleAxes(true);
        ui->widgetNet->yAxis->setRangeLower(0);
        ui->widgetNet->replot();

        x7.append((double)tik);
        y7.append((transmitB - transmitBytes.last())/1024); // разность между текущим количеством отправленных байт и сек.назад
        transmitBytes.append(transmitB);

        //обновляем графики сети:
        ui->widgetNet2->graph()->setData(x7, y7);
        ui->widgetNet2->graph()->rescaleAxes(true);
        ui->widgetNet2->yAxis->setRangeLower(0);
        ui->widgetNet2->replot();


        if(receivePackets.isEmpty()) receivePackets.append(receiveP);//если вектор полученных пакетов - пуст (т.е. только что запустили мониторинг) то занести первое  значение
        if(transmitPackets.isEmpty()) transmitPackets.append(transmitP);//если вектор переданных пакетов - пуст, то аналогично


        x6.append((double)tik);
        y6.append((receiveP - receivePackets.last())); // разность между текущим количеством принятых пакетов и сек.назад = скорость приема
        receivePackets.append(receiveP);

        //обновляем графики сети:
        ui->widgetTCP->graph()->setData(x6, y6);
        ui->widgetTCP->graph()->rescaleAxes(true);
        ui->widgetTCP->yAxis->setRangeLower(0);
        ui->widgetTCP->replot();

        x8.append((double)tik);
        y8.append((transmitP - transmitPackets.last())); // разность между текущим количеством отправленных пакетов и сек.назад
        transmitPackets.append(transmitP);

        //обновляем графики сети:
        ui->widgetTCP2->graph()->setData(x8, y8);
        ui->widgetTCP2->graph()->rescaleAxes(true);
        ui->widgetTCP2->yAxis->setRangeLower(0);
        ui->widgetTCP2->replot();
    }
}

void MainWindow::updateProcess() //мониторинг активных процессов
{
    if(processMonitorActive){ //если мониторинг активен

        QFile cpu("/proc/loadavg"); //поддключаем файл
        if (!cpu.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&cpu);//поток ввода

        QString line, temp;

        in >> temp >> temp >> temp >> line; //берем из файла 4й столбец

        y4.append((line.left(line.indexOf('/'))).toDouble()); //и заносим из столбца в y все до символа / - число активных процессов в данный момент
        x4.append((double)tik);

//        qDebug() << x4 << y4 <<line;

        //обновляем график активных процессов:
        ui->widgetProcess->graph()->setData(x4, y4);
        ui->widgetProcess->graph()->rescaleAxes(true);
        ui->widgetProcess->yAxis->setRangeLower(0);
        ui->widgetProcess->replot();
    }
}

void MainWindow::updateSWAP() //для графика файла подкачки
{
    if(swapMonitorActive){//если монитор активен

        QFile mem("/proc/meminfo"); //подключаем файл
        if (!mem.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&mem);//поток ввода
        QString temp, temp1; //вспомогательные переменные
        int memtotal, memfree;//переменные общего размера подкачки и свободного объема
        //пропускаем 14 строк
        for (int i =0; i < 14; i++) {
         in.readLine();
        }
        // идем к 15-й строке вывода, считываем переменные
        in >> temp >> memtotal >> temp1;
        in >> temp1 >> memfree;

        int swap_used = (memtotal - memfree)/1024/1024; //вычисляем объем используемой подкачки в Гб
        y5.append((double)swap_used);//присоединяем к векторам вычисленные значения
        x5.append((double)tik);

//       qDebug() << temp << memtotal << temp1 << memfree << y5;

        //обновляем графики:
        ui->widgetSWAP->graph()->setData(x5, y5);
        ui->widgetSWAP->graph()->rescaleAxes(true);
        ui->widgetSWAP->yAxis->setRangeLower(0);
        ui->widgetSWAP->replot();
    }
}

void MainWindow::on_pushButtonSysInfo_clicked()
{
    //вывод окна системной информации
    SysInfoWindow *sysinfo = new SysInfoWindow;
    sysinfo->show();
}

//void MainWindow::on_pushButtonUsers_clicked()
//{
//    //вывод пользователей, их прав и проч. инф. о них
//    UsersWindow *users = new UsersWindow;
//    users->show();

//}


void MainWindow::on_pushButtonStartAll_clicked()//кнопка Запустить все мониторы
{
    //запускаем все мониторы через слоты кнопок
    on_pushButtonStartCPU_clicked();
    on_pushButtonStartRAM_clicked();
    on_pushButtonStartDisk_clicked();
    on_pushButtonStartNet_clicked();
    on_pushButtonStartProcess_clicked();
    on_pushButtonStartSWAP_clicked();

}

void MainWindow::on_pushButtonStopAll_clicked()//кнопка Остановить все мониторы
{
    //выключаем все мониторы через слоты кнопок
    on_pushButtonStopCPU_clicked();
    on_pushButtonStopRAM_clicked();
    on_pushButtonStopDisk_clicked();
    on_pushButtonStopNet_clicked();
    on_pushButtonStopProcess_clicked();
    on_pushButtonStopSWAP_clicked();

}


void MainWindow::on_pushButtonAbout_clicked()
{
    //открывает окно "О программе"
    About *about = new About;
    about->show();
}

void MainWindow::on_pushButtonRaspisanie_clicked()
{
    //Открывает окно задания расписания мониторинга
    RaspisanieWindow *raspisanie = new RaspisanieWindow;
    raspisanie->show();
}

void MainWindow::on_pushButtonSravnenie_clicked() //кнопка сравнения графиков
{
    //Запускает сравнение показателей на одном графике
    SravnenieWindow *sravnenie = new SravnenieWindow;

    //ссылки на все вектора для каждого мониторящегося параметра,
    //информация в окне сравнения для графиков будет браться по этим ссылкам
    sravnenie->x0 = &x0; sravnenie->y0 = &y0;
    sravnenie->x1 = &x1; sravnenie->y1 = &y1;
    sravnenie->x2 = &x2; sravnenie->y2 = &y2;
    sravnenie->x3 = &x3; sravnenie->y3 = &y3;
    sravnenie->x4 = &x4; sravnenie->y4 = &y4;
    sravnenie->x5 = &x5; sravnenie->y5 = &y5;
    sravnenie->x6 = &x6; sravnenie->y6 = &y6;
    sravnenie->x7 = &x7; sravnenie->y7 = &y7;
    //отображение окна сравнения
    sravnenie->show();

}

void MainWindow::on_pushButtonProcess_clicked()
{
    //Открывает окно с процессами в системе
    ProcessWindow *processinfo = new ProcessWindow;
    processinfo->show();
}


void MainWindow::on_pushButtonStartCPU_clicked()
{ //нажата кнопка начать мониторинг CPU
    ui->pushButtonStartCPU->setEnabled(0); //сделать кнопку старт неактивной
    ui->pushButtonStopCPU->setEnabled(1); //активировать кнопку стоп
    cpuMonitorActive = 1; //флаг мониторинга CPU активирован
}

void MainWindow::on_pushButtonStopCPU_clicked()
{//нажата кнопка остановить мониторинг CPU
    ui->pushButtonStartCPU->setEnabled(1); //сделать кнопку старт активной
    ui->pushButtonStopCPU->setEnabled(0); //сделать кнопку стоп неактивной
    cpuMonitorActive = 0; //флаг мониторинга снят
}

void MainWindow::on_pushButtonSaveCPU_clicked()
{
        saveLogFile(x0, y0, "Использование CPU"); //нажата кнопка сохранить лог-файл, вызываем функцию сохранения
}


//далее - аналогично повторяется для кнопок активирующих, оставливающих мониторинг и сохраняющих лог-файлы:
void MainWindow::on_pushButtonStartRAM_clicked()
{//нажата кнопка начать мониторинг для ОЗУ
    ui->pushButtonStartRAM->setEnabled(0);
    ui->pushButtonStopRAM->setEnabled(1);
    ramMonitorActive = 1;
}

void MainWindow::on_pushButtonStopRAM_clicked()
{//кнопка остановить мониторинг для ОЗУ
    ui->pushButtonStartRAM->setEnabled(1);
    ui->pushButtonStopRAM->setEnabled(0);
    ramMonitorActive = 0;
}

void MainWindow::on_pushButtonSaveRAM_clicked()
{
        saveLogFile(x1, y1, "Использование ОЗУ"); //сохранить лог-файл
}

void MainWindow::on_pushButtonStartDisk_clicked()
{//начать мониторинг диска
    ui->pushButtonStartDisk->setEnabled(0);
    ui->pushButtonStopDisk->setEnabled(1);
    diskMonitorActive = 1;
}

void MainWindow::on_pushButtonStopDisk_clicked()
{//остановит мониторинг диска
    ui->pushButtonStartDisk->setEnabled(1);
    ui->pushButtonStopDisk->setEnabled(0);
    diskMonitorActive = 0;
}

void MainWindow::on_pushButtonSaveDisk_clicked()
{
        saveLogFile(x2, y2, "Дисковые операции"); //сохранение в лог-файл
}

void MainWindow::on_pushButtonStartNet_clicked()
{//начать сетевой мониторинг
    ui->pushButtonStartNet->setEnabled(0);
    ui->pushButtonStopNet->setEnabled(1);
    netMonitorActive = 1;
}


void MainWindow::on_pushButtonStopNet_clicked()
{//остановить сетевой мониторинг
    ui->pushButtonStartNet->setEnabled(1);
    ui->pushButtonStopNet->setEnabled(0);
    netMonitorActive = 0;
}


void MainWindow::on_pushButtonSaveNet_clicked()
{
        saveLogFile(x3, y3, "Статистика принятых данных по сети"); //сохранение 2-х лог-файлов  - для приема
        saveLogFile(x7, y7, "Статистика отправленных данных по сети"); //и для передачи данных по сети
}

void MainWindow::on_pushButtonStartProcess_clicked()
{//начать мониторинг активных процессов
    ui->pushButtonStartProcess->setEnabled(0);
    ui->pushButtonStopProcess->setEnabled(1);
    processMonitorActive = 1;
}

void MainWindow::on_pushButtonStopProcess_clicked()
{//остановить монитор активных процессов
    ui->pushButtonStartProcess->setEnabled(1);
    ui->pushButtonStopProcess->setEnabled(0);
    processMonitorActive = 0;
}

void MainWindow::on_pushButtonSaveProcess_clicked()
{
        saveLogFile(x4, y4, "Активные процессы в системе"); //сохранение лога
}

void MainWindow::on_pushButtonStartSWAP_clicked()
{//начать мониторинг подкачки
    ui->pushButtonStartSWAP->setEnabled(0);
    ui->pushButtonStopSWAP->setEnabled(1);
    swapMonitorActive = 1;
}

void MainWindow::on_pushButtonStopSWAP_clicked()
{ //остановит мониторинг подкачки
    ui->pushButtonStartSWAP->setEnabled(1);
    ui->pushButtonStopSWAP->setEnabled(0);
    swapMonitorActive = 0;
}

void MainWindow::on_pushButtonSaveSWAP_clicked()
{
    saveLogFile(x5, y5, "Использование SWAP"); //сохранение лога
}


void MainWindow::on_pushButtonTCPDUMP_clicked()
{//нажата кнопка tcpdump
    TCPDUMP *tcpdump = new TCPDUMP; //создаем экземрляр и открываем окно, описанное в tcpdump.cpp
    tcpdump->show();
}

void MainWindow::on_pushButtonSNMP_clicked()
{//нажата кнопка SNMP информация
    SNMP *snmp = new SNMP; //создаем экземрляр и открываем окно, описанное в snmp.cpp
    snmp->show();
}

void MainWindow::saveLogFile(QVector<double> x, QVector<double> y, QString title){ //функция сохранения в лог-файл показателей графика
    QString logfile = QFileDialog::getSaveFileName(0, "Save Dialog", title, "*.log"); //вызывает диалог сохранения файла

    QFile logf(logfile+".log"); //прибавляем к пути файла расширение
    if(logf.open(QIODevice::WriteOnly | QIODevice::Text))
        { //Если  файл открыт для записи
            QTextStream logfStream(&logf); //поток ввода
            logfStream << title << endl; //записываем заголовок для данных
            for(int i = 0; i < x.length(); i++){ //и в цикле записываем сами данные
                logfStream << x[i] << " "<< y[i] << endl; //в каждой строке файла - x и y, пока не дойдем до конца вектора
            }

            logf.close(); // Запись завершена, закрываем лог-файл
        }
}
