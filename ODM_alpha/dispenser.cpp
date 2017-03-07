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
