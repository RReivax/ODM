/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "app_jsonStream.h"


app_jsonStream::app_jsonStream()
{

}

bool app_jsonStream::initApp()
{

    socket = new QTcpSocket(this);
    socket->connectToHost(HOSTNAME,PORT);

    qDebug() << "Connecting to the Server " << HOSTNAME << "on port " << PORT ;
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected to " << HOSTNAME << "on port "<< PORT;
        return true;
    }
    else
    {
        qDebug() << "could not connect to the TCP server...";
        socket->disconnectFromHost();
        return false;
    }
}



bool app_jsonStream::defAppType()
{
    return true;
}

bool app_jsonStream::loopFct()
{
    //qDebug() << "Loop Fct";
    if(updateState()){
        if(state.length() > 0){
            for(int i = 0;i<state.length();i++){

                QJsonDocument data(QJsonObject::fromVariantMap(state[i]));
                socket->write(data.toJson(QJsonDocument::Compact));
                socket->waitForBytesWritten(-1);
                qDebug() << data.toJson(QJsonDocument::Compact);
            }
        }
    }
    else{
        qDebug() << "No updates";
    }
    QThread::sleep(TIME_LAPS);

    return false;
}


bool app_jsonStream::closeApp()
{
    socket->disconnectFromHost();

    return true;
}

