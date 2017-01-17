#include "receiver.h"

odm::Receiver::Receiver(QObject *parent) : QObject(parent)
{

}

void odm::Receiver::recieveData(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    emit endOfReception();
}

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
