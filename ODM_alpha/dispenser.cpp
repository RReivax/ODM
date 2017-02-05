#include "dispenser.h"

/**
 * @brief odm::dispenser::dispenser
 * @param parent
 */
odm::Dispenser::Dispenser(QObject *parent) : QObject(parent)
{
    state = QVector<QMap<QString, QVariant>>();
    initStateParams();
}

/**
 * Creates the state vector depending on the 
 * @brief odm::Dispenser::initDataStructure
 */

void odm::Dispenser::initStateParams(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QFile config("C:/Users/Gauthier/Documents/Scolaire/ING4/PPE/Git/ODM_alpha/config.xml");
    QDomDocument dom;
    QDomNode node;
    QDomElement docElem;
    QDomElement elem;
    QString n;
    //QVariant t;

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
            qDebug() << Q_FUNC_INFO << n;
            //t = elem.attribute("type"); unused value type, is it necessary?
            params.insert(n,QVariant());
        }
        node = node.nextSibling();
    }
}

/**
 * Updates the realtime dataset.
 * @brief odm::dispenser::processData
 * @param dataset
 */
void odm::Dispenser::processData(QVector<data_id> dataset){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    foreach (data_id tuple, dataset) {
        qDebug() << tuple.id << " --> " << tuple.data;
    }

    emit requestData();
}

/**
 * Sends the realtime vector reference to an application.
 * @brief odm::Dispenser::shareStacks
 */

void odm::Dispenser::shareState(){

}
