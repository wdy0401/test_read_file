#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include<QFile>
#include <QProcess>
#include <QTextCodec>

using namespace std;

MainWindow *pw;
void readfile(const string &);
void readcmd(const string &);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    pw=&w;
    w.show();

//    readfile("d:/2.txt");
    readcmd("");
    return a.exec();
}
void readfile(const string & filename)
{
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    while (!file.atEnd())
    {
        QString ql=file.readLine();
        cout << ql.toStdString();
    }
}
void readcmd(const string & cmdname)
{
//    QString program = "C:/Windows/System32/cmd.exe";
//    QStringList arguments;
//    arguments << "/c" << "dir" << "C:\\";
//    QProcess *cmdProcess = new QProcess;
//    cmdProcess->start(program, arguments);
    QProcess *cmdProcess = new QProcess;
    cmdProcess->start("E:/cygwin64/bin/ls c:/");
    QObject::connect(cmdProcess, &QProcess::readyRead, [=] ()
        {
//            QTextCodec *codec = QTextCodec::codecForName("GBK");
//            QString dir = codec->toUnicode(cmdProcess->readAll());
//            qDebug() << dir;


            while (!cmdProcess->atEnd())
            {
                QTextCodec *codec = QTextCodec::codecForName("GBK");
                qDebug() <<  codec->toUnicode(cmdProcess->readLine());
                qDebug() << "AA" << endl;
            }
        }
    );
}

