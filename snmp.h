#ifndef SNMP_H
#define SNMP_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class SNMP;
}

class SNMP : public QDialog
{
    Q_OBJECT

public:
    explicit SNMP(QWidget *parent = 0);
    ~SNMP();

private:
    Ui::SNMP *ui;
};

#endif // SNMP_H
