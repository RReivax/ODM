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
