#ifndef dispenser_H
#define dispenser_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>
#include <QtXml>
#include <QMap>
#include <QVariant>
#include <QString>


namespace odm {
    class Dispenser : public QObject
    {
        Q_OBJECT
    public:
        explicit Dispenser(QObject *parent = 0);
        QVector<QVariantMap> state;
        QMap<QString, QChar> params;
    private:
        void initStateParams();
        //dataset structure/class for real time data

    signals:
        void requestData();
    public slots:
        void processData(QVector<QJsonObject>);
        void shareState();
    };
}

#endif // dispenser_H
