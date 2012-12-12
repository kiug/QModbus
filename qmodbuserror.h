#ifndef QMODBUSERROR_H
#define QMODBUSERROR_H

#include <QObject>

#include "modbus.h"
#include "qmodbus.h"

class QString;

namespace Modbus
{
    #define OUT_OF_RANGE_ENO (MODBUS_ENOBASE-1)
    #define OUT_OF_RANGE_MSG "Register index out of range"
    class QMODBUSSHARED_EXPORT QModbusError
    {
        friend class QModbusMaster;
        friend class QModbusBits;
        friend class QModbusRegisters;
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
