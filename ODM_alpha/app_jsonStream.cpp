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
        return false;
    }
}



bool app_jsonStream::defAppType()
{
    return true;
}

bool app_jsonStream::loopFct()
{
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

    return true;
}


bool app_jsonStream::closeApp()
{
    socket->disconnectFromHost();
    return true;
}

