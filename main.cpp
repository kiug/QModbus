#include "qmodbus.h"
#include "testqmodbusbits.h"
#include "testqmodbusregisters.h"
#include "testqmodbus.h"

#include <QtTest/QTest>
#include <QDebug>

#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
    TestQModbusBits testQModbusBits;
    QTest::qExec(&testQModbusBits);
    TestQModbusRegisters testQModbusRegisters;
    QTest::qExec(&testQModbusRegisters);
    TestQModbus testQModbus;
    QTest::qExec(&testQModbus);

    return 0;
}

//QTEST_MAIN(TestQModbusBits);
