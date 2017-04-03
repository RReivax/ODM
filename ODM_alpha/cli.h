#ifndef CLI_H
#define CLI_H

#include <QtCore>
#include <QtWidgets>

namespace odm{
    class CLI : public QWidget
    {
        Q_OBJECT
    public:
        explicit CLI(QWidget *parent = 0);

    signals:
        void passCommand(QString cmd);
    public slots:
        void startReading();
        void readCommand();
    private:
        QBoxLayout *layout;
        QLineEdit *inpLine;
        QPushButton *btn;
    };
}

#endif // CLI_H
