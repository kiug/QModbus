/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef TESTQMODBUSMASTER_H
#define TESTQMODBUSMASTER_H

#include <QObject>
#include "qmodbusmaster.h"

#define IP "127.0.0.1"
#define PORT 502

class TestQModbusMaster : public QObject
{
    Q_OBJECT
public:
    explicit TestQModbusMaster (QObject *parent = 0);
    ~TestQModbusMaster ();

private slots:
    void testConstructor ();
    void testSetBroadcast ();
    void testSetSlave ();
    void testConnection ();

    void testWriteBit ();
    void testWriteRegister ();
    void testWriteBits ();
    void testWriteRegisters ();

    void testReadBits ();
    void testReadInputBits ();
    void testReadRegisters ();
    void testReadInputRegisters ();

    void testReportSlaveId ();
    void testFlush ();
    void testNotConnectedError ();
    void testRtuAndTcpPiConstructors ();
    void testContextSettings ();
    void testConnectionError ();

private:
    Modbus::QModbusMaster * modbus;
    Modbus::QModbusBits bits;
    Modbus::QModbusRegisters regs;
};

#endif // TESTQMODBUSMASTER_H
