#ifndef APP_MAP_H
#define APP_MAP_H

#include <QTcpSocket>
#include "application.h"

class app_map : public odm::Application
{
    public:
        app_map();

        void start();

    private:
        const QString HOSTNAME="localhost";
        const qint16 PORT=7070;
        const int TIME_LAPS = 1;

        QTcpSocket *socket;

        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

        void loop();

        bool init();
};
#endif
