/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

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
    void testOutOfRange ();
};

#endif // TESTQMODBUSBITS_H
