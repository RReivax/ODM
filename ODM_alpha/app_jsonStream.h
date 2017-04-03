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
        /**
         * @brief start
         */
        void launch();
    private:
        const QString HOSTNAME="localhost";
        const qint16 PORT=7070;
        const int TIME_LAPS = 1;

        QTcpSocket *socket;

        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

    protected:
        bool defAppType();
        bool loopFct();
        bool initApp();
        bool closeApp();
};
#endif
