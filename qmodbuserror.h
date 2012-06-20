#ifndef QMODBUSERROR_H
#define QMODBUSERROR_H

#include "qmodbus.h"

class QString;

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusError
    {
        friend class QModbus;
    public:
        QModbusError ();
        QModbusError (const QModbusError & other);
        bool isValid ();
        QString message ();
    private:
        void set (int errnum);
        void clear ();
        int error;
        bool valid;
    };
};

#endif // QMODBUSERROR_H
