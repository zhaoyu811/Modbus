#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class settings;
}

class settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    struct Serial
    {
        char name[20];
        int  baudRate;
        int  dataBits;
        char parity;
        int  stopBits;
    };

    Serial serial;

private slots:
    void on_pB_Aplly_clicked();

private:
    Ui::settings *ui;

};

#endif // SETTINGS_H
