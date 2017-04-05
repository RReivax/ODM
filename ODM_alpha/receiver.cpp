/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "receiver.h"

/**
 * @brief odm::Receiver::Receiver
 * @param parent
 */
odm::Receiver::Receiver(QObject *parent) : QObject(parent) {
   tcpServer = new QTcpServer(this);

   connect(this, SIGNAL(dataReceived(QByteArray)), SLOT(stackData(QByteArray)));
   dc=0;
}

void odm::Receiver::startServer(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    if (!tcpServer->listen(/*QHostAddress::Any,667*/)){
        qDebug() << Q_FUNC_INFO <<  "Unable to start the server";
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i){
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel=tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                         .arg(ipAddress).arg(tcpServer->serverPort());
    qDebug() << Q_FUNC_INFO << statusLabel;
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
    qDebug() << tcpServer->serverAddress();
}

/**
 * Receives data from plugins and stack it.
 * @brief odm::Receiver::recieveData
 */

void odm::Receiver::newClient(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while(tcpServer->hasPendingConnections()){
        QTcpSocket* socket=tcpServer->nextPendingConnection();
        qDebug() << socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(InitClient()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}
/**
 * @brief odm::Receiver::InitClient
 *
 * Initialisation process with the pluggin
 */
void odm::Receiver::InitClient(){

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    QObject::disconnect(socket, SIGNAL(readyRead()), this, SLOT(InitClient()));
    bool error=false;
    QJsonObject newClient;

    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }
    if (!QJsonDocument::fromJson(*buffer).isNull()){
        qDebug() << "New new client";
        newClient = QJsonDocument::fromJson(*buffer).object();
        ///Debug
        qDebug() << newClient.value("name").toString();
        foreach (QString name, flightData.keys()) {
            qDebug()<<name<< "=="<<newClient.value("name").toString()<< "?";
            if(name == newClient.value("name").toString())
            {
                if(socket->write("ERROR")<0)
                    qDebug()<<"Fail to send Error message";
                socket->abort();
                error=true;
            }
        }
    }

    if(!error)
    {
        if(socket->write("SUCCESS")<0)
            qDebug()<<"Fail to send Success message";
        flightData[newClient.value("name").toString()].push(newClient);
        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    }
}

void odm::Receiver::disconnected(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    //Libère nom
    //qDebug()<<"all = "<<*buffer;
    qDebug()<<"name = "<<QJsonDocument::fromJson(*buffer).object().value("name").toString();
    toDelete.push_back(QJsonDocument::fromJson(*buffer).object().value("name").toString());
    //flightData[QJsonDocument::fromJson(*buffer).object().value("name").toString()]
    connect(&flightData[QJsonDocument::fromJson(*buffer).object().value("name").toString()],SIGNAL(StackEmpty()),this,SLOT(RemoveStack()));
    delete buffer;
    socket->deleteLater();
}

void odm::Receiver::readSocket(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);

    buffer->clear();
    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }

    if (!QJsonDocument::fromJson(*buffer).isNull()){
        QJsonObject newData = QJsonDocument::fromJson(*buffer).object();
        flightData[newData.value("name").toString()].push(newData);
    }
}
/**
 * Get top of stacks and transfer them if not empty.
 * @brief odm::Receiver::prepareData
 */
void odm::Receiver::prepareData(){
    //qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QVector<QJsonObject> dataset;

    for(QMap<QString, QJsonStack>::iterator i = flightData.begin(); i != flightData.end(); i++){
        if(!i.value().isEmptyEmitSignal())
            dataset.push_back(i.value().pop());
    }
    if(dataset.isEmpty()){
        //qDebug() << "No data to transfer";
        emit noDataToTransfer();
    }
    else{
        qDebug() << "Data transfer";
        emit transferData(dataset);
    }
}
void odm::Receiver::stackData(QByteArray toStack){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    qDebug() << toStack;
    if (!QJsonDocument::fromJson(toStack).isNull()){
            QMap<QString, QVariant> tmp = QJsonDocument::fromJson(toStack).object().toVariantMap();
    }
}
void odm::Receiver::RemoveStack()
{
    if(!toDelete.isEmpty())
    {
        foreach (QString name, toDelete) {
            if(flightData[name].toQStack().isEmpty()){
                qDebug()<<"Deleting : "<<name;
                emit stateToDelete(name);
                flightData.remove(name);
            }
        }
        toDelete.clear();
    }
}
void odm::Receiver::stopServer()
{

    foreach(QTcpSocket* sock, buffers.keys()){
        qDebug() << " NIK TA SOCKET";
        sock->disconnectFromHost();
        buffers.remove(sock);
    }
    qDebug() << " LE OUI ";
    this->tcpServer->deleteLater();
    qDebug() << " LE OUI OUI";
    emit readyToStop();
    //qDebug() << "Server is down.";
}
