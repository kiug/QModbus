/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

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
    void testSetAndGetFloat32 ();
    void testSetAndGetFloat64 ();
    // Register byte/word order (big-endian)
    void testSetFloat32RegisterOrder ();
    void testGetFloat32RegisterOrder ();
    void testSetUInteger32RegisterOrder ();
    void testSetFloat64RegisterOrder ();
};

#endif // TESTQMODBUSREGISTERS_H
