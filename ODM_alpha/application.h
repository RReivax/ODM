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
    void requestRt();
public slots:
    void getRt(int*, QReadWriteLock*);
protected:
    int *rt_ref;
    QReadWriteLock *rt_lock;
    int rt;
};

#endif // APPLICATION_H
