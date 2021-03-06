/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include <QCoreApplication>
#include "controller.h"
using namespace odm;
int main(int argc, char *argv[])
{
    qDebug() << "Initialisation...";
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Open Drone Monitoring");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();


    QCommandLineOption startallOption(QStringList() << "S" << "startall",
            QCoreApplication::translate("main", "Start all services."));
    parser.addOption(startallOption);

    QCommandLineOption servicesOption(QStringList() << "s" << "service-name",
            QCoreApplication::translate("main", "Starts <service>."),
            QCoreApplication::translate("main", "service"));
    parser.addOption(servicesOption);

    parser.process(a);

    bool serviceAll = parser.isSet(startallOption);
    QStringList serviceList = parser.values(servicesOption);

    qDebug() << "service all = " << serviceAll << "\nServices :";
    foreach(QString s, serviceList)
        qDebug() << "\t" << s;

    Controller controller;

    QObject::connect(&controller, SIGNAL(quit_all()), &a, SLOT(quit()));
    if(serviceAll){
        controller.launchAll();
    }
    else{
        controller.launch();
    }

    return a.exec();
}
