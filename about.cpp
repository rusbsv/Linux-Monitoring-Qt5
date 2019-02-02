#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),//наследуем от QDialog это диалоговое окно
    ui(new Ui::About) //подключение интерфейса из about.ui
{
    ui->setupUi(this); //установка интерфейса
}

About::~About() //деструктор вызывается после закрытия окна
{
    delete ui;
}
