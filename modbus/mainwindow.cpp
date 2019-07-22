#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->hL_MainLayout);
    s = new settings(this);
    this->setTabOrder(ui->lE_Slave_W, ui->lE_Registor_W);
    this->setTabOrder(ui->lE_Registor_W, ui->lE_Data_W);
    this->setTabOrder(ui->lE_Data_W, ui->pB_Send_W);
    this->setTabOrder(ui->pB_Send_W, ui->lE_Slave_R);
    this->setTabOrder(ui->lE_Slave_R, ui->lE_Registor_R);
    this->setTabOrder(ui->lE_Registor_R, ui->lE_Data_R);
    this->setTabOrder(ui->lE_Data_R, ui->pB_Send_R);

    connect(ui->action, &QAction::triggered, this, &MainWindow::SettingsUI_Show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SettingsUI_Show(void)
{
    s->show();
}

void MainWindow::on_pB_Send_W_clicked()
{
    ctx = modbus_new_rtu(s->serial.name, s->serial.baudRate, s->serial.parity,\
                         s->serial.dataBits, s->serial.stopBits);

    if (modbus_connect(ctx) == -1) {
         QMessageBox::information(this,tr("打开串口失败"),tr("打开串口失败"),QMessageBox::Yes);
         modbus_free(ctx);
         return;
    }

    modbus_set_slave(ctx, ui->lE_Slave_W->text().toInt());

    if (modbus_write_register(ctx, ui->lE_Registor_W->text().toInt(), ui->lE_Data_W->text().toInt()) == 1)
    {
        modbus_close(ctx);
        modbus_free(ctx);
        QMessageBox::information(this,tr("写入成功"),tr("写入成功"),QMessageBox::Yes);
    }
    else
    {
        modbus_close(ctx);
        modbus_free(ctx);
        QMessageBox::information(this,tr("写入失败"),tr("写入失败"),QMessageBox::Yes);
    }
}

void MainWindow::on_pB_Send_R_clicked()
{
    uint16_t dest[100] = {0};

    qDebug()<<s->serial.name;

    ctx = modbus_new_rtu(s->serial.name, s->serial.baudRate, s->serial.parity,\
                         s->serial.dataBits, s->serial.stopBits);

    if (modbus_connect(ctx) == -1) {
         QMessageBox::information(this,tr("打开串口失败"),tr("打开串口失败"),QMessageBox::Yes);
         modbus_free(ctx);
         return;
    }

    modbus_set_slave(ctx, ui->lE_Slave_R->text().toInt());

    if (modbus_read_input_registers(ctx, ui->lE_Registor_R->text().toInt(), ui->lE_Data_R->text().toInt(), dest)\
                            == ui->lE_Data_R->text().toInt())
    {
        QString ret_data = tr("数据:");
        for(int i=0; i<ui->lE_Data_R->text().toInt(); i++)
        {
            ret_data += QString("%1 ").arg(dest[i]);
        }

        modbus_close(ctx);
        modbus_free(ctx);

        QMessageBox::information(this,tr("读取成功"),ret_data,QMessageBox::Yes);

        qDebug()<<"从机地址"<<ui->lE_Slave_R->text().toInt()\
                <<"寄存器地址"<<ui->lE_Registor_R->text().toInt()\
                <<"个数"<<ui->lE_Data_R->text().toInt()\
                <<ret_data;
    }
    else
    {
        modbus_close(ctx);
        modbus_free(ctx);
        QMessageBox::information(this,tr("读取失败"),tr("读取失败"),QMessageBox::Yes);
    }
}
