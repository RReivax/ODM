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

    //receiveData();
    //for testing purposes in dispenser
   /* QByteArray val;
    //QFile file("C:/Users/Gauthier/Documents/Scolaire/ING4/PPE/Git/build-ODM_alpha-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/test.json");
    QFile file("C:/Users/Xavier/Desktop/test.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << Q_FUNC_INFO << file.error();
        return;
    }else{
        val = file.readAll();
        file.close();
        qWarning() << val;
        QJsonDocument d = QJsonDocument::fromJson(val);
        QJsonObject test = d.object();
        flightData[test.value("name").toString()].push(test);
        qDebug() << "Lat = " << flightData["ThisIsMyName"].top()["latitude"].toDouble();
    }*/
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
        connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
        //connect(socket, SIGNAL(readyRead()), this, SLOT(InitClient()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}

void odm::Receiver::InitClient(){
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    //foreach flightData.keys()

    if(true){
       // QObject::disconnect();
       // QObject::connect(...., readSocket);
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
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);

    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
    }

    if (!QJsonDocument::fromJson(*buffer).isNull()){
        qDebug() << "New object";
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
    //qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QVector<QJsonObject> dataset;

    for(QMap<QString, QStack<QJsonObject>>::iterator i = flightData.begin(); i != flightData.end(); i++){
        if(!i.value().isEmpty()) dataset.push_back(i.value().pop());
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

