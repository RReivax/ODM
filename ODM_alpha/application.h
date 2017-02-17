#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QReadWriteLock>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>

namespace odm{
    /**
     * @class Application
     * @brief The abstract Application class.
     *
     * All features of O.D.M. inherit from this class.
     */
    class Application : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @fn Application()
         * @brief Application constructor.
         */
        Application();
    public slots:
        /**
         * @fn static void Application::getState(QVector<QVariantMap>* rt_table, QReadWriteLock* lo)
         * @brief Sets the static pointers state_ref and state_lock of Application.
         * @param rt_table a pointer to QVector<QVariantMap> dispenser.state
         * @param lo a pointer to QReadWriteLock dispenser.lock
         *
         * This slot is called when the dispenser is started.
         * The two pointers are used in updateState().
         */
        static void getState(QVector<QVariantMap>* rt_table, QReadWriteLock* lo);
    protected:
        static QVector<QVariantMap> *state_ref;/**< Pointer to QVector<QVariantMap> dispenser.state*/
        static QReadWriteLock *state_lock;/**< Pointer to QReadWriteLock dispenser.lock*/
        QVector<QVariantMap> state;/**< Local copy of the real time drone data set. 1 QVariantMap <=> 1 drone*/
        /**
         * @fn bool updateState()
         * @brief  Updates state with the most recent drone data.
         * @return a boolean.
         *
         * Updates the local copy of the most recent drone data set. Returns true if the update was successful, false otherwise.
         */
        bool updateState();
    };
}

#endif // APPLICATION_H
