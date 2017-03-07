#include "app_dbSave.h"

app_bdSave::app_bdSave()
{

}

void app_bdSave::start(){
    QThread::sleep(1);
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Start of app_dbSave on:";
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << Q_FUNC_INFO << QThread::currentThreadId();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if(get_conf())
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Config file loaded";
    else if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "No config file loaded, default value are used";

    db.setHostName(DB_HOSTNAME);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);
    db.setDatabaseName(DB_NAME);
    if(db.open())
    {
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Connected to:";
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << db.hostName();
        is_running = true;
        if(this->init())
            this->loop();
    }
    else
    {
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Connecion failed";
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << db.lastError().text();
    }
    db.close();
}

bool app_bdSave::get_conf(){
    QFile config("C:/Users/Arnaud/Documents/ECE/ING4/PPE/ODM_alpha/config_db.xml");
    if(!config.open(QIODevice::ReadOnly)){
        if (DEBUG_ENABLE)
            qDebug() << Q_FUNC_INFO << config.error();
        return false;
    }
    else {
        if(!dom.setContent(&config)){
            if (DEBUG_ENABLE)
                qDebug() << Q_FUNC_INFO << "File error 2";
            config.close();
            return false;
        }
    }
    config.close();


}

bool app_bdSave::init(){
    QSqlQuery query;
    bool return_b = false;
    if(query.exec("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'odm_db' AND TABLE_NAME = 'main';"))
    {
        if(query.next()){
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "The DB table 'main' exists !";
            return_b = true;
        }
        else {
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Trying to create table 'main'...";
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "CREATE TABLE main ("+TABLE_ID+" int, "+TABLE_LONG+" double, "+TABLE_LAT+" double, "+TABLE_ALT+" double, position"+TABLE_DTE+" datetime);";
            if (query.exec("CREATE TABLE main ("+TABLE_ID+" int, "+TABLE_LONG+" double, "+TABLE_LAT+" double, "+TABLE_ALT+" double, position"+TABLE_DTE+" datetime);"))
            {
                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "created";
                return_b = true;
            }
            else
                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Error while creating the table.";
        }
    }
    return return_b;
}

void app_bdSave::loop(){
    QSqlQuery query;
    QString id_drone, longitude, latitude, altitude, date;
    while(is_running){
        if(updateState()){
            for(int i=0 ; i<state.length() ; i++){
                id_drone = state[i].take(TABLE_ID).toString();
                longitude = state[i].take(TABLE_LONG).toString();
                latitude = state[i].take(TABLE_LAT).toString();
                altitude = state[i].take(TABLE_ALT).toString();
                date = state[i].take(TABLE_DTE).toString();

                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "INSERT INTO `main`(`"+TABLE_ID+"`, `"+TABLE_LONG+"`, `"+TABLE_LAT+"`, `"+TABLE_ALT+"`, `positiondate`) VALUES ("+id_drone+","+longitude+","+latitude+","+altitude+",\""+date+"\")";
                if(query.exec("INSERT INTO `main`(`"+TABLE_ID+"`, `"+TABLE_LONG+"`, `"+TABLE_LAT+"`, `"+TABLE_ALT+"`, `positiondate`) VALUES ("+id_drone+","+longitude+","+latitude+","+altitude+",\""+date+"\")"))
                {
                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Insert success";
                }
                else{
                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Insert Failed !";
                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << query.lastError().text();
                }
            }
        }
        QThread::sleep(TIME_LAPS);
    }
}
