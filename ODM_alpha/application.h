#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QReadWriteLock>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

class Application : public QObject
{
    Q_OBJECT
public:
    Application();
signals:
    void requestState();
public slots:
    static void getState(QVector<QVariantMap>*, QReadWriteLock*);
    bool updateState();
protected:
    static QVector<QVariantMap> *state_ref;
    static QReadWriteLock *state_lock;
    QVector<QVariantMap> state;
};

#endif // APPLICATION_H
