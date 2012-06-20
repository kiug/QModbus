#ifndef QMODBUSREGISTERS_H
#define QMODBUSREGISTERS_H

#include "qmodbus.h"
#include <stddef.h>
#include <QVector>

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusRegisters : public QVector <quint16>
    {
        friend class QModbus;
    public:
        typedef enum {b1 = 0, b2, b3, b4, b5, b6, b7, b8} bytePosition;
        typedef unsigned char byteOrder2 [2];
        typedef unsigned char byteOrder4 [4];
        typedef unsigned char byteOrder8 [8];

        QModbusRegisters (unsigned int address, unsigned int number = 1);
        quint16 getValue (unsigned int index);
        void setValue (unsigned int index, quint16 value);
        unsigned int getNumber (void);
        void setNumber (unsigned int number);
        unsigned int getAddress (void);
        void setAddress (unsigned int address);
        QString getBitString (unsigned int index);
        // Integer
        short int getInteger16 (unsigned int index);
        void setInteger16 (unsigned int index, short int value);
        int getInteger32 (unsigned int index);
        void setInteger32 (unsigned int index, int value);
        long long int getInteger64 (unsigned int index);
        void setInteger64 (unsigned int index, long long int value);
        // UInteger
        short unsigned int getUInteger16 (unsigned int index);
        void setUInteger16 (unsigned int index, short unsigned int value);
        unsigned int getUInteger32 (unsigned int index);
        void setUInteger32 (unsigned int index, unsigned int value);
        long long unsigned int getUInteger64 (unsigned int index);
        void setUInteger64 (unsigned int index, long long unsigned int value);
        // Float
        float getFloat32 (unsigned int index);
        void setFloat32 (unsigned int index, float value);
        double getFloat64 (unsigned int index);
        void setFloat64 (unsigned int index, double value);
        long double getFloat96 (unsigned int index);
        void setFloat96 (unsigned int index, long double value);
    private:
        unsigned int addr;
    };
};

#endif // QMODBUSREGISTERS_H
