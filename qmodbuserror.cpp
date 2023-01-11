/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include <modbus/modbus.h>
#include "qmodbuserror.h"
#include <QString>

using namespace Modbus;

QModbusError::QModbusError ()
{
    clear ();
}

QModbusError::QModbusError (const QModbusError & other)
{
    error = other.error;
    valid = other.valid;
}

bool QModbusError::isValid ()
{
    return valid;
}

QString QModbusError::message ()
{
    if (error == OUT_OF_RANGE_ENO) {
        return QString (OUT_OF_RANGE_MSG);
    }
    else if (error == NOT_CONNECTED_ENO) {
        return QString (NOT_CONNECTED_MSG);
    }
    else {
        return QString (modbus_strerror (error));
    }
}

void QModbusError::set (int errnum)
{
    error = errnum;
    valid = true;
}

void QModbusError::clear ()
{
    error = 0;
    valid = false;
}
