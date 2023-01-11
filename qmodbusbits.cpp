/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#include "qmodbusbits.h"

using namespace Modbus;

QModbusBits::QModbusBits (unsigned int address, unsigned int number) : addr (address)
{
    fill (false, number);
}

bool QModbusBits::getValue (unsigned int index)
{
    return operator[](index);
}

void QModbusBits::setValue (unsigned int index, bool value)
{
    operator[](index) = value;
}

unsigned int QModbusBits::getNumber (void)
{
    return size ();
}

void QModbusBits::setNumber (unsigned int number)
{
    resize (number);// default-constructed values <=> 0
}

unsigned int QModbusBits::getAddress (void)
{
    return addr;
}

void QModbusBits::setAddress (unsigned int address)
{
    addr = address;
}
