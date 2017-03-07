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

    QObject::connect(&dThread, SIGNAL(started()), &dispenser, SLOT(shareState()));


    QObject::connect(&dispenser, SIGNAL(requestData()), this, SIGNAL(queued_prepareData()));
    QObject::connect(&receiver, SIGNAL(noDataToTransfer()), this, SIGNAL(queued_prepareData()));
    QObject::connect(this, SIGNAL(queued_prepareData()), &receiver, SLOT(prepareData()));


    QObject::connect(&receiver, SIGNAL(transferData(QVector<QJsonObject>)), &dispenser, SLOT(processData(QVector<QJsonObject>)));

    //CLI message transmition
    QObject::connect(&cli, SIGNAL(passCommand(QString)), this, SLOT(processCommand(QString)));

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
 * Starts the Controller then the CLI, Receiver and Dispenser threads.
 * @brief odm::Controller::launchAll
 */
void odm::Controller::launchAll(){
    this->moveToThread(this);
    this->start();

    cli.startReading();

    rThread.start();
    dThread.start();

    //apptesdThread.start();
    appsvbddThread.start();

    //apptest.test();
    appsvbdd.start();
}

/**
 * Starts Controller and CLI
 * @brief odm::Controller::launch
 */
void odm::Controller::launch(){
    this->moveToThread(this);
    this->start();

    cli.startReading();
}

void odm::Controller::processCommand(QString cmd){
    QStringList l = cmd.split(" ", QString::SkipEmptyParts, Qt::CaseInsensitive);

    QMetaObject MetaObject = this->staticMetaObject;
    QMetaEnum MetaEnum = MetaObject.enumerator(MetaObject.indexOfEnumerator("Keywords"));

    switch (MetaEnum.keysToValue(l[0].toUpper().toLatin1())){
        case SERVER:
            qDebug() << "SERVER CONFIG";
            switch (MetaEnum.keysToValue(l[1].toUpper().toLatin1())){
                case START:
                    rThread.start();
                    dThread.start();
                break;
                case STOP:
                break;
                case RESTART:
                break;
                default:
                    qDebug() << l[0] << " is not a valid action. Type \"help\" for more information";
            }
        break;

        case DBSAVE:
        break;

        case JSONSTREAM:
        break;

        case HELP:
        break;

        case EXIT:
        case QUIT:
            qDebug() << "Shutting down...";
        break;

        default:
            qDebug() << l[0] << " is not a valid component. Type \"help\" for more information";
    }

}
