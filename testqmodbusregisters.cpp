#include "testqmodbusregisters.h"
#include "qmodbusregisters.h"

#include <QtTest/QTest>
#include <QDebug>
#include <cfloat>

void TestQModbusRegisters::testGetValue ()
{
    Modbus::QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getValue (3), (quint16)0);
}

void TestQModbusRegisters::testGetNumber ()
{
    Modbus::QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getNumber (), (unsigned int)16);
}

void TestQModbusRegisters::testGetAddress ()
{
    Modbus::QModbusRegisters registers (4, 16);
    QCOMPARE (registers.getAddress (), (unsigned int)4);
}

void TestQModbusRegisters::testSetAndGetValue ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setValue (8,  0U);
    QCOMPARE (registers.getValue (8), (quint16)0);
    registers.setValue (8,  32767U);
    QCOMPARE (registers.getValue (8), (quint16)32767U);
    registers.setValue (8,  65535U);
    QCOMPARE (registers.getValue (8), (quint16)65535U);
}

void TestQModbusRegisters::testSetAndGetNumber ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setNumber (8);
    QCOMPARE (registers.getNumber (), (unsigned int)8);
    registers.setNumber (32);
    QCOMPARE (registers.getNumber (), (unsigned int)32);
}

void TestQModbusRegisters::testSetAndGetAddress ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setAddress (8);
    QCOMPARE (registers.getAddress (), (unsigned int)8);
    registers.setAddress (16);
    QCOMPARE (registers.getAddress (), (unsigned int)16);
}

void TestQModbusRegisters::testGetBitString ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getBitString (8), QString ("0000000000000000"));
    registers.setValue (8,  (quint16)32767);
    QCOMPARE (registers.getBitString (8), QString ("0111111111111111"));
    registers.setValue (8,  (quint16)0xffff);
    QCOMPARE (registers.getBitString (8), QString ("1111111111111111"));
}

void TestQModbusRegisters::testGetInteger16 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger16 (8), (short int)0);
}

void TestQModbusRegisters::testGetInteger32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger32 (8), (int)0);
}

void TestQModbusRegisters::testGetInteger64 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getInteger64 (8), (long long int)0);
}

void TestQModbusRegisters::testSetAndGetInteger16 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setInteger16(8, -32768);
    QCOMPARE (registers.getInteger16 (8), (short int)-32768);
    registers.setInteger16(8, 0);
    QCOMPARE (registers.getInteger16 (8), (short int)0);
    registers.setInteger16(8, 32767);
    QCOMPARE (registers.getInteger16 (8), (short int)32767);
}

void TestQModbusRegisters::testSetAndGetInteger32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setInteger32(8, -2147483647);
    QCOMPARE (registers.getInteger32 (8), (int)-2147483647);
    registers.setInteger32(8, 0);
    QCOMPARE (registers.getInteger32 (8), (int)0);
    registers.setInteger32(8, 2147483647);
    QCOMPARE (registers.getInteger32 (8), (int)2147483647);
}

void TestQModbusRegisters::testSetAndGetInteger64 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setInteger64(8, -9223372036854775807LL);
    QCOMPARE (registers.getInteger64 (8), (long long int)-9223372036854775807LL);
    registers.setInteger64(8, 0);
    QCOMPARE (registers.getInteger64 (8), (long long int)0);
    registers.setInteger64(8, 9223372036854775807LL);
    QCOMPARE (registers.getInteger64 (8), (long long int)9223372036854775807LL);
}

void TestQModbusRegisters::testGetUInteger16 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger16 (8), (short unsigned int)0);
}

void TestQModbusRegisters::testGetUInteger32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger32 (8), (unsigned int)0);
}

void TestQModbusRegisters::testGetUInteger64 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getUInteger64 (8), (long long unsigned int)0);
}

void TestQModbusRegisters::testSetAndGetUInteger16 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setUInteger16(8, 0);
    QCOMPARE (registers.getUInteger16 (8), (short unsigned int)0);
    registers.setUInteger16(8, 32767U);
    QCOMPARE (registers.getUInteger16 (8), (short unsigned int)32767U);
    registers.setUInteger16(8, 65535U);
    QCOMPARE (registers.getUInteger16 (8), (short unsigned int)65535U);
}

void TestQModbusRegisters::testSetAndGetUInteger32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setUInteger32(8, 0);
    QCOMPARE (registers.getUInteger32 (8), (unsigned int)0);
    registers.setUInteger32(8, 2147483647U);
    QCOMPARE (registers.getUInteger32 (8), (unsigned int)2147483647U);
    registers.setUInteger32(8, 4294967295U);
    QCOMPARE (registers.getUInteger32 (8), (unsigned int)4294967295U);
}

void TestQModbusRegisters::testSetAndGetUInteger64 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setUInteger64(8, 0);
    QCOMPARE (registers.getUInteger64 (8), (long long unsigned int)0);
    registers.setUInteger64(8, (long long unsigned int)9223372036854775807ULL);
    QCOMPARE (registers.getUInteger64 (8), (long long unsigned int)9223372036854775807ULL);
    registers.setUInteger64(8, (long long unsigned int)18446744073709551615ULL);
    QCOMPARE (registers.getUInteger64 (8), (long long unsigned int)18446744073709551615ULL);
}

void TestQModbusRegisters::testGetFloat32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getFloat32 (8), (float)0);
}

void TestQModbusRegisters::testGetFloat64 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getFloat64 (8), (double)0);
}

void TestQModbusRegisters::testGetFloat96 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    QCOMPARE (registers.getFloat96 (8), (long double)0);
}

void TestQModbusRegisters::testSetAndGetFloat32 ()
{
    Modbus::QModbusRegisters registers (0, 16);
    registers.setFloat32(8, FLT_MIN);
    QCOMPARE (registers.getFloat32 (8), (float)FLT_MIN);
    registers.setFloat32(8, 0);
    QCOMPARE (registers.getFloat32 (8), (float)0);
    registers.setFloat32(8, FLT_MAX);
    QCOMPARE (registers.getFloat32 (8), (float)FLT_MAX);
}

void TestQModbusRegisters::testSetAndGetFloat64 ()
{
    Modbus::QModbusRegisters registers (0, 12);
    registers.setFloat64(8, DBL_MIN);
    QCOMPARE (registers.getFloat64 (8), (double)DBL_MIN);
    registers.setFloat64(8, 0);
    QCOMPARE (registers.getFloat64 (8), (double)0);
    registers.setFloat64(8, DBL_MAX);
    QCOMPARE (registers.getFloat64 (8), (double)DBL_MAX);
}

void TestQModbusRegisters::testSetAndGetFloat96 ()
{
    Modbus::QModbusRegisters registers (0, 14);
    registers.setFloat96(8, LDBL_MIN);
    QCOMPARE (registers.getFloat96 (8), (long double)LDBL_MIN);
    registers.setFloat96(8, 0);
    QCOMPARE (registers.getFloat96 (8), (long double)0);
    registers.setFloat96(8, LDBL_MAX);
    QCOMPARE (registers.getFloat96 (8), (long double)LDBL_MAX);
}
