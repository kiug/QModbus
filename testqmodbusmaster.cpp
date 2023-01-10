/****************************************************************************
**
** SPDX-License-Identifier: GPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include "testqmodbusmaster.h"
#include "qmodbusmaster.h"

#include <QtTest/QTest>
#include <QDebug>

#include <limits>

using namespace Modbus;

TestQModbusMaster::TestQModbusMaster (QObject *parent) : QObject (parent)
{
    bits.setAddress (0);
    bits.setNumber (16);

    bits.setValue (0, true);
    bits.setValue (1, true);
    bits.setValue (2, true);
    bits.setValue (3, true);
    bits.setValue (4, false);
    bits.setValue (5, false);
    bits.setValue (6, true);
    bits.setValue (7, false);
    bits.setValue (8, true);
    bits.setValue (9, true);
    bits.setValue (10, true);
    bits.setValue (11, true);
    bits.setValue (12, false);
    bits.setValue (13, false);
    bits.setValue (14, true);
    bits.setValue (15, false);

    regs.setAddress (0);
    regs.setNumber (50);

    regs.setInteger16 (0, std::numeric_limits<qint16>::min());
    regs.setInteger16 (1, 0);
    regs.setInteger16 (2, std::numeric_limits<qint16>::max());

    regs.setInteger32 (3, std::numeric_limits<qint32>::min());
    regs.setInteger32 (5, 0);
    regs.setInteger32 (7, std::numeric_limits<qint32>::max());

    regs.setInteger64 (9, std::numeric_limits<qint64>::min());
    regs.setInteger64 (13, 0);
    regs.setInteger64 (17, std::numeric_limits<qint64>::max());

    regs.setUInteger16 (21, std::numeric_limits<quint16>::min());
    regs.setUInteger16 (22, std::numeric_limits<quint16>::max());

    regs.setUInteger32 (23, std::numeric_limits<quint32>::min());
    regs.setUInteger32 (25, std::numeric_limits<quint32>::max());

    regs.setUInteger64 (29, std::numeric_limits<quint64>::min());
    regs.setUInteger64 (33, std::numeric_limits<quint64>::max());

    regs.setFloat32 (37, std::numeric_limits<float>::min());
    regs.setFloat32 (39, std::numeric_limits<float>::max());

    regs.setFloat64 (41, std::numeric_limits<double>::min());
    regs.setFloat64 (45, std::numeric_limits<double>::max());
}

TestQModbusMaster::~TestQModbusMaster ()
{
    modbus->close();
}

void TestQModbusMaster::testConstructor ()
{
    modbus = new QModbusMaster (IP, PORT, this);
    QCOMPARE (modbus->lastError ().isValid (), false);
    modbus->setDebug (true);
}

void TestQModbusMaster::testSetBroadcast ()
{
    modbus->setBroadcast ();
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testSetSlave ()
{
    modbus->setSlave (1);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testConnection ()
{
    modbus->connect ();
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testWriteBit ()
{
    modbus->writeBit (bits);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testWriteRegister ()
{
    modbus->writeRegister (regs);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testWriteBits ()
{
    modbus->writeBits (bits);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testWriteRegisters ()
{
    modbus->writeRegisters (regs);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testReadBits ()
{
    QModbusBits bits (0, 18);
    modbus->readBits (bits);
    QCOMPARE (modbus->lastError ().isValid (), false);
    qDebug()
            << bits.getValue (0)
            << bits.getValue (1)
            << bits.getValue (2)
            << bits.getValue (3)
            << bits.getValue (4)
            << bits.getValue (5)
            << bits.getValue (6)
            << bits.getValue (7)
            << bits.getValue (8)
            << bits.getValue (9)
            << bits.getValue (10)
            << bits.getValue (11)
            << bits.getValue (12)
            << bits.getValue (13)
            << bits.getValue (14)
            << bits.getValue (15)
            << bits.getValue (16)
            << bits.getValue (17);
    QCOMPARE (bits.getValue (0), true);
    QCOMPARE (bits.getValue (1), true);
    QCOMPARE (bits.getValue (2), true);
    QCOMPARE (bits.getValue (3), true);
    QCOMPARE (bits.getValue (4), false);
    QCOMPARE (bits.getValue (5), false);
    QCOMPARE (bits.getValue (6), true);
    QCOMPARE (bits.getValue (7), false);
    QCOMPARE (bits.getValue (8), true);
    QCOMPARE (bits.getValue (9), true);
    QCOMPARE (bits.getValue (10), true);
    QCOMPARE (bits.getValue (11), true);
    QCOMPARE (bits.getValue (12), false);
    QCOMPARE (bits.getValue (13), false);
    QCOMPARE (bits.getValue (14), true);
    QCOMPARE (bits.getValue (15), false);
    QCOMPARE (bits.getValue (16), false);
    QCOMPARE (bits.getValue (17), false);
}

void TestQModbusMaster::testReadInputBits ()
{
    QModbusBits bits (0, 8);
    modbus->readInputBits (bits);
    QCOMPARE (modbus->lastError ().isValid (), false);
    qDebug()
            << bits.getValue (0)
            << bits.getValue (1)
            << bits.getValue (2)
            << bits.getValue (3)
            << bits.getValue (4)
            << bits.getValue (5)
            << bits.getValue (6)
            << bits.getValue (7);
    QCOMPARE (bits.getValue (0), false);
    QCOMPARE (bits.getValue (1), false);
    QCOMPARE (bits.getValue (2), false);
    QCOMPARE (bits.getValue (3), false);
    QCOMPARE (bits.getValue (4), false);
    QCOMPARE (bits.getValue (5), false);
    QCOMPARE (bits.getValue (6), false);
    QCOMPARE (bits.getValue (7), false);
}

void TestQModbusMaster::testReadRegisters ()
{
    QModbusRegisters regs (0, 51);
    modbus->readRegisters (regs);
    QCOMPARE (modbus->lastError ().isValid (), false);
    for (int i = 0; i < 51; ++i)
    {
        qDebug() << i << regs.getBitString (i);
    }

    QCOMPARE (regs.getInteger16 (0), std::numeric_limits<qint16>::min());
    QCOMPARE (regs.getInteger16 (1), (qint16)0);
    QCOMPARE (regs.getInteger16 (2), std::numeric_limits<qint16>::max());

    QCOMPARE (regs.getInteger32 (3), std::numeric_limits<qint32>::min());
    QCOMPARE (regs.getInteger32 (5), (qint32)0);
    QCOMPARE (regs.getInteger32 (7), std::numeric_limits<qint32>::max());

    QCOMPARE (regs.getInteger64 (9), std::numeric_limits<qint64>::min());
    QCOMPARE (regs.getInteger64 (13), (qint64)0);
    QCOMPARE (regs.getInteger64 (17), std::numeric_limits<qint64>::max());

    QCOMPARE (regs.getUInteger16 (21), std::numeric_limits<quint16>::min());
    QCOMPARE (regs.getUInteger16 (22), std::numeric_limits<quint16>::max());

    QCOMPARE (regs.getUInteger32 (23), std::numeric_limits<quint32>::min());
    QCOMPARE (regs.getUInteger32 (25), std::numeric_limits<quint32>::max());

    QCOMPARE (regs.getUInteger64 (29), std::numeric_limits<quint64>::min());
    QCOMPARE (regs.getUInteger64 (33), std::numeric_limits<quint64>::max());

    QCOMPARE (regs.getFloat32 (37), std::numeric_limits<float>::min());
    QCOMPARE (regs.getFloat32 (39), std::numeric_limits<float>::max());

    QCOMPARE (regs.getFloat64 (41), std::numeric_limits<double>::min());
    QCOMPARE (regs.getFloat64 (45), std::numeric_limits<double>::max());

    QCOMPARE (regs.getValue (49), (quint16)0);
    QCOMPARE (regs.getValue (50), (quint16)0);
}

void TestQModbusMaster::testReadInputRegisters ()
{
    QModbusRegisters regs (0, 8);
    modbus->readInputRegisters (regs);
    QCOMPARE (modbus->lastError ().isValid (), false);
    for (int i = 0; i < 8; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    QCOMPARE (regs.getValue (0), (quint16)0);
    QCOMPARE (regs.getValue (1), (quint16)0);
    QCOMPARE (regs.getValue (2), (quint16)0);
    QCOMPARE (regs.getValue (3), (quint16)0);
    QCOMPARE (regs.getValue (4), (quint16)0);
    QCOMPARE (regs.getValue (5), (quint16)0);
    QCOMPARE (regs.getValue (6), (quint16)0);
    QCOMPARE (regs.getValue (7), (quint16)0);
}

void TestQModbusMaster::testReportSlaveId ()
{
    //quint8 dest;
    //modbus->reportSlaveId (&dest);
    QCOMPARE (modbus->lastError ().isValid (), false);
}

void TestQModbusMaster::testFlush ()
{
    modbus->flush ();
    QCOMPARE (modbus->lastError ().isValid (), false);
}
