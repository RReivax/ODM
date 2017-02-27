#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>
#include <application.h>

#include "data_id.h"
#include "receiver.h"
#include "dispenser.h"
#include "application.h"
#include "app_test.h"
#include "app_sv_bdd.h"
#include "app_map.h"

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

        //Applications
        app_test apptest;
        QThread apptestThread;

        app_sv_bdd appsvbdd;
        QThread appsvbddThread;
    };
}

#endif // CONTROLLER_H
