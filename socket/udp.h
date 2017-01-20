#ifndef UDP_H
#define UDP_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include "crc32.h"

namespace Ui {
class udp;
}

class udp : public QMainWindow
{
    Q_OBJECT

public:
    explicit udp(QWidget *parent = 0);
    ~udp();
    void StopConnect();
    void SocketClose();
    void sendData(QByteArray buffer,int pos, int Count);
    //void RecvData();
    bool StartConnect(QString strIP,int dwPort);
    bool SendScanConfig(QString strIP, QString strGate, QString strMask, int dwScanID,QByteArray mac);

private:
    Ui::udp *ui;
    QUdpSocket *sendUdpSocket;
    QUdpSocket *recvUdpSocket;
    QHostAddress ipAddress;
    //QHostAddress gateAddress;
    //QHostAddress maskAddress;
    int sendPort;
    int recvPort;
    QString ipText;
    QByteArray *sendBuf;
    QByteArray *recvBuf;

private slots:
    void on_setButton_clicked();
    void on_sendButton_clicked();
    void RecvData();
};

#endif // UDP_H
