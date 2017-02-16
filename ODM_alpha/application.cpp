#include "application.h"

QVector<QVariantMap>* Application::state_ref = NULL;
QReadWriteLock* Application::state_lock = NULL;

Application::Application(){

}

void Application::getState(QVector<QVariantMap> *rt_table, QReadWriteLock *l){
    if(state_ref == NULL){
        qDebug() << Q_FUNC_INFO;
        Application::state_ref = rt_table;
        Application::state_lock = l;
    }
}

bool Application::updateState(){
    QReadLocker read_lock(state_lock);
    if(state_ref != NULL){
        state = *state_ref;
        qDebug() << state_ref << state_lock;
        return true;
    }
    return false;
}
