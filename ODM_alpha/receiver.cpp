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
    if (!tcpServer->listen()){
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

    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }
    if (!QJsonDocument::fromJson(*buffer).isNull()){
        qDebug() << "New new client";
        QJsonObject newClient = QJsonDocument::fromJson(*buffer).object();
        for( QList<QString>::Iterator name = flightData.keys().begin(); name!= flightData.keys().end() ; name++ )
        {
            if(*name == newClient.value("name").toString())
            {
                if(socket->write("ERROR")<0)
                    qDebug()<<"Fail to send Error message";
                socket->abort();
                error=true;
            }
        }
    }
    buffer->clear();

    if(!error)
    {
        if(socket->write("SUCCESS")<0)
            qDebug()<<"Fail to send Success message";
        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    }
}

void odm::Receiver::disconnected(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    socket->deleteLater();
    //Libère nom
    delete buffer;
}

void odm::Receiver::readSocket(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    dc++;
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);

    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }

    if (!QJsonDocument::fromJson(*buffer).isNull()){
        qDebug() << "New object";
        QJsonObject newData = QJsonDocument::fromJson(*buffer).object();
        flightData[newData.value("name").toString()].push(newData);
        qDebug() << "Size = " << flightData[newData.value("name").toString()].size();
    }
    qDebug() << "Count = " << dc;
    buffer->clear();
}

/**
 * Get top of stacks and transfer them if not empty.
 * @brief odm::Receiver::prepareData
 */
void odm::Receiver::prepareData(){
    //qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QVector<QJsonObject> dataset;

    for(QMap<QString, QStack<QJsonObject>>::iterator i = flightData.begin(); i != flightData.end(); i++){
        if(!i.value().isEmpty())dataset.push_back(i.value().pop());
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

void odm::Receiver::stopServer(){
    this->tcpServer->close();
    emit readyToStop();
    qDebug() << "Server is down.";
}
