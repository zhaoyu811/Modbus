#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include <libmodbus/libmodbus.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void SettingsUI_Show(void);

    void on_pB_Send_W_clicked();

    void on_pB_Send_R_clicked();

private:
    Ui::MainWindow *ui;
    settings *s;
    modbus_t *ctx;
};

#endif // MAINWINDOW_H
