/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "cli.h"

odm::CLI::CLI(QWidget *parent) : QWidget(parent){
    resize(600,50);
    setWindowTitle("ODM - Input command line");

    layout = new QBoxLayout(QBoxLayout::LeftToRight);

    inpLine = new QLineEdit();
    inpLine->resize(500, 40);
    layout->addWidget(inpLine);

    btn = new QPushButton("Enter");
    layout->addWidget(btn);

    this->setLayout(layout);
}

void odm::CLI::startReading(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    QObject::connect(inpLine, SIGNAL(returnPressed()), this, SLOT(readCommand()));
    QObject::connect(btn, SIGNAL(clicked(bool)), this, SLOT(readCommand()));
    show();
}

void odm::CLI::readCommand(){
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    if(!inpLine->text().isEmpty())emit passCommand(inpLine->text());
    inpLine->setText("");
}
