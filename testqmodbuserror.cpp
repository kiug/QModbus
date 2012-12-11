#include "testqmodbuserror.h"
#include "qmodbuserror.h"

#include <QtTest/QTest>

void TestQModbusError::testIsValid()
{
    Modbus::QModbusError modbusError;
    QCOMPARE(modbusError.isValid(), true);
}
