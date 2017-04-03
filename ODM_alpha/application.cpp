#include "application.h"

QVector<QVariantMap>* odm::Application::state_ref = NULL;
QReadWriteLock* odm::Application::state_lock = NULL;

odm::Application::Application(){

}

void odm::Application::getState(QVector<QVariantMap> *rt_table, QReadWriteLock *lo){
    if(state_ref == NULL){
        Application::state_ref = rt_table;
        Application::state_lock = lo;
    }
}

bool odm::Application::updateState(){
    //locking the QVector<QVariantMap> dispenser.state for reading
    QReadLocker read_lock(state_lock);
    //if the pointer to state is set
    if(state_ref != NULL){
        //copying dispenser.state to this.state
        state = *state_ref;
        return true;
    }
    return false;
}

void odm::Application::launch(){
    LOOP = false;
    LOOP = defAppType();
    if(LOOP && initApp()){
       bool closed = appLoop();
         if(closed){
            QThread::currentThread()->exit();
         }else{
            qDebug() << "Error closing the application " << this->metaObject()->className() << ". Forcing closing.";
            QThread::currentThread()->terminate();
         }
    }
}

bool odm::Application::appLoop(){
    bool interupt = true;
    while((!QThread::currentThread()->isInterruptionRequested())&&interupt){
        interupt = loopFct();
    }
    return closeApp();
}

void odm::Application::askForClosing(){
    bool closed = closeApp();
    if(closed){
        QThread::currentThread()->exit();
    }else{
        qDebug() << "Error closing the application " << this->metaObject()->className() << ". Forcing closing.";
        QThread::currentThread()->terminate();
    }
}
