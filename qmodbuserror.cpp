#include "modbus.h"
#include "qmodbuserror.h"
#include <QString>

using namespace Modbus;

QModbusError::QModbusError ()
{
    clear ();
}

QModbusError::QModbusError (const QModbusError & other)
{
    error = other.error;
    valid = other.valid;
}

bool QModbusError::isValid ()
{
    return valid;
}

QString QModbusError::message ()
{
    if (error == MODBUS_ENOBASE-1) {
        return QString (OUT_OF_RANGE_MSG);
    }
    else {
        return QString (modbus_strerror (error));
    }
}

void QModbusError::set (int errnum)
{
    error = errnum;
    valid = true;
}

void QModbusError::clear ()
{
    error = 0;
    valid = false;
}
