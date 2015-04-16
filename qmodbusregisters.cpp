#include "qmodbusregisters.h"
#include "modbus.h"

using namespace Modbus;

union twoRegistersRepresentation {
    quint16 component[2];
    quint32 uint32;
    qint32 int32;
    float float32;
};

union fourRegistersRepresentation {
    quint16 component[4];
    quint64 uint64;
    qint64 int64;
    double float64;
};

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
    }
    else {
        modbusError.clear();
    }
    qint16 value = 0;
    ((quint16 *) &value)[0] = at (index);
    return value;
}

void QModbusRegisters::setInteger16 (unsigned int index, qint16 value)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear();
    }
    operator [] (index) = ((quint16 *) &value)[0];
}

qint32 QModbusRegisters::getInteger32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear();
    }
    twoRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    return valueRep.int32;
}

void QModbusRegisters::setInteger32 (unsigned int index, qint32 value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear();
    }
    twoRegistersRepresentation valueRep;
    valueRep.int32 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
}

qint64 QModbusRegisters::getInteger64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    valueRep.component[2] = at (index + 2);
    valueRep.component[3] = at (index + 3);
    return valueRep.int64;
}

void QModbusRegisters::setInteger64 (unsigned int index, qint64 value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.int64 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
    operator [] (index + 2) = valueRep.component[2];
    operator [] (index + 3) = valueRep.component[3];
}

quint16 QModbusRegisters::getUInteger16 (unsigned int index)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    quint16 value = 0;
    ((quint16 *) &value)[0] = at (index);
    return value;
}

void QModbusRegisters::setUInteger16 (unsigned int index, quint16 value)
{
    if (size () <= (int)index) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    operator [] (index) = ((quint16 *) &value)[0];
}

quint32 QModbusRegisters::getUInteger32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    twoRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    return valueRep.uint32;
}

void QModbusRegisters::setUInteger32 (unsigned int index, quint32 value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    twoRegistersRepresentation valueRep;
    valueRep.uint32 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
}

quint64 QModbusRegisters::getUInteger64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    valueRep.component[2] = at (index + 2);
    valueRep.component[3] = at (index + 3);
    return valueRep.uint64;
}

void QModbusRegisters::setUInteger64 (unsigned int index, quint64 value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.uint64 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
    operator [] (index + 2) = valueRep.component[2];
    operator [] (index + 3) = valueRep.component[3];
}

float QModbusRegisters::getFloat32 (unsigned int index)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    twoRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    return valueRep.float32;
}

void QModbusRegisters::setFloat32 (unsigned int index, float value)
{
    if (size () <= (int)index + 1) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    twoRegistersRepresentation valueRep;
    valueRep.float32 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
}

double QModbusRegisters::getFloat64 (unsigned int index)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.component[0] = at (index);
    valueRep.component[1] = at (index + 1);
    valueRep.component[2] = at (index + 2);
    valueRep.component[3] = at (index + 3);
    return valueRep.float64;
}

void QModbusRegisters::setFloat64 (unsigned int index, double value)
{
    if (size () <= (int)index + 3) {
        modbusError.set (OUT_OF_RANGE_ENO);
    }
    else {
        modbusError.clear ();
    }
    fourRegistersRepresentation valueRep;
    valueRep.float64 = value;
    operator [] (index) = valueRep.component[0];
    operator [] (index + 1) = valueRep.component[1];
    operator [] (index + 2) = valueRep.component[2];
    operator [] (index + 3) = valueRep.component[3];
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
    return modbus_get_float (src);
}

void QModbusRegisters::setFloat (float value, quint16 *dest)
{
    modbus_set_float (value, dest);
}
