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
