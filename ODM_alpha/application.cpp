/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
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
