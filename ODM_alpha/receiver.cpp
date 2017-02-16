#include "receiver.h"

/**
 * @brief odm::Receiver::Receiver
 * @param parent
 */
odm::Receiver::Receiver(QObject *parent) : QObject(parent) {
   tcpServer = new QTcpServer(this);
   connect(this, SIGNAL(dataReceived(QByteArray)), SLOT(stackData(QByteArray)));
}

void odm::Receiver::startServer(){
    if (!tcpServer->listen()) {
        qDebug() << Q_FUNC_INFO <<  "Unable to start the server";
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
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

    recieveData();
}

/**
 * Receives data from plugins and stack it.
 * @brief odm::Receiver::recieveData
 */
void odm::Receiver::recieveData(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    //emit endOfReception();
}

void odm::Receiver::newClient(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while(tcpServer->hasPendingConnections()){
        QTcpSocket* socket=tcpServer->nextPendingConnection();

        qDebug() << socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}

void odm::Receiver::disconnected(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    socket->deleteLater();
    delete buffer;
}

void odm::Receiver::readSocket(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);

    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }

    if (!QJsonDocument::fromJson(*buffer).isNull()){
        QJsonObject newData = QJsonDocument::fromJson(*buffer).object();
        flightData["test"].push(newData);
        flightData[newData.value("name").toString()].push(newData);
    }
    buffer->clear();
}

/**
 * Get top of stacks and transfer them if not empty.
 * @brief odm::Receiver::prepareData
 */
void odm::Receiver::prepareData(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QVector<QJsonObject> dataset;

    for(QMap<QString, QStack<QJsonObject>>::iterator i = flightData.begin(); i != flightData.end(); i++){
        if(i.value().isEmpty()) dataset.push_back(i.value().pop());
    }

    if(dataset.isEmpty()){
        qDebug() << "No data to transfer";
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

