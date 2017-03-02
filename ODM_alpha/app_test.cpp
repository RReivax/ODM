#include "app_test.h"

app_test::app_test()
{

}

void app_test::test(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while(1){
<<<<<<< HEAD
        this->rt_lock->lockForRead();
        rt = *rt_ref;
        this->rt_lock->unlock();

        qDebug() << rt;
=======
        while(!updateState()){
            qDebug() << "Not_ready";
        }
        qDebug() << state;
        QThread::sleep(1);
>>>>>>> 3821156035fff33c0cfb15a1feb159047f8c4b38
    }
}
