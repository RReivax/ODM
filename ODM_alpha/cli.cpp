#include "cli.h"

odm::CLI::CLI(QObject *parent) : QObject(parent){

}

void odm::CLI::startReading(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QSocketNotifier *pNot = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
    connect(pNot, SIGNAL(activated(int)), this, SLOT(readCommand()));
    pNot->setEnabled(true);
}

void odm::CLI::readCommand(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    QTextStream stream(stdin);
    QString line;
    while (stream.readLineInto(&line)) {
        if(line == "shutdown")
            qDebug() << "Shuting down...";
    }
}
