#ifndef QMODBUSBITS_H
#define QMODBUSBITS_H

#include "qmodbus.h"
#include <QVector>

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusBits : public QVector <bool>
    {
        friend class QModbus;
    public:
        QModbusBits (unsigned int address, unsigned int number = 1);
        bool getValue (unsigned int index);
        void setValue (unsigned int index, bool value);
        unsigned int getNumber (void);
        void setNumber (unsigned int number);
        unsigned int getAddress (void);
        void setAddress (unsigned int address);
    private:
        unsigned int addr;
    };
};
#endif // QMODBUSBITS_H
