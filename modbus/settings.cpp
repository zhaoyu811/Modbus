#include "settings.h"
#include "ui_settings.h"
#include <qDebug>
#include <string.h>

settings::settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    QStringList serialPortList;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serialPortList.append(info.portName());
    }
    ui->cB_SerialPort->addItems(serialPortList);
}

settings::~settings()
{
    delete ui;
}

void settings::on_pB_Aplly_clicked()
{
    //int i=0;
    //const char *tmp = ui->lE_SerialPort->text().toStdString().c_str();
    //const char *tmp = QString(("\\\\.\\"+ui->cB_SerialPort->currentText())).toStdString().c_str();
    //qDebug()<<QString(("\\\\.\\"+ui->cB_SerialPort->currentText()));


    strcpy(serial.name, QString(("\\\\.\\"+ui->cB_SerialPort->currentText())).toStdString().c_str());
    /*
    for(;tmp[i]!='\0'; i++)
    {
        serial.name[i] = tmp[i];
    }
    serial.name[i] = '\0';
    qDebug()<<i;
    */
    qDebug()<<serial.name;

    serial.baudRate = ui->cB_Baudrate->currentText().toInt();
    serial.dataBits = ui->cB_DataBits->currentText().toInt();
    serial.stopBits = ui->cB_StopBits->currentText().toInt();

    if(ui->cB_Parity->currentText() == "No")
    {
        serial.parity = 'N';
    }
    else if(ui->cB_Parity->currentText() == "Even")
    {
        serial.parity = 'E';
    }
    else if(ui->cB_Baudrate->currentText() == "Odd")
    {
        serial.parity = 'O';
    }
    else
    {
        serial.parity = 'N';
    }

    this->hide();
}
