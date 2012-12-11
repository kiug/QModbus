#ifndef TESTQMODBUSMASTER_H
#define TESTQMODBUSMASTER_H

#include <QObject>
#include "qmodbus.h"

#define IP "127.0.0.1"
#define PORT 502

class TestQModbusMaster : public QObject
{
    Q_OBJECT
public:
    explicit TestQModbusMaster(QObject *parent = 0);
    ~TestQModbusMaster();

private slots:
    void testConnection ();
    void bitsTest ();
    void registersTest ();

private:
    Modbus::QModbusMaster *modbus;
};

#endif // TESTQMODBUSMASTER_H
