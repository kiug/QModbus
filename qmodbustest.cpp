/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

/*
** To run this tests MOD_RSSIM (http://www.plcsimulator.org/) is required
**/

#include "testqmodbusbits.h"
#include "testqmodbusregisters.h"
#include "testqmodbuserror.h"
#include "testqmodbusmaster.h"

#include <QtTest/QTest>
#include <QDebug>

int main (int argc, char *argv[])
{
    Q_UNUSED (argc);
    Q_UNUSED (argv);
    TestQModbusBits testQModbusBits;
    QTest::qExec (&testQModbusBits);
    TestQModbusRegisters testQModbusRegisters;
    QTest::qExec (&testQModbusRegisters);
    TestQModbusError testQModbusError;
    QTest::qExec (&testQModbusError);
    TestQModbusMaster testQModbusMaster;
    QTest::qExec (&testQModbusMaster);

    return 0;
}

//QTEST_MAIN(TestQModbusBits);
