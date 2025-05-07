#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QDebug>
#include <QRegularExpression>
#include <QTimer>
#include <QElapsedTimer>


class TCPSocket : public QObject
{
    Q_OBJECT

public:

    explicit TCPSocket(bool lgF, QString logFN, QObject *parent = nullptr);
    ~TCPSocket();


    //Connects to TCP Socket and Waits for Connection
    void Connect();
    //Disconnects the TCP Socket
    void Disconnect();
    //Is TCP Socket Connected
    bool IsConnected();


public slots:

    //When Signal readReady, this Slot Reads the TCP Socket and Forwards it to
    //the Hooker Engine
    void TCPReadData();

    //When TCP Socket Connects, it calls this Slot, which emit another Signal to
    //Hooker Engine to Let it Know it Connected
    void SocketConnected();
    //When TCP Socket Disconnects, it calls this Slot, which emit another Signal to
    //Hooker Engine to Let it Know it Disconnected
    void SocketDisconnected();

    void TCPConnectionTimeOut();


private:


    ///////////////////////////////////////////////////////////////////////////

    //TCP Socket Connection
    QTcpSocket *p_hookSocket;
    bool isConnected;

    //Timer
    QTimer *p_waitingForConnection;

    //Elapse Timer
    QElapsedTimer *p_elapseTimer;

    qint64 elapseTime;


    //read Data
    QByteArray readData;

    //Log File
    bool isLogFile;
    QString logName;
    QFile *p_logFile;
    QTextStream out;


};

#endif // TCPSOCKET_H
