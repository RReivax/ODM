/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
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
        void quit_all();
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
        app_dbSave appdbSave;
        QThread appdbSaveThread;
        app_jsonStream appjsonStream;
        QThread appjsonStreamThread;
    };
}

#endif // CONTROLLER_H
