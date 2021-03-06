/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "app_dbSave.h"

app_dbSave::app_dbSave()
{

}

bool app_dbSave::initApp(){
    bool correctInit=true;
    is_running=true;
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Start of app_dbSave on:";
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << Q_FUNC_INFO << QThread::currentThreadId();
    db = QSqlDatabase::addDatabase("QMYSQL");
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
        correctInit = this->init();
    }
    else
    {
        correctInit=false;
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Connecion failed";
        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << db.lastError().text();
    }

    return correctInit;
}

bool app_dbSave::defAppType(){
    return true;
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

    QFile config("config_db.xml");
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
    QSqlQuery query_create;
    bool return_b = false;
    query_create.prepare("CREATE TABLE main (id"+TABLE_ID+" text, "+TABLE_LONG+" double, "+TABLE_LAT+" double, "+TABLE_ALT+" double, position"+TABLE_DTE+" datetime);");

    if(query.exec("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'odm_db' AND TABLE_NAME = 'main';"))
    {
        if(query.next()){
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "The DB table 'main' exists !";
            return_b = true;
        }
        else {
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Trying to create table 'main'...";
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "CREATE TABLE main (id"+TABLE_ID+" text, "+TABLE_LONG+" double, "+TABLE_LAT+" double, "+TABLE_ALT+" double, position"+TABLE_DTE+" datetime);";
            if (query_create.exec()){
                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "created";
                return_b = true;
            }
            else
            {
                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Error while creating the table.";
                if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << query_create.lastError().text();
            }
        }
    }
    return return_b;
}


bool app_dbSave::loopFct(){
    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "loopFct";
    QSqlQuery query_insert;
    query_insert.prepare("INSERT INTO `main`(`id"+TABLE_ID+"`, `"+TABLE_LONG+"`, `"+TABLE_LAT+"`, `"+TABLE_ALT+"`, `position"+TABLE_DTE+"`) VALUES (:id_v,:long_v,:lat_v,:alt_v,:date_v)");
    QString id_drone, longitude, latitude, altitude, date;
        if(updateState()){
            if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "updateState";
            for(int i=0 ; i<state.length() ; i++){

                id_drone = state[i].take(TABLE_ID).toString();
                longitude = state[i].take(TABLE_LONG).toString();
                latitude = state[i].take(TABLE_LAT).toString();
                altitude = state[i].take(TABLE_ALT).toString();
                date = state[i].take(TABLE_DTE).toString();

                if(!lastUpadate.contains(id_drone) || lastUpadate[id_drone]!=date){
                    lastUpadate.insert(id_drone, date);

                    query_insert.bindValue(":id_v", id_drone);
                    query_insert.bindValue(":long_v", longitude);
                    query_insert.bindValue(":lat_v", latitude);
                    query_insert.bindValue(":alt_v", altitude);
                    query_insert.bindValue(":date_v", date);

                    if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "INSERT INTO `main`(`id"+TABLE_ID+"`, `"+TABLE_LONG+"`, `"+TABLE_LAT+"`, `"+TABLE_ALT+"`, `positiondate`) VALUES ("+id_drone+","+longitude+","+latitude+","+altitude+","+date+")";
                    if(query_insert.exec())
                    {
                        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Insert success";
                    }
                    else{
                        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << "Insert Failed !";
                        if (DEBUG_ENABLE) qDebug() << MARKER_DEBUG << query_insert.lastError().text();
                    }
                }
            }
        }
        QThread::sleep(TIME_LAPS);
    return false;
}


bool app_dbSave::closeApp(){
    is_running=false;
    db.close();
    return true;
}
