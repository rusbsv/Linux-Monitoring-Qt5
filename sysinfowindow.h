#ifndef SYSINFOWINDOW_H
#define SYSINFOWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class SysInfoWindow;
}

class SysInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SysInfoWindow(QWidget *parent = 0);
    ~SysInfoWindow();

private:
    Ui::SysInfoWindow *ui;
};

#endif // SYSINFOWINDOW_H
