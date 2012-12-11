#ifndef QMODBUS_H
#define QMODBUS_H

#if defined(QMODBUS_LIBRARY)
#  define QMODBUSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMODBUSSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "qmodbusmaster.h"
#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"

#endif // QMODBUS_H
