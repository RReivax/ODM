#ifndef CLI_H
#define CLI_H

#include <QObject>
#include <QtCore>

namespace odm{
    class CLI : public QObject
    {
        Q_OBJECT
    public:
        explicit CLI(QObject *parent = 0);

    signals:

    public slots:
        void startReading();
        void readCommand();
    };
}

#endif // CLI_H
