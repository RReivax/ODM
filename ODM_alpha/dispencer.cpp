#include "dispencer.h"

/**
 * @brief odm::Dispencer::Dispencer
 * @param parent
 */
odm::Dispencer::Dispencer(QObject *parent) : QObject(parent)
{

}

/**
 * Updates the realtime dataset.
 * @brief odm::Dispencer::processData
 * @param dataset
 */
void odm::Dispencer::processData(QVector<data_id> dataset){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    foreach (data_id tuple, dataset) {
        qDebug() << tuple.id << " --> " << tuple.data;
    }

    emit requestData();
}
