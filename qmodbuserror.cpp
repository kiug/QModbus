#include "modbus.h"
#include "qmodbuserror.h"

using namespace Modbus;

QModbusError::QModbusError ()
{
}

QModbusError::QModbusError (const QModbusError & other)
{
    error = other.error;
}

bool QModbusError::isValid ()
{
    return valid;
}

QString QModbusError::message ()
{
    return QString (modbus_strerror (error));
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
