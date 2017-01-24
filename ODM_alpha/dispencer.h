#ifndef DISPENCER_H
#define DISPENCER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

#include "data_id.h"

namespace odm {
    class Dispencer : public QObject
    {
        Q_OBJECT
    public:
        explicit Dispencer(QObject *parent = 0);
    private:
        //dataset structure/class for real time data

    signals:
        void requestData();
    public slots:
        void processData(QVector<data_id>);
    };
}

#endif // DISPENCER_H
