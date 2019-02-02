#ifndef SRAVNENIEWINDOW_H
#define SRAVNENIEWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDateTime>
#include <qcustomplot.h>
#include <QPrinter>

namespace Ui {
class SravnenieWindow;
}

class SravnenieWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SravnenieWindow(QWidget *parent = 0);
    ~SravnenieWindow();

    QVector<double> *x0, *y0;
    QVector<double> *x1, *y1;
    QVector<double> *x2, *y2;
    QVector<double> *x3, *y3;
    QVector<double> *x4, *y4;
    QVector<double> *x5, *y5;
    QVector<double> *x6, *y6;
    QVector<double> *x7, *y7;

    QVector<double> *xLog, *yLog;

private slots:
    void on_pushButtonStartSravn_clicked();

    void on_pushButtonStopSravn_clicked();

    void on_pushButtonLoad_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonSaveJPG_clicked();

    void on_pushButtonSaveTXT_clicked();

    void on_pushButtonSavePDF_clicked();

    void updateTik();

private:
    Ui::SravnenieWindow *ui;

    int sravnActive;

     QTimer *tmr;

     void updateGraphic(QVector<double> &x, QVector<double> &y, QString color, int i);
};

#endif // SRAVNENIEWINDOW_H
