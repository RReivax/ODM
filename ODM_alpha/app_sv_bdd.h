#ifndef APP_SV_BDD_H
#define APP_SV_BDD_H

#include "application.h"
#include <QtSql>
#include <QString>

/**
 * @class app_sv_bdd
 * @brief Use to save real time data
 * 		into a specified data base
 *
 * Every TIME_LAPS seconds, the function will copy all the actual infos of UAV (the state vector)
 * on a DB using MySQL. The DB is configured with the information below
 */

class app_sv_bdd : public odm::Application
{
    public:
        app_sv_bdd();

        /** @fn void app_sv_bdd::start()
             *  @brief will try to connect to the DB with the given info, if succeed, will call init();.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void start();

    private:
        const QString DB_HOSTNAME="localhost";
        const QString DB_USERNAME="root";
        const QString DB_PASSWORD="root";
        const QString DB_NAME="odm_db";
        const int TIME_LAPS = 3;

        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

        /** @fn void app_sv_bdd::loop()
             *  @brief Each TIME_LAPS seconds, save in the BDD the state table.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void loop();

        /** @fn void app_sv_bdd::loop()
             *  @brief heck if the table exist, if not, try to create it.
             *  @return true if the table is ready false else.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool init();
};

#endif // APP_SV_BDD_H
