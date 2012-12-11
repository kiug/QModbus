#ifndef QMODBUSERROR_H
#define QMODBUSERROR_H

#include "qmodbusmaster.h"

class QString;

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusError
    {
        friend class QModbusMaster;
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
