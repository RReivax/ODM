#include "application.h"

Application::Application(){
    this->rt_ref = NULL;
    this->rt_lock = NULL;
    requestRt();
}

void Application::getRt(int *rt_table, QReadWriteLock *l){
    if(!rt_ref){
        this->rt_ref = rt_table;
        this->rt_lock = l;
    }
}
