#include "receiver.h"

/**
 * @brief odm::Receiver::Receiver
 * @param parent
 */
odm::Receiver::Receiver(QObject *parent) : QObject(parent)
{

}

/**
 * Receives data from plugins and stack it.
 * @brief odm::Receiver::recieveData
 */
void odm::Receiver::recieveData(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    emit endOfReception();
}

/**
 * Get top of stacks and transfer them if not empty.
 * @brief odm::Receiver::prepareData
 */
void odm::Receiver::prepareData(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QVector<data_id> dataset;

    for(int i = 0; i < stacks.size(); i++){
        if(!stacks[i].isEmpty()) dataset.push_back(stacks[i].pop());
    }

    if(dataset.isEmpty())
        emit noDataToTransfer();
    else
        emit transferData(dataset);
}
