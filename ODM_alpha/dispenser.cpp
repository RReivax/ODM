#include "dispenser.h"

/**
 * @brief odm::dispenser::dispenser
 * @param parent
 */
odm::Dispenser::Dispenser(QObject *parent) : QObject(parent)
{


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
