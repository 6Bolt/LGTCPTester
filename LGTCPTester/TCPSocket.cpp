#include "TCPSocket.h"

TCPSocket::TCPSocket(bool lgF, QString logFN, QObject *parent)
    : QObject{parent}
{

    isLogFile = lgF;
    logName = logFN;
    isConnected = false;

    //Create the New TCP Socket
    p_hookSocket = new QTcpSocket(this);

    //Connect Signal of when there is read data, to the slot that will read it
    connect(p_hookSocket,SIGNAL(readyRead()), this, SLOT(TCPReadData()));
    connect(p_hookSocket,SIGNAL(connected()), this, SLOT(SocketConnected()));
    connect(p_hookSocket,SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));

    //If Using Log File, then Open it and Set-Up QTextStream
    if(isLogFile)
    {
        p_logFile = new QFile(logName);

        if(!p_logFile->open (QIODevice::WriteOnly  | QIODevice::Text))
        {
            qDebug() << "Couldn't open write file. File: " << logName;
            isLogFile = false;
        }

        qDebug() << "Made New Log File";

        out.setDevice (p_logFile);
    }

    p_waitingForConnection = new QTimer(this);
    p_waitingForConnection->setInterval (1050);
    p_waitingForConnection->setSingleShot (true);
    connect(p_waitingForConnection, SIGNAL(timeout()), this, SLOT(TCPConnectionTimeOut()));

}


TCPSocket::~TCPSocket()
{
    if(isConnected)
        p_hookSocket->close();

    delete p_hookSocket;

    if(isLogFile)
    {
        out.flush ();
        p_logFile->close();
    }
    delete p_logFile;
}


//public:

void TCPSocket::Connect()
{
    qDebug() << "Waiting for a TCP Connection";

    //Set the Address for the TCP Socket
    p_hookSocket->connectToHost ("localhost", 8000);

    //Wait for Connection
    p_hookSocket->waitForConnected (10000);

    p_waitingForConnection->start ();

}


void TCPSocket::Disconnect()
{
    //qDebug() << "Closed TCP Connection - Disconnect";

    //Close TCP Socket
    p_hookSocket->close ();
}

bool TCPSocket::IsConnected()
{
    return isConnected;
}



//public slots:

void TCPSocket::TCPReadData()
{
    //Read the TCP Socket Data
    readData = p_hookSocket->readAll ();

    QString message = QString::fromStdString (readData.toStdString ());

    //Remove the \r at the end
    if(message.endsWith('\r') || message.endsWith('\n'))
        message.chop(1);

    //If Multiple Data Lines, they will be seperated into lines, using \r or \n
    //If it had 2 data lines together, then \r would be at end which is chopped off, and middle
    //QRegularExpression endLines("[\r\n]");
    QStringList tcpSocketReadData = message.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);

    for(quint8 x = 0; x < tcpSocketReadData.count(); x++)
    {
        qDebug() << tcpSocketReadData[x];

        if(isLogFile)
        {
            out << tcpSocketReadData[x] << "\n";
        }
    }

    if(isLogFile)
        out.flush ();

}

void TCPSocket::SocketConnected()
{
    p_waitingForConnection->stop ();

    isConnected = true;

    qDebug() << "TCP Socket is Connected";

    if(isLogFile)
    {
        out << "TCP Socket is Connected\n";
    }
}

void TCPSocket::SocketDisconnected()
{
    isConnected = false;

    qDebug() << "TCP Socket has been Disconnected";

    if(isLogFile)
    {
        out << "TCP Socket has been Disconnected\n";
    }

    Connect();

}


void TCPSocket::TCPConnectionTimeOut()
{
    if(!isConnected)
    {
        //Set the Address for the TCP Socket
        p_hookSocket->connectToHost ("localhost", 8000);

        //Wait for Connection
        p_hookSocket->waitForConnected (10000);

        p_waitingForConnection->start ();
    }
}
