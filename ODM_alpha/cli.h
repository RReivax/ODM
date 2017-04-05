/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
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
        void closeEvent(QCloseEvent *event);
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
