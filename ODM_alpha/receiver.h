#ifndef Receiver_H
#define Receiver_H

#include <QtCore>
#include <QtNetwork>
#include "qjsonstack.h"


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
<<<<<<< HEAD
            void stateToDelete(QString);
=======
            void readyToStop();
>>>>>>> 59d80cf76a0e345cfc7649f0be770c3e0628b53a
        public slots:
            void startServer();
            void stopServer();

            void newClient();
            void disconnected();
            void readSocket();
            void InitClient();
            void RemoveStack();
            void prepareData();
            void stackData(QByteArray toStack);
        private:
            QTcpServer *tcpServer;
            QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
            QString statusLabel;
            QStringList toDelete;
            QMap<QString,QJsonStack> flightData;
            int dc;

    };
}

#endif // Receiver_H
