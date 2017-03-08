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
    QObject::connect(this, SIGNAL(stopServer()), &receiver, SLOT(stopServer()));
    QObject::connect(&receiver, SIGNAL(readyToStop()), &rThread, SLOT(quit()));

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
    QTextStream out(stdout);

    out << " > " << cmd << endl;
    QStringList l = cmd.split(" ", QString::SkipEmptyParts, Qt::CaseInsensitive);

    QMetaObject MetaObject = this->staticMetaObject;
    QMetaEnum MetaEnum = MetaObject.enumerator(MetaObject.indexOfEnumerator("Keywords"));

    if(l.size() >= 1){
        switch (MetaEnum.keysToValue(l[0].toUpper().toLatin1())){
            case SERVER:
                if(l.size() >= 2){
                    switch (MetaEnum.keysToValue(l[1].toUpper().toLatin1())){
                        case START:
                            if(!rThread.isRunning() && !dThread.isRunning()){
                                rThread.start();
                                dThread.start();
                            }
                            if(rThread.isRunning() ^ dThread.isRunning()){
                                emit stopServer();
                                dThread.terminate();
                                while(rThread.isRunning() ^ dThread.isRunning());
                                rThread.start();
                                dThread.start();
                            }
                        break;

                        case STOP:
                            if(dThread.isRunning() ){
                                emit stopServer();
                                this->dThread.quit();
                            }
                            else{
                                qDebug() << "Server is already down.";
                            }
                        break;

                        case RESTART:
                            if(rThread.isRunning() ^ dThread.isRunning()){
                                qDebug() << "Waiting for server to shutdown...";
                                emit stopServer();
                                dThread.quit();
                                while(rThread.isRunning() ^ dThread.isRunning());
                                rThread.start();
                                dThread.start();
                            }
                        break;

                        default:
                            qDebug() << l[1] << " is not a valid action. Type \"help\" for more information";
                    }
                }
                else{
                    qDebug() << "Please specify an action (START, STOP, RESTART); e.g. SERVER START";
                }
            break;

            case DBSAVE:
                if(l.size() >= 2){
                    switch (MetaEnum.keysToValue(l[1].toUpper().toLatin1())){
                        case START:
                            if(!appsvbddThread.isRunning()){
                                appsvbddThread.start();
                            }
                            else{
                                qDebug() << "DBSAVE is already running.";
                            }
                        break;
                        case STOP:
                            if(appsvbddThread.isRunning() ){
                                this->appsvbddThread.quit();
                            }
                            else{
                                qDebug() << "Server is already down.";
                            }
                        break;
                    }
                }
                else{
                    qDebug() << "Please specify an action (START, STOP, RESTART, SET <attribute> <value>); e.g. DBSAVE START";
                }
            break;

            case JSONSTREAM:
            break;

            case HELP:
                qDebug() << "Command syntax : <component> <action>\nIf <action> is SET, append <property> <value>\n\tComponents : SERVER, DBSAVE, JSONSTREAM\n\tActions : START, STOP, RESTART, SET";
            break;

            case EXIT:
            case QUIT:
                qDebug() << "Shutting down...";
                this->appsvbddThread.quit();
                //this->jsonstreamThread.quit()
                this->rThread.quit();
                this->dThread.quit();
                this->quit();
            break;

            default:
                qDebug() << l[0] << " is not a valid component. Type \"help\" for more information";
        }
    }

}
