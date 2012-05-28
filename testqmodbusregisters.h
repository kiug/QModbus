#ifndef TESTQMODBUSREGISTERS_H
#define TESTQMODBUSREGISTERS_H

#include <QObject>

class TestQModbusRegisters : public QObject
{
    Q_OBJECT
private slots:
    void testGetValue ();
    void testGetNumber ();
    void testGetAddress ();
    void testSetAndGetValue ();
    void testSetAndGetNumber ();
    void testSetAndGetAddress ();
    void testGetBitString ();

    // Integer
    void testGetInteger16 ();
    void testGetInteger32 ();
    void testGetInteger64 ();
    void testSetAndGetInteger16 ();
    void testSetAndGetInteger32 ();
    void testSetAndGetInteger64 ();
    // UInteger
    void testGetUInteger16 ();
    void testGetUInteger32 ();
    void testGetUInteger64 ();
    void testSetAndGetUInteger16 ();
    void testSetAndGetUInteger32 ();
    void testSetAndGetUInteger64 ();
    // Float
    void testGetFloat32 ();
    void testGetFloat64 ();
    void testGetFloat96 ();
    void testSetAndGetFloat32 ();
    void testSetAndGetFloat64 ();
    void testSetAndGetFloat96 ();
    //float getFloat16 (unsigned int index);
    //void setFloat16 (unsigned int index, float value);
    //float getFloat32 (unsigned int index);
    //void setFloat32 (unsigned int index, float value);
    //double getFloat64 (unsigned int index);
    //void setFloat64 (unsigned int index, double value);
    //long double getFloat96 (unsigned int index);
    //void setFloat96 (unsigned int index, long double value);
};

#endif // TESTQMODBUSREGISTERS_H
