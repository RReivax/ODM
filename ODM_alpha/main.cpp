#include <QCoreApplication>
#include "controller.h"
using namespace odm;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller controller;

    controller.launch();
    return a.exec();
}
