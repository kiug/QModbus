#include "modbus.h"
#include "qmodbus.h"
#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"
#include <stdexcept>
#include <QDebug>

using namespace Modbus;

QModbus::QModbus (const char *ip, int port, QObject* parent)
{
    ctx = (modbus_t *) modbus_new_tcp (ip, port);
    checkContext ((modbus_t *) ctx);
    modbusError = new QModbusError;
}

QModbus::QModbus (const char *device, int baud, char parity, int dataBit, int stopBit, QObject* parent) : QObject(parent)
{
    ctx = (modbus_t *) modbus_new_rtu (device, baud, parity, dataBit, stopBit);
    checkContext ((modbus_t *) ctx);
    modbusError = new QModbusError;
}

QModbus::QModbus (const char *node, const char *service, QObject* parent) : QObject(parent)
{
    ctx = (modbus_t *) modbus_new_tcp_pi (node, service);
    checkContext ((modbus_t *) ctx);
    modbusError = new QModbusError;
}

QModbus::~QModbus ()
{
    close ();
    modbus_free ((modbus_t *) ctx);
    delete modbusError;
}

QModbusError QModbus::lastError ()
{
    return *modbusError;
}

void QModbus::setSlave (int slave)
{
    if (modbus_set_slave ((modbus_t *) ctx, slave) != 0)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::invalid_argument::invalid_argument (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

void QModbus::setBroadcast()
{
    if (modbus_set_slave((modbus_t *) ctx, MODBUS_BROADCAST_ADDRESS) != 0)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::invalid_argument::invalid_argument (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

void QModbus::connect ()
{
    if (modbus_connect ((modbus_t *) ctx) != 0)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::invalid_argument::invalid_argument (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

void QModbus::close()
{
    modbus_close ((modbus_t *) ctx);
}

void QModbus::flush ()
{
    if (modbus_flush ((modbus_t *) ctx) != 0)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::runtime_error::runtime_error (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

void QModbus::getByteTimeout (long *sec, long *usec)
{
    struct timeval timeout;
    modbus_get_byte_timeout ((modbus_t *) ctx, &timeout);
    *sec = timeout.tv_sec;
    *usec = timeout.tv_usec;
}

void QModbus::setByteTimeout (long sec, long usec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    modbus_set_byte_timeout ((modbus_t *) ctx, &timeout);
}

void QModbus::setDebug (bool debug)
{
    modbus_set_debug ((modbus_t *) ctx, (int)debug);
}

void QModbus::setErrorRecovery (errorRecoveryMode errorRecovery)
{
    if (!modbus_set_error_recovery ((modbus_t *) ctx, (modbus_error_recovery_mode)errorRecovery))
    {
        modbusError->set(errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::invalid_argument::invalid_argument (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

int QModbus::getHeaderLength (void)
{
    return modbus_get_header_length ((modbus_t *) ctx);
}

void QModbus::getResponseTimeout (long *sec, long *usec)
{
    struct timeval timeout;
    modbus_get_response_timeout ((modbus_t *) ctx, &timeout);
    *sec = timeout.tv_sec;
    *usec = timeout.tv_usec;
}

void QModbus::setResponseTimeout (long sec, long usec)
{
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    modbus_set_response_timeout ((modbus_t *) ctx, &timeout);
}

void QModbus::setSocket (int socket)
{
    modbus_set_socket ((modbus_t *) ctx, socket);
}

int QModbus::getSocket (void)
{
    return modbus_get_socket ((modbus_t *) ctx);
}

void QModbus::readBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_read_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data()));
}

void QModbus::readInputBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_read_input_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data()));
}

void QModbus::readRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_read_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data()));
}

void QModbus::readInputRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_read_input_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data()));
}

void QModbus::reportSlaveId (quint8 *dest)
{
    checkOperationsReturnValue (modbus_report_slave_id ((modbus_t *) ctx, dest));
}

void QModbus::writeBit (QModbusBits &bit)
{
    checkOperationsReturnValue (modbus_write_bit ((modbus_t *) ctx, bit.addr, bit.data()[0]));
}

void QModbus::writeRegister (QModbusRegisters &reg)
{
    checkOperationsReturnValue (modbus_write_register ((modbus_t *) ctx, reg.addr, (unsigned int)(reg.data()[0])));
}

void QModbus::writeBits (QModbusBits &bits)
{
    checkOperationsReturnValue (modbus_write_bits ((modbus_t *) ctx, bits.addr, bits.size(), (quint8 *)bits.data()));
}

void QModbus::writeRegisters (QModbusRegisters &regs)
{
    checkOperationsReturnValue (modbus_write_registers ((modbus_t *) ctx, regs.addr, regs.size(), regs.data()));
}

void QModbus::writeAndReadRegisters (QModbusRegisters &writeRegs, QModbusRegisters &readRegs)
{
    checkOperationsReturnValue (modbus_write_and_read_registers ((modbus_t *) ctx, writeRegs.addr, writeRegs.size(), writeRegs.data(), readRegs.addr, readRegs.size(), readRegs.data()));
}

void QModbus::sendRawRequest(quint8 *rawReq, int rawReqLength)
{
    checkOperationsReturnValue (modbus_send_raw_request ((modbus_t *) ctx, rawReq, rawReqLength));
}

void QModbus::receiveConfirmation (quint8 *rsp)
{
    checkOperationsReturnValue (modbus_receive_confirmation ((modbus_t *) ctx, rsp));
}

void QModbus::replyException (quint8 *req, modbusException exceptionCode)
{
    checkOperationsReturnValue (modbus_reply_exception ((modbus_t *) ctx, req, (unsigned int)exceptionCode));
}

const quint8 QModbus::getHighByte (quint16 data)
{
    return MODBUS_GET_HIGH_BYTE ((int)data);
}

const quint8 QModbus::getLowByte (quint16 data)
{
    return MODBUS_GET_LOW_BYTE ((int)data);
}

const int QModbus::getInt32FromInt16 (quint16 *data, int index)
{
    return MODBUS_GET_INT32_FROM_INT16 (data, index);
}

const short int QModbus::getInt16FromInt8 (quint8 *data, int index)
{
    return MODBUS_GET_INT16_FROM_INT8 (data, index);
}

void QModbus::setInt16ToInt8 (quint8 *data, int index, short int value)
{
    MODBUS_SET_INT16_TO_INT8 (data, index, value);
}

void QModbus::setBitsFromByte (quint8 *dest, int index, const quint8 value)
{
    modbus_set_bits_from_byte (dest, index, value);
}

void QModbus::setBitsFromBytes (quint8 *dest, int index, unsigned int nb_bits, const quint8 *tab_byte)
{
    modbus_set_bits_from_bytes (dest, index, nb_bits, tab_byte);
}

void QModbus::getByteFromBits (const quint8 *src, int index, unsigned int nb_bits)
{
    modbus_get_byte_from_bits (src, index, nb_bits);
}

const float QModbus::getFloat (const quint16 *src)
{
    return modbus_get_float (src);
}

void QModbus::setFloat (float value, quint16 *dest)
{
    modbus_set_float (value, dest);
}

// private
void QModbus::checkContext (void *ctx)
{
    if (ctx == NULL)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::invalid_argument::invalid_argument (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}

void QModbus::checkOperationsReturnValue (int operationsReturnValue)
{
    if (operationsReturnValue == -1)
    {
        modbusError->set (errno);
        qErrnoWarning (errno, modbus_strerror (errno));
        throw std::logic_error::logic_error (modbus_strerror (errno));
    }
    else
    {
        modbusError->clear();
    }
}
