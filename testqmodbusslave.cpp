#include "testqmodbusslave.h"

#include <modbus.h>
#include <QDebug>

TestQModbusSlave::TestQModbusSlave(QObject *parent) : QThread(parent), stopFlag(false)
{
}

void TestQModbusSlave::stop()
{
    stopFlag = true;
    wait();
}

void TestQModbusSlave::run()
{
    /* your thread implementation goes here */
    int socket;
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;

    qDebug() << "TestQModbusSlave::run()";
    ctx = modbus_new_tcp("127.0.0.1", 502);
    /* modbus_set_debug(ctx, TRUE); */

    mb_mapping = modbus_mapping_new(5000, 5000, 5000, 5000);
    if (mb_mapping == NULL) {
        //fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        qDebug() << "Failed to allocate the mapping:" << QString(modbus_strerror(errno));
        modbus_free(ctx);
        return;
    }

    socket = modbus_tcp_listen(ctx, 1);
    modbus_tcp_accept(ctx, &socket);

    for (;;)
    {
        for (;;) {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc;

            rc = modbus_receive(ctx, query);
            if (rc != -1) {
                /* rc is the query size */
                modbus_reply(ctx, query, rc, mb_mapping);
            } else {
                /* Connection closed by the client or error */
                //printf("Quit the loop: %s\n", modbus_strerror(errno));
                //qDebug() << "Quit the loop:", QString(modbus_strerror(errno));
                break;
                ///qDebug() << "QModbusSlave ERROR:", QString(modbus_strerror(errno));
            }

        }
        if (stopFlag)
        {
            break;
        }
    }
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);
    qDebug() << "TestQModbusSlave::stop()";
}
