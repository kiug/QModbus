/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include "testqmodbuserror.h"
#include "qmodbuserror.h"

#include <QtTest/QTest>

using namespace Modbus;

void TestQModbusError::testIsValid ()
{
    QModbusError modbusError;
    QCOMPARE (modbusError.isValid (), false);
}

void TestQModbusError::testMessage ()
{
    QModbusError modbusError;
    // Default error code exercises the modbus_strerror branch.
    QVERIFY (!modbusError.message ().isEmpty ());
}
