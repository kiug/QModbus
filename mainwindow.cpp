#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qmodbusregisters.h"

using namespace Modbus;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //modbus = new QModbusMaster("127.0.0.1", 502, this);
    //modbus->connect();

    QModbusMaster modbusMaster("127.0.0.1", 502);
    modbusMaster.connect();
    // wektor rejestrow o adresie poczatkowym 0 i dlugosci 4
    QModbusRegisters reg(0, 4);
    // odczyt 4 rejestrow od adresu 0
    modbusMaster.readRegisters(reg);
    if(modbusMaster.lastError().isValid()) {
        qDebug()<<"ERROR"<<modbusMaster.lastError().message();
    }
    else {
        qDebug()<<reg
                <<reg.getBitString(0)
                <<reg.getInteger64(0)
                <<reg.getInteger32(0)
                <<reg.getFloat32(0);
    }
    modbusMaster.close();

    /*
    QModbusMaster modbusMaster("127.0.0.1", 502);
    modbusMaster.connect();
    QModbusRegisters reg(modbusMaster, 0, 4);
    if(!reg.read()) {
        qDebug()<<reg.lastError().text();
    }
    else {
        qDebug()<<reg
                <<reg.getBitString(0)
                <<reg.getInteger64(0)
                <<reg.getInteger32(0)
                <<reg.getFloat32(0);
    }
    modbusMaster.close();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    //modbus->close();
}
