#include "app_jsonStream.h"


app_jsonStream::app_jsonStream()
{


}

void app_jsonStream::start()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(HOSTNAME,PORT);
    is_running = true;
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected to the TCP server";
        this->loop();
    }

}

void app_jsonStream::loop()
{
    qDebug() << "App loop";

    while(is_running){
        //socket->write(QString("{\"latitude\":250}").toLatin1().data());
        //socket->waitForBytesWritten(1000);

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
    }
}

bool app_jsonStream::init()
{
    return true;
}

