/****************************************************************************
**
** SPDX-License-Identifier: GPL-3.0-or-later
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
