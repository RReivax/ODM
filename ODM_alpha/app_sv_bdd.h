#ifndef APP_SV_BDD_H
#define APP_SV_BDD_H

#include "application.h"
#include <QtSql>
#include <QString>

class app_sv_bdd : public Application
{
    public:
        app_sv_bdd();
        void start();

    private:
        const QString DB_HOSTNAME="localhost";
        const QString DB_USERNAME="root";
        const QString DB_PASSWORD="";
        const QString DB_NAME="odm_db";
        const int TIME_LAPS = 3;

        bool is_running; //Boolean controlling the main loop, of the 'void loop()' (below)
        void loop(); //Each TIME_LAPS seconds, save in the BDD the state table.
        bool init(); //Check if the table exist, if not, try to create it.
};

#endif // APP_SV_BDD_H
