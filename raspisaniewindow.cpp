#include "raspisaniewindow.h"
#include "ui_raspisaniewindow.h"

RaspisanieWindow::RaspisanieWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaspisanieWindow)
{
    ui->setupUi(this);
}

RaspisanieWindow::~RaspisanieWindow()
{
    delete ui;
}
