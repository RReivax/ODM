/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef Receiver_H
#define Receiver_H

#include <QtCore>
#include <QtNetwork>
#include "qjsonstack.h"


namespace odm {
    class Receiver : public QObject
    {
        Q_OBJECT

        public:
            explicit Receiver(QObject *parent = 0);
        signals:
            void transferData(QVector<QJsonObject>);
            void endOfReception();
            void noDataToTransfer();

            void dataReceived(QByteArray);
            void stateToDelete(QString);
            void readyToStop();
        public slots:
            void startServer();
            void stopServer();

            void newClient();
            void disconnected();
            void readSocket();
            void InitClient();
            void RemoveStack();
            void prepareData();
            void stackData(QByteArray toStack);
        private:
            QTcpServer *tcpServer;
            QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
            QString statusLabel;
            QStringList toDelete;
            QMap<QString,QJsonStack> flightData;
            int dc;

    };
}

#endif // Receiver_H
