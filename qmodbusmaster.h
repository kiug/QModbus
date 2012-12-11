#ifndef QMODBUSMASTER_H
#define QMODBUSMASTER_H

#include <QObject>

#if defined(QMODBUS_LIBRARY)
#  define QMODBUSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMODBUSSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "qmodbuserror.h"
#include "qmodbusbits.h"
#include "qmodbusregisters.h"

namespace Modbus
{
    class QModbusError;
    class QModbusBits;
    class QModbusRegisters;

    class QMODBUSSHARED_EXPORT QModbusMaster : public QObject
    {
        Q_OBJECT
    public:
        typedef enum
        {
            None = 0,//MODBUS_ERROR_RECOVERY_NONE
            Link = (1<<1),//MODBUS_ERROR_RECOVERY_LINK
            Protocol = (1<<2)//MODBUS_ERROR_RECOVERY_PROTOCOL
        } errorRecoveryMode;

        typedef enum
        {
            IllegalFunction = 0x01,//MODBUS_EXCEPTION_ILLEGAL_FUNCTION, // (1)
            IllegalDataAddress,// = MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS, // (2)
            IllegalDataValue,// = MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE, // (3)
            SlaveOrServerFailure,// = MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE, // (4)
            Acknowledge,// = MODBUS_EXCEPTION_ACKNOWLEDGE, // (5)
            SlaveOrServerBusy,// = MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY, // (6)
            NegativeAcknowledge,// = MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE, // (7)
            MemoryParity,// = MODBUS_EXCEPTION_MEMORY_PARITY, // (8)
            NotDefined,// = MODBUS_EXCEPTION_NOT_DEFINED, // (9)
            GatewayPath,// = MODBUS_EXCEPTION_GATEWAY_PATH, // (10)
            GatewayTarget// = MODBUS_EXCEPTION_GATEWAY_TARGET // (11)
        } modbusException;

        QModbusMaster (const char *ip, int port, QObject* parent = 0);
        QModbusMaster (const char *device, int baud, char parity, int dataBit, int stopBit, QObject* parent = 0);
        QModbusMaster (const char *node, const char *service, QObject* parent = 0);
        ~QModbusMaster ();
        QModbusError lastError ();
        void setSlave (int slave);
        void setBroadcast ();
        void connect ();
        void close ();
        void flush ();

        //Context setters and getters
        void getByteTimeout (long *sec, long *usec);
        void setByteTimeout (long sec, long usec);
        void setDebug (bool debug);
        void setErrorRecovery (errorRecoveryMode errorRecovery);
        int getHeaderLength (void);
        void getResponseTimeout (long *sec, long *usec);
        void setResponseTimeout (long sec, long usec);

        // Read data
        void readBits (QModbusBits &bits);
        void readInputBits (QModbusBits &bits);
        void readRegisters (QModbusRegisters &regs);
        void readInputRegisters (QModbusRegisters &regs);
        void reportSlaveId (quint8 *dest);

        // Write data
        void writeBit (QModbusBits &bit);
        void writeRegister (QModbusRegisters &reg);
        void writeBits (QModbusBits &bits);
        void writeRegisters (QModbusRegisters &regs);

        // Write and read data
        void writeAndReadRegisters (QModbusRegisters &writeRegs, QModbusRegisters &readRegs);

        // Raw requests
        void sendRawRequest (quint8 *rawReq, int rawReqLength);
        void receiveConfirmation (quint8 *rsp);

        // Reply an exception
        void replyException (quint8 *req, modbusException exceptionCode);

        //
        void setSocket (int socket);
        int getSocket (void);

        // Macros for data manipulation
        inline static const quint8 getHighByte (quint16 data);// extracts the high byte from a byte
        inline static const quint8 getLowByte (quint16 data);// extracts the low byte from a byte
        inline static const int getInt32FromInt16 (quint16 *data, int index);// builds an int32 from the two first int16 starting at tab_int16[index]
        inline static const short int getInt16FromInt8 (quint8 *data, int index);// builds an int16 from the two first int8 starting at tab_int8[index]
        inline static void setInt16ToInt8 (quint8 *data, int index, short int value);// set an int16 value into the two first bytes starting at tab_int8[index]

        // Functions for data manipulation
        inline static void setBitsFromByte (quint8 *dest, int index, const quint8 value);
        inline static void setBitsFromBytes (quint8 *dest, int index, unsigned int nb_bits, const quint8 *tab_byte);
        inline static void getByteFromBits (const quint8 *src, int index, unsigned int nb_bits);
        inline static const float getFloat (const quint16 *src);
        inline static void setFloat (float value, quint16 *dest);

    private:
        void *ctx;
        QModbusError *modbusError;
        //
        inline void checkContext (void *ctx);
        inline void checkOperationsReturnValue (int returnValue);
    };
};

#endif // QMODBUSMASTER_H
