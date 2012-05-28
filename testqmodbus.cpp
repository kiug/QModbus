#include "testqmodbus.h"
#include "qmodbus.h"

#include <QtTest/QTest>
#include <QDebug>

using namespace Modbus;

TestQModbus::TestQModbus(QObject *parent) : QObject(parent)
{
}

void TestQModbus::testConnection ()
{
    QModbus modbus (IP, PORT);
    modbus.setDebug (true);
    modbus.connect ();
    modbus.close();
}

void TestQModbus::bitsTest ()
{
    QModbus modbus (IP, PORT);
    modbus.setDebug (true);
    qDebug() << "Connecting...";
    modbus.connect ();

    // test readBits
    QModbusBits bits (0, 8);
    modbus.readBits (bits);
    qDebug()
            << bits.getValue (0)
            << bits.getValue (1)
            << bits.getValue (2)
            << bits.getValue (3)
            << bits.getValue (4)
            << bits.getValue (5)
            << bits.getValue (6)
            << bits.getValue (7);

    // realocate vector memory and then test readBits
    bits.setNumber (32);
    modbus.readBits (bits);
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
            << bits.getValue (17)
            << bits.getValue (18)
            << bits.getValue (19)
            << bits.getValue (20)
            << bits.getValue (21)
            << bits.getValue (22)
            << bits.getValue (23)
            << bits.getValue (24)
            << bits.getValue (25)
            << bits.getValue (26)
            << bits.getValue (27)
            << bits.getValue (28)
            << bits.getValue (29)
            << bits.getValue (30)
            << bits.getValue (31);

    // test writeBits
    bits.setValue(30, !bits.getValue (30)); // invert bit 30 value
    modbus.writeBits (bits);
    modbus.readBits (bits);
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
            << bits.getValue (17)
            << bits.getValue (18)
            << bits.getValue (19)
            << bits.getValue (20)
            << bits.getValue (21)
            << bits.getValue (22)
            << bits.getValue (23)
            << bits.getValue (24)
            << bits.getValue (25)
            << bits.getValue (26)
            << bits.getValue (27)
            << bits.getValue (28)
            << bits.getValue (29)
            << bits.getValue (30)
            << bits.getValue (31);

    // test writeBit
    QModbusBits bit (0);
    bit.setValue(0, !bits.getValue (0));
    modbus.writeBit (bit);
    modbus.readBits (bit);
    qDebug() << "FIRST bit " << bit.getValue (0);

    // test readInputsBits
    bits.setAddress(0);
    bits.setNumber(16);
    modbus.readInputBits (bits);
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
            << bits.getValue (15);

    modbus.close();
}

void TestQModbus::registersTest ()
{
    QModbus modbus (IP, PORT);
    modbus.setDebug (true);
    modbus.connect ();

    // test readRegisters
    QModbusRegisters regs (0, 8);
    modbus.readRegisters (regs);
    for (int i = 0; i < 8; ++i)
    {
        qDebug() << regs.getBitString (i);
    }

    // test readInputRegisters
    regs.setNumber (16);
    modbus.readInputRegisters (regs);
    for (int i = 0; i < 16; ++i)
    {
        qDebug() << regs.getBitString (i);
    }

    // test writeRegister
    QModbusRegisters reg (0);
    modbus.readRegisters (reg);
    qDebug() << regs.getBitString (0);
    reg.setValue (0, reg.getValue (0));
    modbus.writeRegister (reg);
    modbus.readRegisters (reg);
    qDebug() << regs.getBitString (0);

    // test writeRegisters
    regs.setNumber(2);
    modbus.readRegisters (regs);
    for (int i = 0; i < 2; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    regs.setFloat32 (0, 916.540649);
    modbus.writeRegisters (regs);
    modbus.readRegisters (regs);
    for (int i = 0; i < 2; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    //std::cout.precision(9);
    qDebug() << regs.getFloat32(0);

    // test writeRegisters Integer32
    regs.setAddress(2);
    regs.setNumber(2);
    modbus.readRegisters (regs);
    for (int i = 0; i < 2; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    regs.setInteger32 (0, 64);
    modbus.writeRegisters (regs);
    modbus.readRegisters (regs);
    for (int i = 0; i < 2; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    qDebug() << regs.getInteger32(0);

    // test writeRegisters Integer64
    regs.setAddress(4);
    regs.setNumber(4);
    modbus.readRegisters (regs);
    for (int i = 0; i < 4; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    regs.setInteger64 (0, (long long int)-9223372036854775807LL);
    for (int i = 0; i < 4; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    modbus.writeRegisters (regs);
    modbus.readRegisters (regs);
    QCOMPARE (regs.getInteger64 (0), (long long int)-9223372036854775807LL);

    // test writeRegisters UInteger64
    regs.setAddress(8);
    regs.setNumber(4);
    qDebug() << regs.getAddress() << regs.getNumber() << regs.size();
    modbus.readRegisters (regs);
    for (int i = 0; i < 4; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    regs.setUInteger64 (0, (long long unsigned int)18446744073709551615ULL);
    modbus.writeRegisters (regs);
    modbus.readRegisters (regs);
    for (int i = 0; i < 4; ++i)
    {
        qDebug() << regs.getBitString (i);
    }
    QCOMPARE (regs.getUInteger64 (0), (long long unsigned int)18446744073709551615ULL);

    modbus.close();
}
