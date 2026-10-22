/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include "testqmodbusregisters.h"
#include "qmodbusregisters.h"

#include <QtTest/QTest>
#include <QDebug>
#include <cfloat>

using namespace Modbus;

void TestQModbusRegisters::testGetValue ()
{
    QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getValue (3), (quint16)0);
}

void TestQModbusRegisters::testGetNumber ()
{
    QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getNumber (), (unsigned int)16);
}

void TestQModbusRegisters::testGetAddress ()
{
    QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getAddress (), (unsigned int)4);
}

void TestQModbusRegisters::testSetAndGetValue ()
{
    QModbusRegisters registers (0, 16);
    registers.setValue (8,  0U);
    QCOMPARE (registers.getValue (8), (quint16)0);
    registers.setValue (8,  32767U);
    QCOMPARE (registers.getValue (8), (quint16)32767U);
    registers.setValue (8,  65535U);
    QCOMPARE (registers.getValue (8), (quint16)65535U);
}

void TestQModbusRegisters::testSetAndGetNumber ()
{
    QModbusRegisters registers (0, 16);
    registers.setNumber (8);
    QCOMPARE (registers.getNumber (), (unsigned int)8);
    registers.setNumber (32);
    QCOMPARE (registers.getNumber (), (unsigned int)32);
}

void TestQModbusRegisters::testSetAndGetAddress ()
{
    QModbusRegisters registers (0, 16);
    registers.setAddress (8);
    QCOMPARE (registers.getAddress (), (unsigned int)8);
    registers.setAddress (16);
    QCOMPARE (registers.getAddress (), (unsigned int)16);
}

void TestQModbusRegisters::testGetBitString ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getBitString (8), QString ("0000000000000000"));
    registers.setValue (8,  (quint16)32767);
    QCOMPARE (registers.getBitString (8), QString ("0111111111111111"));
    registers.setValue (8,  (quint16)0xffff);
    QCOMPARE (registers.getBitString (8), QString ("1111111111111111"));
}

void TestQModbusRegisters::testGetInteger16 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger16 (8), (qint16)0);
}

void TestQModbusRegisters::testGetInteger32 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger32 (8), (qint32)0);
}

void TestQModbusRegisters::testGetInteger64 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger64 (8), (qint64)0);
}

void TestQModbusRegisters::testSetAndGetInteger16 ()
{
    QModbusRegisters registers (0, 16);
    registers.setInteger16(8, -32768);
    QCOMPARE (registers.getInteger16 (8), (qint16)-32768);
    registers.setInteger16(8, 0);
    QCOMPARE (registers.getInteger16 (8), (qint16)0);
    registers.setInteger16(8, 32767);
    QCOMPARE (registers.getInteger16 (8), (qint16)32767);
}

void TestQModbusRegisters::testSetAndGetInteger32 ()
{
    QModbusRegisters registers (0, 16);
    registers.setInteger32 (8, -2147483647);
    QCOMPARE (registers.getInteger32 (8), (qint32)-2147483647);
    registers.setInteger32 (8, 0);
    QCOMPARE (registers.getInteger32 (8), (qint32)0);
    registers.setInteger32 (8, 2147483647);
    QCOMPARE (registers.getInteger32 (8), (qint32)2147483647);
}

void TestQModbusRegisters::testSetAndGetInteger64 ()
{
    QModbusRegisters registers (0, 16);
    registers.setInteger64 (8, -9223372036854775807LL);
    QCOMPARE (registers.getInteger64 (8), (qint64)-9223372036854775807LL);
    registers.setInteger64 (8, 0);
    QCOMPARE (registers.getInteger64 (8), (qint64)0);
    registers.setInteger64 (8, 9223372036854775807LL);
    QCOMPARE (registers.getInteger64 (8), (qint64)9223372036854775807LL);
}

void TestQModbusRegisters::testGetUInteger16 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger16 (8), (quint16)0);
}

void TestQModbusRegisters::testGetUInteger32 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger32 (8), (quint32)0);
}

void TestQModbusRegisters::testGetUInteger64 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger64 (8), (quint64)0);
}

void TestQModbusRegisters::testSetAndGetUInteger16 ()
{
    QModbusRegisters registers (0, 16);
    registers.setUInteger16 (8, 0);
    QCOMPARE (registers.getUInteger16 (8), (quint16)0);
    registers.setUInteger16 (8, 32767U);
    QCOMPARE (registers.getUInteger16 (8), (quint16)32767U);
    registers.setUInteger16 (8, 65535U);
    QCOMPARE (registers.getUInteger16 (8), (quint16)65535U);
}

void TestQModbusRegisters::testSetAndGetUInteger32 ()
{
    QModbusRegisters registers (0, 16);
    registers.setUInteger32 (8, 0);
    QCOMPARE (registers.getUInteger32 (8), (quint32)0);
    registers.setUInteger32 (8, 2147483647U);
    QCOMPARE (registers.getUInteger32 (8), (quint32)2147483647U);
    registers.setUInteger32 (8, 4294967295U);
    QCOMPARE (registers.getUInteger32 (8), (quint32)4294967295U);
}

void TestQModbusRegisters::testSetAndGetUInteger64 ()
{
    QModbusRegisters registers (0, 16);
    registers.setUInteger64 (8, 0);
    QCOMPARE (registers.getUInteger64 (8), (quint64)0);
    registers.setUInteger64 (8, (quint64)9223372036854775807ULL);
    QCOMPARE (registers.getUInteger64 (8), (quint64)9223372036854775807ULL);
    registers.setUInteger64 (8, (quint64)18446744073709551615ULL);
    QCOMPARE (registers.getUInteger64 (8), (quint64)18446744073709551615ULL);
}

void TestQModbusRegisters::testGetFloat32 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getFloat32 (8), (float)0);
}

void TestQModbusRegisters::testGetFloat64 ()
{
    QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getFloat64 (8), (double)0);
}

void TestQModbusRegisters::testSetAndGetFloat32 ()
{
    QModbusRegisters registers (0, 16);
    registers.setFloat32 (8, FLT_MIN);
    QCOMPARE (registers.getFloat32 (8), (float)FLT_MIN);
    registers.setFloat32 (8, 0);
    QCOMPARE (registers.getFloat32 (8), (float)0);
    registers.setFloat32 (8, FLT_MAX);
    QCOMPARE (registers.getFloat32 (8), (float)FLT_MAX);
}

void TestQModbusRegisters::testSetAndGetFloat64 ()
{
    QModbusRegisters registers (0, 12);
    registers.setFloat64 (8, DBL_MIN);
    QCOMPARE (registers.getFloat64 (8), (double)DBL_MIN);
    registers.setFloat64 (8, 0);
    QCOMPARE (registers.getFloat64 (8), (double)0);
    registers.setFloat64 (8, DBL_MAX);
    QCOMPARE (registers.getFloat64 (8), (double)DBL_MAX);
}

void TestQModbusRegisters::testSetFloat32RegisterOrder ()
{
    QModbusRegisters registers (0, 16);
    registers.setFloat32 (8, 1.0f);
    QCOMPARE (registers.getValue (8), (quint16)0x3F80);
    QCOMPARE (registers.getValue (9), (quint16)0x0000);
    registers.setFloat32 (8, 20.1f);
    QCOMPARE (registers.getValue (8), (quint16)0x41A0);
    QCOMPARE (registers.getValue (9), (quint16)0xCCCD);
}

void TestQModbusRegisters::testGetFloat32RegisterOrder ()
{
    QModbusRegisters registers (0, 16);
    registers.setValue (8, 0x3F80);
    registers.setValue (9, 0x0000);
    QCOMPARE (registers.getFloat32 (8), 1.0f);
    registers.setValue (8, 0x41A0);
    registers.setValue (9, 0xCCCD);
    QCOMPARE (registers.getFloat32 (8), 20.1f);
}

void TestQModbusRegisters::testSetUInteger32RegisterOrder ()
{
    QModbusRegisters registers (0, 16);
    registers.setUInteger32 (8, 0x12345678U);
    QCOMPARE (registers.getValue (8), (quint16)0x1234);
    QCOMPARE (registers.getValue (9), (quint16)0x5678);
    QCOMPARE (registers.getUInteger32 (8), (quint32)0x12345678U);
}

void TestQModbusRegisters::testSetFloat64RegisterOrder ()
{
    QModbusRegisters registers (0, 12);
    registers.setFloat64 (8, 1.0);
    QCOMPARE (registers.getValue (8), (quint16)0x3FF0);
    QCOMPARE (registers.getValue (9), (quint16)0x0000);
    QCOMPARE (registers.getValue (10), (quint16)0x0000);
    QCOMPARE (registers.getValue (11), (quint16)0x0000);
}

void TestQModbusRegisters::testOutOfRange ()
{
    QModbusRegisters registers (0, 1);
    QCOMPARE (registers.getInteger16 (1), (qint16)0);
    QCOMPARE (registers.getInteger32 (0), (qint32)0);
    QCOMPARE (registers.getInteger64 (0), (qint64)0);
    QCOMPARE (registers.getUInteger16 (1), (quint16)0);
    QCOMPARE (registers.getUInteger32 (0), (quint32)0);
    QCOMPARE (registers.getUInteger64 (0), (quint64)0);
    QCOMPARE (registers.getFloat32 (0), (float)0);
    QCOMPARE (registers.getFloat64 (0), (double)0);
    registers.setInteger16 (1, 1);
    registers.setInteger32 (0, 1);
    registers.setInteger64 (0, 1);
    registers.setUInteger16 (1, 1);
    registers.setUInteger32 (0, 1);
    registers.setUInteger64 (0, 1);
    registers.setFloat32 (0, 1.0f);
    registers.setFloat64 (0, 1.0);
}

void TestQModbusRegisters::testGetHighAndLowByte ()
{
    QCOMPARE (QModbusRegisters::getHighByte (0x1234), (quint8)0x12);
    QCOMPARE (QModbusRegisters::getLowByte (0x1234), (quint8)0x34);
}

void TestQModbusRegisters::testInt32FromInt16 ()
{
    quint16 data[2] = {0x1234, 0x5678};
    QCOMPARE (QModbusRegisters::getInt32FromInt16 (data, 0), (int)0x12345678);
}

void TestQModbusRegisters::testInt16ToAndFromInt8 ()
{
    quint8 data[2] = {0x12, 0x34};
    QCOMPARE (QModbusRegisters::getInt16FromInt8 (data, 0), (short int)0x1234);

    quint8 dest[2] = {0, 0};
    QModbusRegisters::setInt16ToInt8 (dest, 0, 0x1234);
    QCOMPARE (dest[0], (quint8)0x12);
    QCOMPARE (dest[1], (quint8)0x34);
}

void TestQModbusRegisters::testBitsFromByteAndBytes ()
{
    quint8 dest[8];

    QModbusRegisters::setBitsFromByte (dest, 0, 0x00);
    QCOMPARE (dest[0], (quint8)0);

    QModbusRegisters::setBitsFromByte (dest, 0, 0xFF);
    QCOMPARE (dest[0], (quint8)1);
    QCOMPARE (dest[7], (quint8)1);

    const quint8 bytes[1] = {0x0F};
    QModbusRegisters::setBitsFromBytes (dest, 0, 8, bytes);
    QCOMPARE (dest[0], (quint8)1);
    QCOMPARE (dest[3], (quint8)1);
    QCOMPARE (dest[4], (quint8)0);

    QModbusRegisters::getByteFromBits (dest, 0, 8); // returns void; coverage only
}

void TestQModbusRegisters::testFloatHelpers ()
{
    const quint16 src[2] = {0x3F80, 0x0000}; // 1.0f, big-endian
    QCOMPARE (QModbusRegisters::getFloat (src), 1.0f);

    quint16 dest[2] = {0, 0};
    QModbusRegisters::setFloat (1.0f, dest);
    QCOMPARE (dest[0], (quint16)0x3F80);
    QCOMPARE (dest[1], (quint16)0x0000);
}
