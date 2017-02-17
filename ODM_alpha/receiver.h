#ifndef Receiver_H
#define Receiver_H

#include <QtCore>
#include <QtNetwork>


namespace odm {
    class Receiver : public QObject
    {
        Q_OBJECT

        public:
            explicit Receiver(QObject *parent = 0);
        signals:
            void transferData(QVector<QJsonObject>);
            void endOfReception();
            void noDataToTransfer();

            void dataReceived(QByteArray);
        public slots:
            void startServer();

            void newClient();
            void disconnected();
            void readSocket();
            void InitClient();

            void prepareData();
            void stackData(QByteArray toStack);
        private:
            QTcpServer *tcpServer;
            QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
            QString statusLabel;

            QMap<QString,QStack<QJsonObject>> flightData;

    };
}

#endif // Receiver_H
