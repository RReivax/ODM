#include "controller.h"

/**
 * @brief odm::Controller::Controller
 * @param parent
 */
odm::Controller::Controller(QObject *parent) : QThread(parent) {
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    receiver.moveToThread(&rThread);
    dispenser.moveToThread(&tThread);

    qRegisterMetaType<QVector<data_id>>("QVector<data_id>");
    QObject::connect(&rThread, SIGNAL(started()), &receiver, SLOT(receiveData()));
    QObject::connect(&tThread, SIGNAL(started()), &dispenser, SIGNAL(requestData()));

    QObject::connect(&dispenser, SIGNAL(requestData()), this, SIGNAL(queued_prepareData()));
    QObject::connect(&receiver, SIGNAL(noDataToTransfer()), this, SIGNAL(queued_prepareData()));
    QObject::connect(this, SIGNAL(queued_prepareData()), &receiver, SLOT(prepareData()));
    QObject::connect(&receiver, SIGNAL(gotData()), this, SIGNAL(queued_receiveData()));
    QObject::connect(this, SIGNAL(queued_receiveData()), &receiver, SLOT(receiveData()));

    QObject::connect(&receiver, SIGNAL(transferData(QVector<data_id>)), &dispenser, SLOT(processData(QVector<data_id>)));
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
 * Starts the Controller then the Receiver and Dispenser threads.
 * @brief odm::Controller::launch
 */
void odm::Controller::launch(){
    this->moveToThread(this);
    this->start();

    rThread.start();
    tThread.start();
}

