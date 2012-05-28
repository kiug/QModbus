#ifndef TESTQMODBUS_H
#define TESTQMODBUS_H

#include <QObject>

#define IP "127.0.0.1"
#define PORT 502

class TestQModbus : public QObject
{
    Q_OBJECT
public:
    explicit TestQModbus(QObject *parent = 0);

private slots:

    void bitsTest ();
    void registersTest ();
    void testConnection ();
};

#endif // TESTQMODBUS_H
