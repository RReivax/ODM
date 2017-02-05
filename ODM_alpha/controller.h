#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

#include "data_id.h"
#include "receiver.h"
#include "dispenser.h"

namespace odm{
    class Controller : public QThread
    {
        Q_OBJECT
    public:
        explicit Controller(QObject *parent = 0);
        void launch();
        virtual void run();
    signals:
        void queued_receiveData();
        void queued_prepareData();
    private:
        QThread rThread;
        QThread tThread;
        Receiver receiver;
        Dispenser dispenser;
    };
}

#endif // CONTROLLER_H
