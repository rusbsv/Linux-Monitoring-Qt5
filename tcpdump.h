#ifndef TCPDUMP_H
#define TCPDUMP_H

#include <QDialog>
#include <QProcess>
#include <QTextCodec>
#include <QTimer>

namespace Ui {
class TCPDUMP;
}

class TCPDUMP : public QDialog
{
    Q_OBJECT

public:
    explicit TCPDUMP(QWidget *parent = 0);
    ~TCPDUMP();

private:
    Ui::TCPDUMP *ui;

    QProcess *proc;
    QStringList arg;
    QByteArray byteOut;
    QString strOut;
private slots:
    void setStdout();

};

#endif // TCPDUMP_H
