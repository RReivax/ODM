#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

#include "receiver.h"
#include "dispenser.h"
#include "cli.h"

#include "application.h"
#include "app_sv_bdd.h"
#include "app_map.h"


namespace odm{
    class Controller : public QThread
    {
        Q_OBJECT
    public:
        explicit Controller(QObject *parent = 0);
        void launch();
        void launchAll();
        virtual void run();
    signals:
        void queued_receiveData();
        void queued_prepareData();
    private:
        QThread rThread;
        QThread dThread;
        QThread cliThread;
        Receiver receiver;
        Dispenser dispenser;
        CLI cli;

        //Applications
        app_sv_bdd appsvbdd;
        QThread appsvbddThread;
    };
}

#endif // CONTROLLER_H
