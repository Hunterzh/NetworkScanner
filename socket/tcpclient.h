#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

class tcpclient : QObject
{
    Q_OBJECT

public:
    tcpclient();
    bool status;
    QHostAddress* serverIP;
    QTcpSocket* tcpSocket;
    void creatConnection(QString ip,int port);
    void closeConnection();
    void sendData(QByteArray data);

public slots:
    QByteArray receivedData();
};

#endif // TCPCLIENT_H
