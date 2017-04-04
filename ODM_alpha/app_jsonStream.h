#ifndef APP_MAP_H
#define APP_MAP_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "application.h"

/**
 * @class app_jsonStream
 * @brief Used to send data via a TCP socket to a specified server
 *
 * Every TIME_LAPS seconds, the function will send to the server all the actual infos of UAVs (the state vector)
 */
class app_jsonStream : public odm::Application
{
    Q_OBJECT

    public:
        app_jsonStream();



   public slots:

        /** @fn void app_jsonStream::initApp()
             *  @brief will try to connect to the TCP server with the given ip and port.
             *  @return true if we could connect to the server.
             *          false if we could not connect.
             */
        bool initApp();


        /** @fn void app_jsonStream::defAppType()
         * @brief specifies that the application is loop-based.
         * @return true
         */
        bool defAppType();

        /**
         * @brief loopFct sends the UAVs infos to the server as a json stream.
         * @return true
         */
        bool loopFct();

        /**
         * @brief closeApp disconnects from the host.
         * @return true
         */
        bool closeApp();


    private:

        /**
         * @brief Connection variables
         * The hostname and the port of the server to which the socket will connect
         */
        const QString HOSTNAME="localhost";
        const qint16 PORT=7070;


        const int TIME_LAPS = 1;

        QTcpSocket *socket;


};
#endif
