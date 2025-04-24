#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QThread>

#include "TCPSocket.h"


//Sub Fuctions
void ShowHelp();


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    bool isLogFile = false;
    bool isArguments = false;
    QString logFile = "log.txt";
    QStringList arguments;


    if(argc > 1)
    {
        //Move Arguments to QStrings in a QStringList
        for(quint8 i = 1; i < argc; i++)
            arguments << argv[i];

        //Process the arguments
        for(quint8 i = 0; i < arguments.count(); i++)
        {
            if(arguments[i] == "-h")
            {
                //Show Help and Quit
                ShowHelp();
                return 1;
            }
            else if(arguments[i] == "-l")
            {
                isLogFile = true;
            }
            else if(arguments[i] == "-n")
            {
                if(arguments.count() > i+1)
                    logFile = arguments[i+1];
                else
                {
                    qDebug() << "No name for log file for -n option. Quitting the program";
                    return 1;
                }

                //For the File Name
                i++;
            }
        }
    }


    TCPSocket socketConnection(isLogFile, logFile);

    socketConnection.Connect ();

    return a.exec();
}


void ShowHelp()
{
    qDebug() << "LGTCPTester or LGTCPTester -options";
    qDebug() << "Options";
    qDebug() << "-h: Shows Help Info, which is this. Also doesn't run program and quits.";
    qDebug() << "-l: Log Output Signals to a Log File. Default Log File is log.txt, unless the -n option is used.";
    qDebug() << "-n follwed with file name: Names the Log file. Example: -n gameX.txt";
}
