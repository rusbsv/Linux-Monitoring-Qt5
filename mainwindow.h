#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDateTime>
#include <qcustomplot.h>
#include <about.h>
#include <raspisaniewindow.h>
#include <sravneniewindow.h>
#include <sysinfowindow.h>
#include <userswindow.h>
#include <processwindow.h>
#include <tcpdump.h>
#include <snmp.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<double> x0, y0;
    QVector<double> x1, y1;
    QVector<double> x2, y2;
    QVector<double> x3, y3;
    QVector<double> x4, y4;
    QVector<double> x5, y5;
    QVector<double> x6, y6;
    QVector<double> x7, y7;
    QVector<double> x8, y8;

    QVector<double> receiveBytes, transmitBytes, receivePackets, transmitPackets;

    int cpuMonitorActive;
    int ramMonitorActive;
    int diskMonitorActive;
    int netMonitorActive;
    int swapMonitorActive;
    int processMonitorActive;


    QDateTime timeStartProgram;
    int tik;

    void saveLogFile(QVector<double> x, QVector<double> y, QString title);

private slots:
    void on_pushButtonSysInfo_clicked();

//  void on_pushButtonUsers_clicked();

    void on_pushButtonStartAll_clicked();

    void on_pushButtonStopAll_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonRaspisanie_clicked();

    void on_pushButtonSravnenie_clicked();

    void on_pushButtonProcess_clicked();

    void on_pushButtonStopCPU_clicked();

    void on_pushButtonStartCPU_clicked();

    void on_pushButtonSaveCPU_clicked();

    void on_pushButtonStartRAM_clicked();

    void on_pushButtonStopRAM_clicked();

    void on_pushButtonSaveRAM_clicked();

    void on_pushButtonStartDisk_clicked();

    void on_pushButtonStopDisk_clicked();

    void on_pushButtonSaveDisk_clicked();

    void on_pushButtonStartNet_clicked();

    void on_pushButtonStopNet_clicked();

    void on_pushButtonSaveNet_clicked();

    void on_pushButtonStartProcess_clicked();

    void on_pushButtonStopProcess_clicked();

    void on_pushButtonSaveProcess_clicked();

    void on_pushButtonStartSWAP_clicked();

    void on_pushButtonStopSWAP_clicked();

    void on_pushButtonSaveSWAP_clicked();

    void on_pushButtonTCPDUMP_clicked();

    void updateTik();

    void updateCPU();
    void updateRAM();
    void updateDisk();
    void updateNet();
    void updateProcess();
    void updateSWAP();


    void on_pushButtonSNMP_clicked();


private:
    Ui::MainWindow *ui;

    QTimer *tmr;

};

#endif // MAINWINDOW_H
