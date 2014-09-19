#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmodbus.h"
#include "qmodbusmaster.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Modbus::QModbusMaster * modbus;
};

#endif // MAINWINDOW_H
