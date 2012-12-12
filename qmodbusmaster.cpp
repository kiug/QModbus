#include "modbus.h"
#include "qmodbusmaster.h"
#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"

#include <QDebug>

using namespace Modbus;

QModbusMaster::QModbusMaster (const char *ip, int port, QObject* parent) : QObject (parent)
{
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

void QModbusMaster::connect ()
{
    if (modbus_connect ((modbus_t *) ctx) != 0) {
        modbusError.set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
    }
    else {
        modbusError.clear ();
    }
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

void QModbusMaster::getByteTimeout (long *sec, long *usec)
{
    struct timeval timeout;
    modbus_get_byte_timeout ((modbus_t *) ctx, &timeout);
    *sec = timeout.tv_sec;
    *usec = timeout.tv_usec;
}

void QModbusMaster::setByteTimeout (long sec, long usec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    modbus_set_byte_timeout ((modbus_t *) ctx, &timeout);
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

void QModbusMaster::getResponseTimeout (long *sec, long *usec)
{
    struct timeval timeout;
    modbus_get_response_timeout ((modbus_t *) ctx, &timeout);
    *sec = timeout.tv_sec;
    *usec = timeout.tv_usec;
}

void QModbusMaster::setResponseTimeout (long sec, long usec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    modbus_set_response_timeout ((modbus_t *) ctx, &timeout);
}

void QModbusMaster::readBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_read_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
}

void QModbusMaster::readInputBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_read_input_bits ((modbus_t *) ctx, bits.addr, bits.size (), (quint8 *)bits.data ()));
}

void QModbusMaster::readRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_read_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
}

void QModbusMaster::readInputRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_read_input_registers ((modbus_t *) ctx, regs.addr, regs.size (), regs.data ()));
}

void QModbusMaster::reportSlaveId (quint8 *dest)
{
    checkOperationsReturnValue (modbus_report_slave_id ((modbus_t *) ctx, dest));
}

void QModbusMaster::writeBit (QModbusBits &bit)
{
    checkOperationsReturnValue (modbus_write_bit ((modbus_t *) ctx, bit.addr, bit.data ()[0]));
}

void QModbusMaster::writeRegister (QModbusRegisters &reg)
{
    checkOperationsReturnValue (modbus_write_register ((modbus_t *) ctx, reg.addr, (unsigned int)(reg.data ()[0])));
}

void QModbusMaster::writeBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_write_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data ()));
}

void QModbusMaster::writeRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_write_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data ()));
}

void QModbusMaster::writeAndReadRegisters (QModbusRegisters &writeRegs, QModbusRegisters &readRegs)
{
    checkOperationsReturnValue (modbus_write_and_read_registers ((modbus_t *) ctx, writeRegs.addr, writeRegs.size (), writeRegs.data (), readRegs.addr, readRegs.size (), readRegs.data ()));
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
