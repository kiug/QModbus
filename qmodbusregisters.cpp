/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include <cstring>
#include <modbus/modbus.h>
#include "qmodbusregisters.h"

using namespace Modbus;

QModbusRegisters::QModbusRegisters (unsigned int address, unsigned int number) : addr (address)
{
    fill (0, number);
}

quint16 QModbusRegisters::getValue (unsigned int index)
{
    return operator [] (index);
}

void QModbusRegisters::setValue (unsigned int index, quint16 value)
{
    operator [] (index) = value;
}

unsigned int QModbusRegisters::getNumber (void)
{
    return size ();
}

void QModbusRegisters::setNumber (unsigned int number)
{
    resize (number);
}

unsigned int QModbusRegisters::getAddress (void)
{
    return addr;
}

void QModbusRegisters::setAddress (unsigned int address)
{
    addr = address;
}

QString QModbusRegisters::getBitString (unsigned int index)
{
    QString bitString;
    unsigned int i;
    i = 1 << (sizeof(operator [] (index)) * 8 - 1);
    while (i > 0)
    {
        if (operator [] (index) & i) {
            bitString.append ("1");
        }
        else {
            bitString.append ("0");
        }
        i >>= 1;
    }
    return bitString;
}

qint16 QModbusRegisters::getInteger16 (unsigned int index)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear();
    return static_cast<qint16> (at (index));
}

void QModbusRegisters::setInteger16 (unsigned int index, qint16 value)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear();
    operator [] (index) = static_cast<quint16> (value);
}

qint32 QModbusRegisters::getInteger32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear();
    const quint32 value = (quint32 (at (index)) << 16) | at (index + 1);
    return static_cast<qint32> (value);
}

void QModbusRegisters::setInteger32 (unsigned int index, qint32 value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear();
    const quint32 u = static_cast<quint32> (value);
    operator [] (index) = static_cast<quint16> (u >> 16);
    operator [] (index + 1) = static_cast<quint16> (u);
}

qint64 QModbusRegisters::getInteger64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear ();
    const quint64 value =
        (quint64 (at (index)) << 48) |
        (quint64 (at (index + 1)) << 32) |
        (quint64 (at (index + 2)) << 16) |
        quint64 (at (index + 3));
    return static_cast<qint64> (value);
}

void QModbusRegisters::setInteger64 (unsigned int index, qint64 value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    const quint64 u = static_cast<quint64> (value);
    operator [] (index) = static_cast<quint16> (u >> 48);
    operator [] (index + 1) = static_cast<quint16> (u >> 32);
    operator [] (index + 2) = static_cast<quint16> (u >> 16);
    operator [] (index + 3) = static_cast<quint16> (u);
}

quint16 QModbusRegisters::getUInteger16 (unsigned int index)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear ();
    return at (index);
}

void QModbusRegisters::setUInteger16 (unsigned int index, quint16 value)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    operator [] (index) = value;
}

quint32 QModbusRegisters::getUInteger32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear ();
    return (quint32 (at (index)) << 16) | at (index + 1);
}

void QModbusRegisters::setUInteger32 (unsigned int index, quint32 value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    operator [] (index) = static_cast<quint16> (value >> 16);
    operator [] (index + 1) = static_cast<quint16> (value);
}

quint64 QModbusRegisters::getUInteger64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0;
    }
    modbusError.clear ();
    return (quint64 (at (index)) << 48) |
           (quint64 (at (index + 1)) << 32) |
           (quint64 (at (index + 2)) << 16) |
           quint64 (at (index + 3));
}

void QModbusRegisters::setUInteger64 (unsigned int index, quint64 value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    operator [] (index) = static_cast<quint16> (value >> 48);
    operator [] (index + 1) = static_cast<quint16> (value >> 32);
    operator [] (index + 2) = static_cast<quint16> (value >> 16);
    operator [] (index + 3) = static_cast<quint16> (value);
}

float QModbusRegisters::getFloat32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0.0f;
    }
    modbusError.clear ();
    const quint32 bits = (quint32 (at (index)) << 16) | at (index + 1);
    float value;
    memcpy (&value, &bits, sizeof (value));
    return value;
}

void QModbusRegisters::setFloat32 (unsigned int index, float value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    quint32 bits;
    memcpy (&bits, &value, sizeof (bits));
    operator [] (index) = static_cast<quint16> (bits >> 16);
    operator [] (index + 1) = static_cast<quint16> (bits);
}

double QModbusRegisters::getFloat64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return 0.0;
    }
    modbusError.clear ();
    const quint64 bits =
        (quint64 (at (index)) << 48) |
        (quint64 (at (index + 1)) << 32) |
        (quint64 (at (index + 2)) << 16) |
        quint64 (at (index + 3));
    double value;
    memcpy (&value, &bits, sizeof (value));
    return value;
}

void QModbusRegisters::setFloat64 (unsigned int index, double value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
        return;
    }
    modbusError.clear ();
    quint64 bits;
    memcpy (&bits, &value, sizeof (bits));
    operator [] (index) = static_cast<quint16> (bits >> 48);
    operator [] (index + 1) = static_cast<quint16> (bits >> 32);
    operator [] (index + 2) = static_cast<quint16> (bits >> 16);
    operator [] (index + 3) = static_cast<quint16> (bits);
}

quint8 QModbusRegisters::getHighByte(quint16 data)
{
    return MODBUS_GET_HIGH_BYTE ((int)data);
}

quint8 QModbusRegisters::getLowByte (quint16 data)
{
    return MODBUS_GET_LOW_BYTE ((int)data);
}

int QModbusRegisters::getInt32FromInt16 (quint16 *data, int index)
{
    return MODBUS_GET_INT32_FROM_INT16 (data, index);
}

short QModbusRegisters::getInt16FromInt8(quint8 *data, int index)
{
    return MODBUS_GET_INT16_FROM_INT8 (data, index);
}

void QModbusRegisters::setInt16ToInt8 (quint8 *data, int index, short int value)
{
    MODBUS_SET_INT16_TO_INT8 (data, index, value);
}

void QModbusRegisters::setBitsFromByte (quint8 *dest, int index, const quint8 value)
{
    modbus_set_bits_from_byte (dest, index, value);
}

void QModbusRegisters::setBitsFromBytes (quint8 *dest, int index, unsigned int nb_bits, const quint8 *tab_byte)
{
    modbus_set_bits_from_bytes (dest, index, nb_bits, tab_byte);
}

void QModbusRegisters::getByteFromBits (const quint8 *src, int index, unsigned int nb_bits)
{
    modbus_get_byte_from_bits (src, index, nb_bits);
}

float QModbusRegisters::getFloat(const quint16 *src)
{
    const quint32 bits = (quint32 (src[0]) << 16) | src[1];
    float value;
    memcpy (&value, &bits, sizeof (value));
    return value;
}

void QModbusRegisters::setFloat (float value, quint16 *dest)
{
    quint32 bits;
    memcpy (&bits, &value, sizeof (bits));
    dest[0] = static_cast<quint16> (bits >> 16);
    dest[1] = static_cast<quint16> (bits);
}
