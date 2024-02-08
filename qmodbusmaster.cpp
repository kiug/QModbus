/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include <modbus/modbus.h>
#include "qmodbusmaster.h"
#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"

#include <QLoggingCategory>

using namespace Modbus;

QModbusMaster::QModbusMaster (const char *ip, int port, QObject* parent) : QObject (parent)
{
    connected = false;
    ctx = (modbus_t *) modbus_new_tcp (ip, port);
    checkContext ((modbus_t *) ctx);
}

QModbusMaster::QModbusMaster (const char *device, int baud, char parity, int dataBit, int stopBit, QObject* parent) : QObject (parent)
{
    ctx = (modbus_t *) modbus_new_rtu (device, baud, parity, dataBit, stopBit);
    checkContext ((modbus_t *) ctx);
}

QModbusMaster::QModbusMaster (const char *node, const char *service, QObject* parent) : QObject (parent)
{
    ctx = (modbus_t *) modbus_new_tcp_pi (node, service);
    checkContext ((modbus_t *) ctx);
}

QModbusMaster::~QModbusMaster ()
{
    close ();
    modbus_free ((modbus_t *) ctx);
}

bool QModbusMaster::setSlave (int slave)
{
    return checkOperationsReturnValue( modbus_set_slave ((modbus_t *) ctx, slave) != 0 );
}

bool QModbusMaster::setBroadcast ()
{
    return checkOperationsReturnValue( modbus_set_slave((modbus_t *) ctx, MODBUS_BROADCAST_ADDRESS) != 0 );
}

bool QModbusMaster::connect ()
{
    const int returnValue = modbus_connect ((modbus_t *) ctx);
    connected = returnValue != 0 ? false : true;
    return checkOperationsReturnValue(returnValue);
}

void QModbusMaster::close()
{
    modbus_close ((modbus_t *) ctx);
    modbusError.clear ();
}

bool QModbusMaster::flush ()
{
    return checkOperationsReturnValue( modbus_flush ((modbus_t *) ctx) != 0 );
}

bool QModbusMaster::getByteTimeout (uint32_t *sec, uint32_t *usec)
{
    return checkOperationsReturnValue( modbus_get_byte_timeout ((modbus_t *) ctx, sec, usec) != 0 );
}

bool QModbusMaster::setByteTimeout (uint32_t sec, uint32_t usec)
{
    return checkOperationsReturnValue( modbus_set_byte_timeout ((modbus_t *) ctx, sec, usec) != 0 );
}

bool QModbusMaster::setDebug (bool debug)
{
    return checkOperationsReturnValue( modbus_set_debug ((modbus_t *) ctx, (int)debug) != 0 );
}

bool QModbusMaster::setErrorRecovery(errorRecoveryMode errorRecovery)
{
    return checkOperationsReturnValue( modbus_set_error_recovery ((modbus_t *) ctx, (modbus_error_recovery_mode)errorRecovery) );
}

int QModbusMaster::getHeaderLength (void)
{
    // function simply returns data from ctx, as we ensure that ctx is always there and never nullptr,
    // this call cannot fail
    return modbus_get_header_length ((modbus_t *) ctx);
}

bool QModbusMaster::getResponseTimeout (uint32_t *sec, uint32_t *usec)
{
    return checkOperationsReturnValue( modbus_get_response_timeout ((modbus_t *) ctx, sec, usec) );
}

bool QModbusMaster::setResponseTimeout (uint32_t sec, uint32_t usec)
{
    return checkOperationsReturnValue( modbus_set_response_timeout ((modbus_t *) ctx, sec, usec) );
}

bool QModbusMaster::readBits (QModbusBits &bits)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_read_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
}

bool QModbusMaster::readInputBits (QModbusBits &bits)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_read_input_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
}

bool QModbusMaster::readRegisters (QModbusRegisters &regs)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_read_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
}

bool QModbusMaster::readInputRegisters (QModbusRegisters &regs)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_read_input_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
}

bool QModbusMaster::reportSlaveId (quint8 *dest)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_report_slave_id ((modbus_t *) ctx, 1, dest));
}

bool QModbusMaster::writeBit (QModbusBits &bit)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_write_bit ((modbus_t *) ctx, bit.addr, bit.data ()[0]));
}

bool QModbusMaster::writeRegister (QModbusRegisters &reg)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_write_register ((modbus_t *) ctx, reg.addr, (unsigned int)(reg.data ()[0])));
}

bool QModbusMaster::writeBits (QModbusBits &bits)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_write_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data ()));
}

bool QModbusMaster::writeRegisters (QModbusRegisters &regs)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_write_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data ()));
}

bool QModbusMaster::writeAndReadRegisters (QModbusRegisters &writeRegs, QModbusRegisters &readRegs)
{
    if (!checkConnection())
        return false;
    return checkOperationsReturnValue (modbus_write_and_read_registers ((modbus_t *) ctx, writeRegs.addr, writeRegs.size (), writeRegs.data (), readRegs.addr, readRegs.size (), readRegs.data ()));
}

// private
void QModbusMaster::checkContext (void *ctx)
{
    if (ctx == NULL) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}

bool QModbusMaster::checkConnection ()
{
    if (!connected) {
        modbusError.set (NOT_CONNECTED_ENO);
    }
    else {
        modbusError.clear ();
    }
    return connected;
}

bool QModbusMaster::checkOperationsReturnValue (int operationsReturnValue)
{
    if (operationsReturnValue == -1) {
        modbusError.set (errno);
        QLoggingCategory category("QModbus");
        qCWarning (category, "%s (%d)", modbus_strerror (errno), errno);
        return false;
    }
    modbusError.clear ();
    return true;
}
