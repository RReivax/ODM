#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtCore>

#include "qjsonstack.h"
#include "receiver.h"
#include "dispenser.h"
#include "cli.h"

#include "application.h"
#include "app_dbSave.h"
#include "app_jsonStream.h"

namespace odm{
    class Controller : public QThread
    {
        Q_OBJECT
        Q_ENUMS(Keywords)

    public:
        explicit Controller(QObject *parent = 0);
        void launch();
        void launchAll();
        virtual void run();

        enum Keywords{
            EXIT, QUIT, HELP, SERVER, DBSAVE, JSONSTREAM, START, STOP, RESTART, SET
        };

    signals:
        void stopServer();

        void queued_receiveData();
        void queued_prepareData();
    public slots:
        void processCommand(QString cmd);
    private:
        QThread rThread;
        QThread dThread;
        QThread cliThread;
        Receiver receiver;
        Dispenser dispenser;
        CLI cli;

        //Applications
        //app_dbSave appdbSave;
        QThread appdbSaveThread;
        //app_jsonStream appjsonStream;
        QThread appjsonStreamThread;
    };
}

#endif // CONTROLLER_H
