#include "testqmodbuserror.h"
#include "qmodbuserror.h"

#include <QtTest/QTest>

using namespace Modbus;

void TestQModbusError::testIsValid ()
{
    QModbusError modbusError;
    QCOMPARE (modbusError.isValid (), false);
}
