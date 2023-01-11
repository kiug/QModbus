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

#include <QDebug>

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

QModbusError & QModbusMaster::lastError ()
{
    return modbusError;
}

void QModbusMaster::setSlave (int slave)
{
    if (modbus_set_slave ((modbus_t *) ctx, slave) != 0) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}

void QModbusMaster::setBroadcast ()
{
    if (modbus_set_slave((modbus_t *) ctx, MODBUS_BROADCAST_ADDRESS) != 0) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}

bool QModbusMaster::connect ()
{
    if (modbus_connect ((modbus_t *) ctx) != 0) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        connected = false;
    }
    else {
        modbusError.clear ();
        connected = true;
    }
    return connected;
}

void QModbusMaster::close()
{
    modbus_close ((modbus_t *) ctx);
}

void QModbusMaster::flush ()
{
    if (modbus_flush ((modbus_t *) ctx) != 0) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}

void QModbusMaster::getByteTimeout (uint32_t *sec, uint32_t *usec)
{
    modbus_get_byte_timeout ((modbus_t *) ctx, sec, usec);
}

void QModbusMaster::setByteTimeout (uint32_t sec, uint32_t usec)
{
    modbus_set_byte_timeout ((modbus_t *) ctx, sec, usec);
}

void QModbusMaster::setDebug (bool debug)
{
    modbus_set_debug ((modbus_t *) ctx, (int)debug);
}

void QModbusMaster::setErrorRecovery (errorRecoveryMode errorRecovery)
{
    if (!modbus_set_error_recovery ((modbus_t *) ctx, (modbus_error_recovery_mode)errorRecovery)) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}

int QModbusMaster::getHeaderLength (void)
{
    return modbus_get_header_length ((modbus_t *) ctx);
}

void QModbusMaster::getResponseTimeout (uint32_t *sec, uint32_t *usec)
{
    modbus_get_response_timeout ((modbus_t *) ctx, sec, usec);
}

void QModbusMaster::setResponseTimeout (uint32_t sec, uint32_t usec)
{
    modbus_set_response_timeout ((modbus_t *) ctx, sec, usec);
}

void QModbusMaster::readBits (QModbusBits &bits)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_read_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
    }
}

void QModbusMaster::readInputBits (QModbusBits &bits)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_read_input_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
    }
}

void QModbusMaster::readRegisters (QModbusRegisters &regs)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_read_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
    }
}

void QModbusMaster::readInputRegisters (QModbusRegisters &regs)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_read_input_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
    }
}

void QModbusMaster::reportSlaveId (quint8 *dest)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_report_slave_id ((modbus_t *) ctx, 1, dest));
    }
}

void QModbusMaster::writeBit (QModbusBits &bit)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_write_bit ((modbus_t *) ctx, bit.addr, bit.data ()[0]));
    }
}

void QModbusMaster::writeRegister (QModbusRegisters &reg)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_write_register ((modbus_t *) ctx, reg.addr, (unsigned int)(reg.data ()[0])));
    }
}

void QModbusMaster::writeBits (QModbusBits &bits)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_write_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data ()));
    }
}

void QModbusMaster::writeRegisters (QModbusRegisters &regs)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_write_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data ()));
    }
}

void QModbusMaster::writeAndReadRegisters (QModbusRegisters &writeRegs, QModbusRegisters &readRegs)
{
    if(checkConnection()) {
        checkOperationsReturnValue (modbus_write_and_read_registers ((modbus_t *) ctx, writeRegs.addr, writeRegs.size (), writeRegs.data (), readRegs.addr, readRegs.size (), readRegs.data ()));
    }
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

void QModbusMaster::checkOperationsReturnValue (int operationsReturnValue)
{
    if (operationsReturnValue == -1) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
}
