#ifndef TESTQMODBUS_H
#define TESTQMODBUS_H

#include <QObject>
#include "qmodbus.h"

#define IP "127.0.0.1"
#define PORT 502

class TestQModbus : public QObject
{
    Q_OBJECT
public:
    explicit TestQModbus(QObject *parent = 0);
    ~TestQModbus();

private slots:
    void testConnection ();
    void bitsTest ();
    void registersTest ();

private:
    Modbus::QModbus *modbus;
};

#endif // TESTQMODBUS_H
