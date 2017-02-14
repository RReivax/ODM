#include "app_test.h"

app_test::app_test()
{

}

void app_test::test(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while(1){
        this->rt_lock->lockForRead();
        rt = *rt_ref;
        this->rt_lock->unlock();

        qDebug() << rt;
    }
}
