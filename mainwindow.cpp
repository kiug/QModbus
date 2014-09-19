#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Modbus;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modbus = new QModbusMaster ("127.0.0.1", 502, this);
    modbus->connect();
}

MainWindow::~MainWindow()
{
    delete ui;
    modbus->close();
}
