#ifndef RASPISANIEWINDOW_H
#define RASPISANIEWINDOW_H

#include <QDialog>

namespace Ui {
class RaspisanieWindow;
}

class RaspisanieWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RaspisanieWindow(QWidget *parent = 0);
    ~RaspisanieWindow();

private:
    Ui::RaspisanieWindow *ui;
};

#endif // RASPISANIEWINDOW_H
