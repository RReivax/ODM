#ifndef APP_MAP_H
#define APP_MAP_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "application.h"

class app_jsonStream : public odm::Application
{
    Q_OBJECT

    public:
        app_jsonStream();



   public slots:
        bool defAppType();
        bool loopFct();
        bool initApp();
        bool closeApp();


    private:
        const QString HOSTNAME="localhost";
        const qint16 PORT=7070;
        const int TIME_LAPS = 1;

        QTcpSocket *socket;


};
#endif
