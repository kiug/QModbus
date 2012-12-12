#ifndef TESTQMODBUSBITS_H
#define TESTQMODBUSBITS_H

#include <QObject>

class TestQModbusBits : public QObject
{
    Q_OBJECT
private slots:
    void testGetValue ();
    void testGetNumber ();
    void testGetAddress ();
    void testSetAndGetValue ();
    void testSetAndGetNumber ();
    void testSetAndGetAddress ();
};

#endif // TESTQMODBUSBITS_H
