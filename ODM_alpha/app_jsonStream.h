/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef APP_MAP_H
#define APP_MAP_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "application.h"

/**
 * @class app_jsonStream
 * @brief Used to send data via a TCP socket to a specified server
 *
 * Every TIME_LAPS seconds, the function will send to the server all the actual infos of UAVs (the state vector)
 */
class app_jsonStream : public odm::Application
{
    Q_OBJECT

public:
        app_jsonStream();



   public slots:

        /** @fn void app_jsonStream::initApp()
             *  @brief will try to connect to the TCP server with the given ip and port.
             *  @return true if we could connect to the server.
             *          false if we could not connect.
             */
        bool initApp();


        /** @fn void app_jsonStream::defAppType()
         * @brief specifies that the application is loop-based.
         * @return true
         */
        bool defAppType();

        /**
         * @brief loopFct sends the UAVs infos to the server as a json stream.
         * @return true
         */
        bool loopFct();

        /**
         * @brief closeApp disconnects from the host.
         * @return true
         */
        bool closeApp();


    private:

        /**
         * @brief Connection variables
         * The hostname and the port of the server to which the socket will connect
         */
        const QString HOSTNAME="localhost";
        const qint16 PORT=7070;


        const int TIME_LAPS = 1;

        QTcpSocket *socket;


};
#endif
