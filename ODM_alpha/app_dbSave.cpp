#include "app_dbSave.h"

app_dbSave::app_dbSave()
{

}

void app_dbSave::start(){
    QThread::sleep(1);
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Start of app_dbSave on:";
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << Q_FUNC_INFO << QThread::currentThreadId();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if(this->get_conf()){
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Config file loaded";
    }
    else {
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "No config file loaded, default value are used";
    }

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

bool app_dbSave::get_conf(){
    QDomDocument dom;
    QDomNode node;
    QDomNode grandchild;
    QDomElement root;
    QDomElement elem;
    QDomElement elem2;
    QString n;
    QChar t;

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
    root = dom.documentElement();
    node = root.firstChild();
    while(!node.isNull()){
        elem = node.toElement();
        if(elem.tagName()=="connection_param"){
            grandchild = node.firstChild();
            while(!grandchild.isNull()){
                    elem2 = grandchild.toElement();
                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << elem2.tagName();
                    grandchild = grandchild.nextSibling();
                    if(elem2.tagName()=="DB_HOSTNAME")
                       DB_HOSTNAME=elem2.text();
                    if(elem2.tagName()=="DB_USERNAME")
                       DB_USERNAME=elem2.text();
                    if(elem2.tagName()=="DB_PASSWORD")
                       DB_PASSWORD=elem2.text();
                    if(elem2.tagName()=="DB_NAME")
                       DB_NAME=elem2.text();
            }
        }
        else if(elem.tagName()=="table_name"){
            grandchild = node.firstChild();
            while(!grandchild.isNull()){
                    elem2 = grandchild.toElement();
                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << elem2.tagName();
                    grandchild = grandchild.nextSibling();
                    if(elem2.tagName()=="TABLE_LAT")
                       TABLE_LAT=elem2.text();
                    if(elem2.tagName()=="TABLE_ALT")
                       TABLE_ALT=elem2.text();
                    if(elem2.tagName()=="TABLE_DTE")
                       TABLE_DTE=elem2.text();
                    if(elem2.tagName()=="TABLE_ID")
                       TABLE_ID=elem2.text();
                    if(elem2.tagName()=="TABLE_LONG")
                       TABLE_LONG=elem2.text();
            }
        }
        else
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << elem.tagName();
        node = node.nextSibling();
    }
    return true;
}

bool app_dbSave::init(){
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

void app_dbSave::loop(){
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
