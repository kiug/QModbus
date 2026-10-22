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

bool QModbusError::isValid () const
{
    return valid;
}

QString QModbusError::message () const
{
    if (!valid) {
        return QString ();
    }
    if (error == OUT_OF_RANGE_ENO) {
        return QStringLiteral (OUT_OF_RANGE_MSG);
    }
    else if (error == NOT_CONNECTED_ENO) {
        return QStringLiteral (NOT_CONNECTED_MSG);
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
