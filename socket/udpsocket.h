#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QVector>
#include "crc32.h"
#include "modelpei.h"
//#include "externvalue.h"

class udpsocket : public QObject
{
    Q_OBJECT
public:
    QByteArray sendBuffer;
    QByteArray recvBuffer;
    QTimer* timer;
    QByteArray portStatus;
    QVector<QString> PeiAlm;


    udpsocket();

    //发送数据
    void sendData(QByteArray buffer);
    //创建连接
    bool StartConnect(QString strIP,int rxPort,int txPort);
    //发送心跳
    void SendHeart();
    //发送时间心跳
    void SendTimeHeart();
    //配置/修改扫描仪
    bool SendScanConfig(QString strIP, QString strGate, QString strMask, int dwScanID,QByteArray mac);
    //配线架状态ACK
    void SendPeixianStatusAck();
    //配线架报警ACK
    void SendAlmAck();
    //接收识别命令
    int OnSocketRecvData(QByteArray buffer);

signals:
    void PeiXianAlm(QVector<QString>);


public slots:
    //发送时间
    void TimerElapsed();
    //接收数据
    void RecvData();


private:
    QUdpSocket* sendUdpSocket;
    QUdpSocket* recvUdpSocket;
    QHostAddress ipAddress;
    int sendPort;
    int recvPort;


};

#endif // UDPSOCKET_H
