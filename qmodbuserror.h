/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef QMODBUSERROR_H
#define QMODBUSERROR_H

#include <QObject>

#include "qmodbus.h"

class QString;

namespace Modbus
{
    // Offset for QModbus-specific error codes, chosen far above typical errno
    // values to avoid collisions with libmodbus errors.
    enum : int {
        QMODBUS_ENOBASE = 112345678,
        OUT_OF_RANGE_ENO = QMODBUS_ENOBASE - 1,
        NOT_CONNECTED_ENO = QMODBUS_ENOBASE - 2
    };

    class QMODBUSSHARED_EXPORT QModbusError
    {
        friend class QModbusMaster;
        friend class QModbusBits;
        friend class QModbusRegisters;
    public:
        QModbusError ();
        bool isValid () const;
        QString message () const;
    private:
        void set (int errnum);
        void clear ();
        int error;
        bool valid;
    };
};

#endif // QMODBUSERROR_H
