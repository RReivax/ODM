#include "app_jsonStream.h"


app_jsonStream::app_jsonStream()
{

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

bool app_jsonStream::initApp()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(HOSTNAME,PORT);
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected to the TCP server";
    }
    return true;
}

bool app_jsonStream::closeApp()
{
    ///To be done
    return true;
}

