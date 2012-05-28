#include "qmodbusregisters.h"

#include <stdexcept>

using namespace Modbus;

#define OUT_OF_RANGE_MSG "Register index out of range"

QModbusRegisters::QModbusRegisters (unsigned int address, unsigned int number) : addr (address)
{
    fill(0, number);
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
    i = 1<<(sizeof(operator [] (index)) * 8 - 1);
    while (i > 0)
    {
        if (operator [] (index) & i)
            bitString.append ("1");
        else
            bitString.append ("0");
        i >>= 1;
    }
    return bitString;
}

short int QModbusRegisters::getInteger16 (unsigned int index)
{
    if (size() <= (int)index)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    short int value = 0;
    ((quint16 *) &value)[0] = at (index);
    return value;
}

void QModbusRegisters::setInteger16 (unsigned int index, short int value)
{
    if (size() <= (int)index)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
}

int QModbusRegisters::getInteger32 (unsigned int index)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    int value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    return value;
}

void QModbusRegisters::setInteger32 (unsigned int index, int value)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
}

long long int QModbusRegisters::getInteger64 (unsigned int index)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    long long int value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    ((quint16 *) &value)[2] = at (index + 2);
    ((quint16 *) &value)[3] = at (index + 3);
    return value;
}

void QModbusRegisters::setInteger64 (unsigned int index, long long int value)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
    operator [] (index + 2) = ((quint16 *) &value)[2];
    operator [] (index + 3) = ((quint16 *) &value)[3];
}

short unsigned int QModbusRegisters::getUInteger16 (unsigned int index)
{
    if (size() <= (int)index)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    short unsigned int value = 0;
    ((quint16 *) &value)[0] = at (index);
    return value;
}

void QModbusRegisters::setUInteger16 (unsigned int index, short unsigned int value)
{
    if (size() <= (int)index)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
}

unsigned int QModbusRegisters::getUInteger32 (unsigned int index)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    unsigned int value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    return value;
}

void QModbusRegisters::setUInteger32 (unsigned int index, unsigned int value)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
}

long long unsigned int QModbusRegisters::getUInteger64 (unsigned int index)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    long long unsigned int value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    ((quint16 *) &value)[2] = at (index + 2);
    ((quint16 *) &value)[3] = at (index + 3);
    return value;
}

void QModbusRegisters::setUInteger64 (unsigned int index, long long unsigned int value)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
    operator [] (index + 2) = ((quint16 *) &value)[2];
    operator [] (index + 3) = ((quint16 *) &value)[3];
}

float QModbusRegisters::getFloat32 (unsigned int index)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    float value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);

    return value;
}

void QModbusRegisters::setFloat32 (unsigned int index, float value)
{
    if (size() <= (int)index + 1)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
}

double QModbusRegisters::getFloat64 (unsigned int index)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    double value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    ((quint16 *) &value)[2] = at (index + 2);
    ((quint16 *) &value)[3] = at (index + 3);
    return value;
}

void QModbusRegisters::setFloat64 (unsigned int index, double value)
{
    if (size() <= (int)index + 3)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
    operator [] (index + 2) = ((quint16 *) &value)[2];
    operator [] (index + 3) = ((quint16 *) &value)[3];
}

long double QModbusRegisters::getFloat96 (unsigned int index)
{
    if (size() <= (int)index + 5)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    long double value = 0;
    ((quint16 *) &value)[0] = at (index);
    ((quint16 *) &value)[1] = at (index + 1);
    ((quint16 *) &value)[2] = at (index + 2);
    ((quint16 *) &value)[3] = at (index + 3);
    ((quint16 *) &value)[4] = at (index + 4);
    ((quint16 *) &value)[5] = at (index + 5);
    return value;
}

void QModbusRegisters::setFloat96 (unsigned int index, long double value)
{
    if (size() <= (int)index + 5)
    {
        throw std::out_of_range::out_of_range (OUT_OF_RANGE_MSG);
    }
    operator [] (index) = ((quint16 *) &value)[0];
    operator [] (index + 1) = ((quint16 *) &value)[1];
    operator [] (index + 2) = ((quint16 *) &value)[2];
    operator [] (index + 3) = ((quint16 *) &value)[3];
    operator [] (index + 4) = ((quint16 *) &value)[4];
    operator [] (index + 5) = ((quint16 *) &value)[5];
}

