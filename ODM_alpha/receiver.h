#ifndef Receiver_H
#define Receiver_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

#include <QMap>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QFile>
#include <QJsonDocument>

//#include <QHostAddress>

#include "data_id.h"

namespace odm {
    typedef struct addr_time{
            QHostAddress host;
            int timestamp;
    }ip_time;

    class Receiver : public QObject
    {
        Q_OBJECT

        public:
            explicit Receiver(QObject *parent = 0);
        signals:
            void transferData(QVector<data_id>);
            void endOfReception();
            void noDataToTransfer();
            void gotData();
        public slots:
            void startServer();
            void prepareData();
            void initTransfer(QHostAddress host);
            void stackData(data_id toStack);
            void receiveData();

        private:
            QTcpServer *tcpServer;
            QString statusLabel;
            QVector<QStack<data_id>> stacks;
            QMap<int,addr_time> idAssoc;
    };
}

#endif // Receiver_H
