#include "controller.h"

/**
 * @brief odm::Controller::Controller
 * @param parent
 */
odm::Controller::Controller(QObject *parent) : QThread(parent) {
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    reciever.moveToThread(&rThread);
    dispencer.moveToThread(&tThread);

    qRegisterMetaType<QVector<data_id>>("QVector<data_id>");
    QObject::connect(&rThread, SIGNAL(started()), &reciever, SLOT(recieveData()));
    QObject::connect(&tThread, SIGNAL(started()), &dispencer, SIGNAL(requestData()));

    QObject::connect(&dispencer, SIGNAL(requestData()), this, SIGNAL(queued_prepareData()));
    QObject::connect(&reciever, SIGNAL(noDataToTransfer()), this, SIGNAL(queued_prepareData()));
    QObject::connect(this, SIGNAL(queued_prepareData()), &reciever, SLOT(prepareData()));

    QObject::connect(&reciever, SIGNAL(endOfReception()), this, SIGNAL(queued_recieveData()));
    QObject::connect(this, SIGNAL(queued_recieveData()), &reciever, SLOT(recieveData()));

    QObject::connect(&reciever, SIGNAL(transferData(QVector<data_id>)), &dispencer, SLOT(processData(QVector<data_id>)));
}

/**
 *
 * @brief odm::Controller::run
 */
void odm::Controller::run(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    this->exec();
}

/**
 * Starts the Controller then the Receiver and Dispencer threads.
 * @brief odm::Controller::launch
 */
void odm::Controller::launch(){
    this->moveToThread(this);
    this->start();

    rThread.start();
    tThread.start();
}

