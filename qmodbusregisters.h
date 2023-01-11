/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef QMODBUSREGISTERS_H
#define QMODBUSREGISTERS_H

#include "qmodbus.h"
#include "qmodbuserror.h"

#include <stddef.h>
#include <QVector>

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusRegisters : public QVector <quint16>
    {
        friend class QModbusMaster;
    public:
        typedef enum {b1 = 0, b2, b3, b4, b5, b6, b7, b8} bytePosition;
        typedef unsigned char byteOrder2 [2];
        typedef unsigned char byteOrder4 [4];
        typedef unsigned char byteOrder8 [8];

        QModbusRegisters (unsigned int address = 0, unsigned int number = 1);
        quint16 getValue (unsigned int index);
        void setValue (unsigned int index, quint16 value);
        unsigned int getNumber (void);
        void setNumber (unsigned int number);
        unsigned int getAddress (void);
        void setAddress (unsigned int address);
        QString getBitString (unsigned int index);
        // Integer
        qint16 getInteger16 (unsigned int index);
        void setInteger16 (unsigned int index, qint16 value);
        qint32 getInteger32 (unsigned int index);
        void setInteger32 (unsigned int index, qint32 value);
        qint64 getInteger64 (unsigned int index);
        void setInteger64 (unsigned int index, qint64 value);
        // UInteger
        quint16 getUInteger16 (unsigned int index);
        void setUInteger16 (unsigned int index, quint16 value);
        quint32 getUInteger32 (unsigned int index);
        void setUInteger32 (unsigned int index, quint32 value);
        quint64 getUInteger64 (unsigned int index);
        void setUInteger64 (unsigned int index, quint64 value);
        // Float
        float getFloat32 (unsigned int index);
        void setFloat32 (unsigned int index, float value);
        double getFloat64 (unsigned int index);
        void setFloat64 (unsigned int index, double value);

        // Macros for data manipulation
        inline static quint8 getHighByte (quint16 data);// extracts the high byte from a byte
        inline static quint8 getLowByte (quint16 data);// extracts the low byte from a byte
        inline static int getInt32FromInt16 (quint16 *data, int index);// builds an int32 from the two first int16 starting at tab_int16[index]
        inline static short int getInt16FromInt8 (quint8 *data, int index);// builds an int16 from the two first int8 starting at tab_int8[index]
        inline static void setInt16ToInt8 (quint8 *data, int index, short int value);// set an int16 value into the two first bytes starting at tab_int8[index]

        // Functions for data manipulation
        inline static void setBitsFromByte (quint8 *dest, int index, const quint8 value);
        inline static void setBitsFromBytes (quint8 *dest, int index, unsigned int nb_bits, const quint8 *tab_byte);
        inline static void getByteFromBits (const quint8 *src, int index, unsigned int nb_bits);
        inline static float getFloat (const quint16 *src);
        inline static void setFloat (float value, quint16 *dest);

    private:
        unsigned int addr;
        QModbusError modbusError;
    };
};

#endif // QMODBUSREGISTERS_H
