#include "receiver.h"

/**
 * @brief odm::Receiver::Receiver
 * @param parent
 */
odm::Receiver::Receiver(QObject *parent) : QObject(parent) {
   tcpServer = new QTcpServer(this);
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
    connect(tcpServer, SIGNAL(newConnection()), this, SIGNAL(gotData()));
    qDebug() << tcpServer->serverAddress();

    //receiveData();
    //for testing purposes in dispenser
    QByteArray val;
    QFile file("C:/Users/Gauthier/Documents/Scolaire/ING4/PPE/Git/build-ODM_alpha-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/test.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << Q_FUNC_INFO << file.error();
        return;
    }else{
        val = file.readAll();
        file.close();
        qWarning() << val;
        QJsonDocument d = QJsonDocument::fromJson(val);
        QJsonObject test = d.object();
        QStack<data_id> s;
        s.push(data_id(1, test));
        stacks.append(s);
    }
}

/**
 * Receives data from plugins and stack it.
 * @brief odm::Receiver::recieveData
 */
void odm::Receiver::receiveData(){
    QTcpSocket* connection=tcpServer->nextPendingConnection();
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    if(connection!=0)
    {
         qDebug() << connection;
    }
    //emit endOfReception();
}

/**
 * Get top of stacks and transfer them if not empty.
 * @brief odm::Receiver::prepareData
 */
void odm::Receiver::prepareData(){
    //qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QVector<data_id> dataset;

    for(int i = 0; i < stacks.size(); i++){
        if(!stacks[i].isEmpty()) dataset.push_back(stacks[i].pop());
    }

    if(dataset.isEmpty())
        emit noDataToTransfer();
    else
        emit transferData(dataset);
}

void odm::Receiver::initTransfer(QHostAddress host){

}

void odm::Receiver::stackData(data_id toStack){

}
