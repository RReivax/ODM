#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QReadWriteLock>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QStack>
#include <QtXml>

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
        bool LOOP;/**< Boolean indicating if the application is build around a looping function or not*/
    public slots:
        /**
         * @fn static void Application::getState(QVector<QVariantMap>* rt_table, QReadWriteLock* lo)
         * @brief Sets the static pointers state_ref and state_lock of Application.
         * @param rt_table a pointer to QVector<QVariantMap> dispenser.state
         * @param lo a pointer to QReadWriteLock dispenser.lock
         *
         * This slot is called when the dispenser is started.
         * The two pointers are used in Application::updateState().
         */
        static void getState(QVector<QVariantMap>* rt_table, QReadWriteLock* lo);
        /**
         * @fn void Application::askForClosing()
         * @brief Asks the application to end.
         *
         * Only works for application not based on a looping function (where LOOP is false).
         */
        void askForClosing();
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
        /**
         * @fn bool Application::appLoop()
         * @brief Handles the loop of application.
         * @return a boolean.
         *
         * Stops the loop if an interuption is requested from the controller. Returns true if the loop ended properly (if closeApp() was successful).
         */
        bool appLoop();
        /**
         * @fn void Application::launch()
         * @brief Starts the application.
         *
         * Calls Application::initApp() and Application::appLoop() if LOOP is true.
         */
        void launch();
        /**
         * @fn virtual bool Application::defAppType()
         * @brief Sets LOOP to true or false depending on the type of application.
         * @return a boolean.
         *
         * Returns true if the application is based on a looping function, false otherwise.
         */
        virtual bool defAppType() = 0;
        /**
         * @fn virtual bool Application::loopFct()
         * @brief The looping function of the application called in Application::appLoop().
         * @return a boolean.
         *
         * This function will be called in every loop round. Returns false if the application has to end, true otherwise.
         */
        virtual bool loopFct() = 0;
        /**
         * @fn virtual bool Application::initApp()
         * @brief Initializes all the variables of the application.
         * @return a boolean.
         *
         * Returns false if the initialization failed, true otherwise.
         */
        virtual bool initApp() = 0;
        /**
         * @fn virtual bool Application::closeApp()
         * @brief Frees/closes critical variables/entities of the application.
         * @return a boolean.
         *
         * Returns false if some entity closing failed, true otherwise.
         */
        virtual bool closeApp() = 0;
    };
}

#endif // APPLICATION_H
