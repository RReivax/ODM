#ifndef APP_TEST_H
#define APP_TEST_H

#include "application.h"
<<<<<<< HEAD
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
=======

class app_test : public odm::Application
{
    public:
        app_test();
        void test();
>>>>>>> 3821156035fff33c0cfb15a1feb159047f8c4b38
};

#endif // APP_TEST_H
