#include "app_test.h"

app_test::app_test()
{

		
}


void app_test::test(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    while(1){
        while(!updateState()){
            qDebug() << "Not_ready";
        }
        qDebug() << state;
        QThread::sleep(1);
    }
}
