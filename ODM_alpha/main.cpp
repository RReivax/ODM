#include <QCoreApplication>
#include "controller.h"
using namespace odm;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller test;

    test.launch();
    return a.exec();
}
