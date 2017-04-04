/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "dispenser.h"

odm::Dispenser::Dispenser(QObject *parent) : QObject(parent)
{
    state = QVector<QVariantMap>();
    initStateParams();
}

void odm::Dispenser::initStateParams(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QFile config("C:/Users/Arnaud/Documents/ECE/ING4/PPE/ODM_alpha/config.xml");
    QDomDocument dom;
    QDomNode node;
    QDomElement docElem;
    QDomElement elem;
    QString n;
    QChar t;

    if(!config.open(QIODevice::ReadOnly)){
        qDebug() << Q_FUNC_INFO << config.error();
        return;
    }else{
        if(!dom.setContent(&config)){
            qDebug() << Q_FUNC_INFO << "File error 2";
            config.close();
            return;
        }
    }
    config.close();
    docElem = dom.documentElement();
    node = docElem.firstChild();
    while(!node.isNull()){
        elem = node.toElement();
        n = elem.attribute("name", "notFound");
        if(n != "notFound"){
            t = elem.attribute("type", " ").at(0);
            if(t != ' '){
                params.insert(n, t);
            }
        }
        node = node.nextSibling();
    }
    QMapIterator<QString, QChar> i(params);
    while(i.hasNext()){
        i.next();
        qDebug() << i.key() << "-->" << i.value();
    }
}

/**
 * Updates the realtime dataset.
 * @brief odm::dispenser::processData
 * @param dataset
 */
void odm::Dispenser::processData(QVector<QJsonObject> dataset){
    QVariantMap tmp;
    int i;
    bool idExists = false;

    QWriteLocker write_lock(&lock);

    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    foreach (QJsonObject tuple, dataset) {
        tmp = tuple.toVariantMap();

        //converting param date to QDate
        if(tmp["date"].canConvert<QDateTime>()){
            tmp["date"] = tmp["date"].toDateTime();
            //setting the most recent value for id as real time
            for(i=0;i<state.size();i++){
                if(tmp["name"] == state[i]["name"]){
                    if(tmp["date"] > state[i]["date"]){
                        state[i] = tmp;
                    }
                    idExists = true;
                }
            }
            if(!idExists){
                state.append(tmp);
                QMapIterator<QString, QVariant> it = QMapIterator<QString, QVariant>(tmp);
                while(it.hasNext()){
                    it.next();
                    qDebug() << it.key() << "-->" << it.value();
                }
            }
            tmp.clear();
        }else{
            qDebug() << "Date format error";
        }
    }

    /*

    //debugging
    QMap<QString, QVariant> param;
    foreach (param, state) {
        QMapIterator<QString, QVariant> it = QMapIterator<QString, QVariant>(param);
        while(it.hasNext()){
            it.next();
            qDebug() << it.key() << "-->" << it.value();
        }
    }*/

    emit requestData();
}


void odm::Dispenser::shareState(){
    emit dispenseState(&state, &lock);
}

void odm::Dispenser::removeState(QString name)
{
    qDebug()<<"Removing State: "<<name;
    for(int i=0;i<state.size();i++)
    {
        if(state[i]["name"]==name)
        {
            qDebug()<<"Removed State: "<<state[i]["name"];
            state.removeAt(i);
            break;
        }
    }
}
