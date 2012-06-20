#ifndef TESTQMODBUSSLAVE_H
#define TESTQMODBUSSLAVE_H

#include <QThread>

class TestQModbusSlave : public QThread
{
    Q_OBJECT
public:
    explicit TestQModbusSlave(QObject *parent = 0);
    void stop();

protected:
    void run();
private:
    volatile bool stopFlag;
};

#endif // TESTQMODBUSSLAVE_H
