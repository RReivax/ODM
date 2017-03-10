#ifndef app_dbSave_H
#define app_dbSave_H

#include "application.h"
#include <QtSql>
#include <QString>

/**
 * @class app_dbSave
 * @brief Use to save real time data
 * 		into a specified data base
 *
 * Every TIME_LAPS seconds, the function will copy all the actual infos of UAV (the state vector)
 * on a DB using MySQL. The DB is configured with the information below
 */

class app_dbSave : public odm::Application
{
    public:
        app_dbSave();

        bool get_conf();

        /** @fn void app_dbSave::start()
             *  @brief will try to connect to the DB with the given info, if succeed, will call init();.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void start();

        /** @fn void app_dbSave::stop();
         * @brief set the is_running boolean to false
         * @return nothing.
         *
         * Set the 'is_running' boolean to false
         */
        void stop();

    private:
        /**
         * @brief MARKER_DEBUG
         *
         * This is the default string which get inhead of every
         * debbuging message of the application
         */
        const QString MARKER_DEBUG = "****** APP DB debug : ";

        /**
         * @brief DATA BASE variables
         *
         * Those are the declaration of the varaible used
         * to connect the MySQL DB
         * to modify the tables inside it
         *
         * They are filled with the default value as below
         * the value that will be used are stored in config_db.xml
         *
         */
        QString DB_HOSTNAME="localhost";
        QString DB_USERNAME="root";
        QString DB_PASSWORD="";
        QString DB_NAME="odm_db";
        QString TABLE_LAT = "latitude";
        QString TABLE_ALT = "altitude";
        QString TABLE_DTE = "date";
        QString TABLE_ID = "id";
        QString TABLE_LONG = "longitude";
        int TIME_LAPS = 3;


        bool DEBUG_ENABLE = false; // True to enable verbose debug mode
        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

        /** @fn void app_dbSave::loop()
             *  @brief Each TIME_LAPS seconds, save in the DB the state table.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        void loop();

        /** @fn void app_dbSave::loop()
             *  @brief heck if the table exist, if not, try to create it.
             *  @return true if the table is ready false else.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool init();
};

#endif // app_dbSave_H
