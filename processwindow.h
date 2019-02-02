    #ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H

#include <QDialog>
#include <QProcess>
#include <QTextCodec>
#include <QTimer>

namespace Ui {
class ProcessWindow;
}

class ProcessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessWindow(QWidget *parent = 0);
    ~ProcessWindow();

private:
    Ui::ProcessWindow *ui;
    QProcess *proc;
    QStringList arg;
    QByteArray byteOut;
    QString strOut;

    int i;
    QTimer *tmr;
    void updateP();
};

#endif // PROCESSWINDOW_H
