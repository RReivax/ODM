#ifndef APP_TEST_H
#define APP_TEST_H

#include "application.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>


class app_test : public Application
{
    public:
        app_test();
        void test();
};

#endif // APP_TEST_H
