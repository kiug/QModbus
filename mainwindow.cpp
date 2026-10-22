/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include <QMessageBox>
#include <QTableWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmodbusregisters.h"
#include "qmodbusbits.h"

using namespace Modbus;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modbus(nullptr)
{
    ui->setupUi(this);

    connect(ui->tcpConnectPushButton, &QPushButton::clicked, this, &MainWindow::connectToDevice);
    connect(ui->rtuConnectPushButton, &QPushButton::clicked, this, &MainWindow::connectToDevice);
    connect(ui->sendQueryPushButton, &QPushButton::clicked, this, &MainWindow::sendQuery);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToDevice()
{
    if (modbus) {
        modbus->close();
        delete modbus;
        modbus = nullptr;
    }

    if (ui->connectionTabWidget->currentIndex() == 0) {
        // TCP
        const QString ip = QString("%1.%2.%3.%4")
            .arg(ui->ipOct1LineEdit->text())
            .arg(ui->ipOct2LineEdit->text())
            .arg(ui->ipOct3LineEdit->text())
            .arg(ui->ipOct4LineEdit->text());
        const int port = ui->portLineEdit->text().toInt();
        const QByteArray ipBytes = ip.toLatin1();
        modbus = new QModbusMaster(ipBytes.constData(), port, this);
    }
    else {
        // RTU
        const char parity = "NEO"[ui->parityComboBox->currentIndex()];
        const QByteArray device = ui->serialPortLineEdit->text().toLatin1();
        modbus = new QModbusMaster(
            device.constData(),
            ui->baudComboBox->currentText().toInt(),
            parity,
            ui->dataBitsComboBox->currentText().toInt(),
            ui->oneRadioButton->isChecked() ? 1 : 2,
            this);
    }

    if (!modbus->connect()) {
        QMessageBox::warning(this, "QModbus", modbus->lastError().message());
    }
}

void MainWindow::sendQuery()
{
    if (!modbus) {
        QMessageBox::warning(this, "QModbus", "Not connected");
        return;
    }

    const int address = ui->addressSpinBox->value();
    const int number = qMin(ui->numberSpinBox->value(), 125);

    ui->resultTableWidget->clear();
    ui->resultTableWidget->setRowCount(0);
    ui->resultTableWidget->setColumnCount(2);
    ui->resultTableWidget->setHorizontalHeaderLabels(QStringList() << "Address" << "Value");

    bool ok = false;
    switch (ui->functionComboBox->currentIndex()) {
    case 0: { // Read bits (01/0x01)
        QModbusBits bits(address, number);
        ok = modbus->readBits(bits);
        for (int i = 0; ok && i < number; ++i) {
            addResultRow(address + i, bits.getValue(i) ? "1" : "0");
        }
        break;
    }
    case 1: { // Read input bits (02/0x02)
        QModbusBits bits(address, number);
        ok = modbus->readInputBits(bits);
        for (int i = 0; ok && i < number; ++i) {
            addResultRow(address + i, bits.getValue(i) ? "1" : "0");
        }
        break;
    }
    case 2: { // Read registers (03/0x03)
        QModbusRegisters regs(address, number);
        ok = modbus->readRegisters(regs);
        for (int i = 0; ok && i < number; ++i) {
            addResultRow(address + i, QString::number(regs.getValue(i)));
        }
        break;
    }
    case 3: { // Read input registers (04/0x04)
        QModbusRegisters regs(address, number);
        ok = modbus->readInputRegisters(regs);
        for (int i = 0; ok && i < number; ++i) {
            addResultRow(address + i, QString::number(regs.getValue(i)));
        }
        break;
    }
    default:
        // Write functions require a value input, which this UI does not provide.
        ui->statusBar->showMessage("Write functions need a value input (not implemented)");
        return;
    }

    if (!ok) {
        QMessageBox::warning(this, "QModbus", modbus->lastError().message());
    }
}

void MainWindow::addResultRow(int address, const QString &value)
{
    const int row = ui->resultTableWidget->rowCount();
    ui->resultTableWidget->insertRow(row);
    ui->resultTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(address)));
    ui->resultTableWidget->setItem(row, 1, new QTableWidgetItem(value));
}
