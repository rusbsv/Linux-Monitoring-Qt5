#include "userswindow.h"
#include "ui_userswindow.h"

UsersWindow::UsersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersWindow)
{
    ui->setupUi(this);
}

UsersWindow::~UsersWindow()
{
    delete ui;
}
