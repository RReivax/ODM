/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
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
 * Every TIME_LAPS seconds, the function will copy all the actual infos of UAVs (the state vector)
 * on a DB using MySQL. The DB is configured with the information below
 */

class app_dbSave : public odm::Application
{
    Q_OBJECT

    public:
        app_dbSave();

        bool get_conf();

        /** If this is a loop application, which means has a appLoop() function
        */
        bool LOOP = true;

    public slots:

        /** @fn void app_dbSave::initApp()
             *  @brief will try to connect to the DB with the given info, if succeed, will call init();.
             *  @return true if everything is fine.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool initApp();

        /** @fn bool app_dbSave::stop();
         * @brief set the is_running boolean to false and try to close the DB
         * @return the return of db.close().
         *
         * Set the 'is_running' boolean to false
         */
        bool closeApp();

        bool defAppType();


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
        QString TABLE_LAT = "Latitude";
        QString TABLE_ALT = "Altitude";
        QString TABLE_DTE = "date";
        QString TABLE_ID = "name";
        QString TABLE_LONG = "Longitude";
        int TIME_LAPS = 3;
        QSqlDatabase db;

        QMap<QString, QString> lastUpadate;

        bool DEBUG_ENABLE = true; // True to enable verbose debug mode
        bool is_running; /**< Boolean controlling the main loop, of the 'void loop()' (below)*/

        /** @fn void app_dbSave::loopFct()
             *  @brief Each TIME_LAPS seconds, save in the DB the state table.
             *  @return nothing.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool loopFct();

        /** @fn void app_dbSave::init()
             *  @brief heck if the table exist, if not, try to create it.
             *  @return true if the table is ready false else.
             *
             *  Uses QtSql libriaries
             *  Set 'DEBUG_ENABLE' to true tu put the verbose mode on.
             */
        bool init();
};

#endif // app_dbSave_H
