/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef QMODBUS_H
#define QMODBUS_H

#include <QObject>

#if defined(QMODBUS_LIBRARY)
#  define QMODBUSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMODBUSSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace Modbus {
    enum errorRecoveryMode : quint8
    {
        None = 0,//MODBUS_ERROR_RECOVERY_NONE
        Link = (1<<1),//MODBUS_ERROR_RECOVERY_LINK
        Protocol = (1<<2)//MODBUS_ERROR_RECOVERY_PROTOCOL
    };
};

#endif // QMODBUS_H
