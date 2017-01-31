#ifndef Receiver_H
#define Receiver_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QHostAddress>

#include "data_id.h"

namespace odm {
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
            void prepareData();
            void recieveData();
        private:
            QTcpServer *tcpServer;
            QString statusLabel;
            QVector<QStack<data_id>> stacks;
    };
}

#endif // Receiver_H
