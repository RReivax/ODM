#ifndef APP_bdSave_H
#define APP_bdSave_H

#include "application.h"
#include <QtSql>
#include <QString>

/**
 * @class app_bdSave
 * @brief Use to save real time data
 * 		into a specified data base
 *
 * Every TIME_LAPS seconds, the function will copy all the actual infos of UAV (the state vector)
 * on a DB using MySQL. The DB is configured with the information below
 */

class app_bdSave : public odm::Application
{
    public:
        app_bdSave();

        /** @fn void app_bdSave::start()
             *  @brief will try to connect to the DB with the given info, if succeed, will call init();.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void start();

    private:
        const QString MARKER_DEBUG = "****** APP DB debug : ";
        QString DB_HOSTNAME="localhost";
        QString DB_USERNAME="root";
        QString DB_PASSWORD="root";
        QString DB_NAME="odm_db";
        QString TABLE_LAT = "latitude";
        QString TABLE_ALT = "altitude";
        QString TABLE_DTE = "date";
        QString TABLE_ID = "id";
        QString TABLE_LONG = "longitude";
        int TIME_LAPS = 3;


        bool DEBUG_ENABLE = true; // True to enable verbose debug mode
        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

        /** @fn void app_bdSave::loop()
             *  @brief Each TIME_LAPS seconds, save in the DB the state table.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void loop();

        /** @fn void app_bdSave::loop()
             *  @brief heck if the table exist, if not, try to create it.
             *  @return true if the table is ready false else.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool init();
};

#endif // APP_bdSave_H
