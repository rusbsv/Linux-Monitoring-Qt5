#ifndef USERSWINDOW_H
#define USERSWINDOW_H

#include <QDialog>

namespace Ui {
class UsersWindow;
}

class UsersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UsersWindow(QWidget *parent = 0);
    ~UsersWindow();

private:
    Ui::UsersWindow *ui;
};

#endif // USERSWINDOW_H
