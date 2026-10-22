/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef TESTQMODBUSERROR_H
#define TESTQMODBUSERROR_H

#include <QObject>

class TestQModbusError : public QObject
{
    Q_OBJECT
private slots:
    void testIsValid ();
    void testMessage ();
};

#endif // TESTQMODBUSERROR_H
