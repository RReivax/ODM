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

#include <QReadWriteLock>


namespace odm{
    /**
     * @class Dispenser
     * @brief The Dispenser class.
     */
    class Dispenser : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @fn Dispenser()
         * @brief Dispenser constructor.
         * @param parent a QObject*
         */
        explicit Dispenser(QObject *parent = 0);

        QVector<QVariantMap> state;/**< The real time drone data set*/
        QMap<QString, QChar> params;/**< The list of a drone data set parameters*/
        QReadWriteLock lock;/**< A lock to secure reading/writing in state*/

    private:
        /**
         * @fn void Dispenser::initStateParams()
         * @brief Settles params by reading in config.xml
         */
        void initStateParams();
    signals:
        /**
         * @fn Dispenser::requestData()
         * @brief Calls the slot Receiver::prepareData().
         *
         * Indicates that dispenser has finished processing the data.
         */
        void requestData();
        /**
         * @fn Dispenser::dispenseState(QVector<QVariantMap>* st, QReadWriteLock* lo)
         * @brief Calls the slot Application::getState(QVector<QVariantMap>* st, QReadWriteLock* lo).
         *
         * Gives pointers to state and lock to the class Application.
         */
        void dispenseState(QVector<QVariantMap>* st, QReadWriteLock* lo);
    public slots:
        /**
         * @fn Dispenser::processData(QVector<QJsonObject>)
         * @brief Updates state with the most recent data set of each drone.
         *
         * Gets a QJsonObject for each drone. Stores the one with the most recent date in state[drone].
         */
        void processData(QVector<QJsonObject>);
        /**
         * @fn Dispenser::shareState()
         * @brief Emits Dispenser::dispenseState(QVector<QVariantMap>* st, QReadWriteLock* lo).
         */
        void shareState();
        void removeState(QString name);
    };
}

#endif // dispenser_H
