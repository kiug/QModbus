/****************************************************************************
**
** SPDX-License-Identifier: GPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include "testqmodbusbits.h"
#include "qmodbusbits.h"

#include <QtTest/QTest>

void TestQModbusBits::testGetValue ()
{
    Modbus::QModbusBits bits (4, 16);
    QCOMPARE (bits.getValue (3), false);
}

void TestQModbusBits::testGetNumber ()
{
    Modbus::QModbusBits bits (4, 16);
    QCOMPARE (bits.getNumber (), (unsigned int)16);
}

void TestQModbusBits::testGetAddress ()
{
    Modbus::QModbusBits bits (4, 16);
    QCOMPARE (bits.getAddress (), (unsigned int)4);
}

void TestQModbusBits::testSetAndGetValue ()
{
    Modbus::QModbusBits bits (0, 16);
    bits.setValue (8, true);
    QCOMPARE (bits.getValue (8), true);
    bits.setValue (8, false);
    QCOMPARE (bits.getValue (8), false);
}

void TestQModbusBits::testSetAndGetNumber ()
{
    Modbus::QModbusBits bits (0, 16);
    bits.setNumber (8);
    QCOMPARE (bits.getNumber (), (unsigned int)8);
    bits.setNumber (32);
    QCOMPARE (bits.getNumber (), (unsigned int)32);
}

void TestQModbusBits::testSetAndGetAddress ()
{
    Modbus::QModbusBits bits (0, 16);
    bits.setAddress (8);
    QCOMPARE (bits.getAddress (), (unsigned int)8);
    bits.setAddress (16);
    QCOMPARE (bits.getAddress (), (unsigned int)16);
}
