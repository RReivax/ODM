#include "app_map.h"
extern const QString MAP_LAT = "Latitude";
extern const QString MAP_ID = "name";
extern const QString MAP_LNG = "Longitude";


app_map::app_map()
{


}

void app_map::start()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(HOSTNAME,PORT);
    is_running = true;
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected to the map server";
        this->loop();
    }

}

void app_map::loop()
{
    qDebug() << "App loop";

    while(is_running){
        if(updateState()){
            if(state.length() > 0){
                for(int i = 0;i<state.length();i++){
                    QString data = "{ \"id\":\""+ state[i][MAP_ID].toString() + "\" ,\"latitude\":"+state[i][MAP_LAT].toString()+", \"longitude\":"+state[i][MAP_LNG].toString()+"}";
                    socket->write(data.toLatin1().data());
                    socket->waitForBytesWritten(1000);
                    qDebug() << data;
                }
            }
        }
        else{
            qDebug() << "No updates";
        }
        QThread::sleep(TIME_LAPS);
    }
}

bool app_map::init()
{
    return true;
}

