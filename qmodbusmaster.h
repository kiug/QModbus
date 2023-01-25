/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef QMODBUSMASTER_H
#define QMODBUSMASTER_H

#include "qmodbus.h"
#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"

namespace Modbus
{
    class QMODBUSSHARED_EXPORT QModbusMaster : public QObject
    {
        Q_OBJECT
    public:
        QModbusMaster (const char *ip, int port, QObject* parent = 0);
        QModbusMaster (const char *device, int baud, char parity, int dataBit, int stopBit, QObject* parent = 0);
        QModbusMaster (const char *node, const char *service, QObject* parent = 0);
        ~QModbusMaster ();
        /*! Returns currently set modbus error, updated in last API call. */
        inline const QModbusError & lastError () const { return modbusError; }
        /*! Sets the slave ID. */
        bool setSlave (int slave);
        bool setBroadcast ();
        bool connect();
        void close ();
        bool flush();

        //Context setters and getters
        bool getByteTimeout (uint32_t *sec, uint32_t *usec);
        bool setByteTimeout(uint32_t sec, uint32_t usec);
        bool setDebug(bool debug);
        bool setErrorRecovery (errorRecoveryMode errorRecovery);
        int getHeaderLength (void);
        bool getResponseTimeout(uint32_t *sec, uint32_t *usec);
        bool setResponseTimeout(uint32_t sec, uint32_t usec);

        // Read data
        bool readBits(QModbusBits &bits);
        bool readInputBits(QModbusBits &bits);
        bool readRegisters(QModbusRegisters &regs);
        bool readInputRegisters(QModbusRegisters &regs);
        bool reportSlaveId(quint8 *dest);

        // Write data
        bool writeBit(QModbusBits &bit);
        bool writeRegister(QModbusRegisters &reg);
        bool writeBits(QModbusBits &bits);
        bool writeRegisters(QModbusRegisters &regs);

        // Write and read data
        bool writeAndReadRegisters(QModbusRegisters &writeRegs, QModbusRegisters &readRegs);

    private:
        void *ctx;
        QModbusError modbusError;
        bool connected;
        /*! Checks for errno set by libmodus and configures modbusError accordingly. */
        void checkContext (void *ctx);
        /*! Checks if connection is established. If connected clears last error and returns true,
            otherwise returns false and sets last error to NOT_CONNECTED_ENO.
        */
        bool checkConnection ();
        /*! Checks if return value is != 0, and if so, sets the errno set by libmodbus and its message
            as last modbusError.
            \return Returns true, if returnValue == 0, or false, if != 0 (error).
        */
        bool checkOperationsReturnValue(int returnValue);
    };
};

#endif // QMODBUSMASTER_H
