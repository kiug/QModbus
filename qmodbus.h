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
    typedef enum
    {
        None = 0,//MODBUS_ERROR_RECOVERY_NONE
        Link = (1<<1),//MODBUS_ERROR_RECOVERY_LINK
        Protocol = (1<<2)//MODBUS_ERROR_RECOVERY_PROTOCOL
    } errorRecoveryMode;

    typedef enum
    {
        IllegalFunction = 0x01,//MODBUS_EXCEPTION_ILLEGAL_FUNCTION, // (1)
        IllegalDataAddress,// = MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS, // (2)
        IllegalDataValue,// = MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE, // (3)
        SlaveOrServerFailure,// = MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE, // (4)
        Acknowledge,// = MODBUS_EXCEPTION_ACKNOWLEDGE, // (5)
        SlaveOrServerBusy,// = MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY, // (6)
        NegativeAcknowledge,// = MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE, // (7)
        MemoryParity,// = MODBUS_EXCEPTION_MEMORY_PARITY, // (8)
        NotDefined,// = MODBUS_EXCEPTION_NOT_DEFINED, // (9)
        GatewayPath,// = MODBUS_EXCEPTION_GATEWAY_PATH, // (10)
        GatewayTarget// = MODBUS_EXCEPTION_GATEWAY_TARGET // (11)
    } modbusException;
};

#endif // QMODBUS_H
