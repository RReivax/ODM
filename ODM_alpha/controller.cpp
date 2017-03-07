#include "controller.h"

/**
 * @brief odm::Controller::Controller
 * @param parent
 */
odm::Controller::Controller(QObject *parent) : QThread(parent) {
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    receiver.moveToThread(&rThread);
    dispenser.moveToThread(&dThread);
    appsvbdd.moveToThread(&appsvbddThread);

    qRegisterMetaType<QVector<QJsonObject>>("QVector<QJsonObject>");
    QObject::connect(&dThread, SIGNAL(started()), &dispenser, SIGNAL(requestData()));
    QObject::connect(&rThread, SIGNAL(started()), &receiver, SLOT(startServer()));
    QObject::connect(&cliThread, SIGNAL(started()), &cli, SLOT(startReading()));

    QObject::connect(&dThread, SIGNAL(started()), &dispenser, SLOT(shareState()));


    QObject::connect(&dispenser, SIGNAL(requestData()), this, SIGNAL(queued_prepareData()));
    QObject::connect(&receiver, SIGNAL(noDataToTransfer()), this, SIGNAL(queued_prepareData()));
    QObject::connect(this, SIGNAL(queued_prepareData()), &receiver, SLOT(prepareData()));


    QObject::connect(&receiver, SIGNAL(transferData(QVector<QJsonObject>)), &dispenser, SLOT(processData(QVector<QJsonObject>)));

    //Application connection
    QObject::connect(&dispenser, &odm::Dispenser::dispenseState, &odm::Application::getState);
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

    cliThread.start();
    rThread.start();
    dThread.start();

    //apptesdThread.start();
    appsvbddThread.start();

    //apptest.test();
    appsvbdd.start();
}
