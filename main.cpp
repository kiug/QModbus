#include "qmodbusmaster.h"
#include "testqmodbusbits.h"
#include "testqmodbusregisters.h"
#include "testqmodbuserror.h"
#include "testqmodbus.h"
//#include "testqmodbusslave.h"

#include <QtTest/QTest>
#include <QDebug>

#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
    //TestQModbusSlave testQModbusSlave;
    //testQModbusSlave.start();

    TestQModbusBits testQModbusBits;
    QTest::qExec(&testQModbusBits);
    TestQModbusRegisters testQModbusRegisters;
    QTest::qExec(&testQModbusRegisters);
    TestQModbusError testQModbusError;
    QTest::qExec(&testQModbusError);
    TestQModbusMaster testQModbusMaster;
    QTest::qExec(&testQModbusMaster);

    //testQModbusSlave.stop();
    return 0;
}

//QTEST_MAIN(TestQModbusBits);
