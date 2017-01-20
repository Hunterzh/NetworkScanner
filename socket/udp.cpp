#include "udp.h"
#include "ui_udp.h"

udp::udp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udp)
{
    ui->setupUi(this);

    sendBuf = new QByteArray(nullptr);
    recvBuf = new QByteArray(nullptr);
    sendBuf->resize(256*1024);
    recvBuf->resize(256*1024);

    sendUdpSocket = new QUdpSocket(this);
    recvUdpSocket = new QUdpSocket(this);

    ui->sendButton->setEnabled(false);
}

udp::~udp()
{
    delete ui;
}


void udp::on_setButton_clicked()
{
     recvPort = ui->rxPortEdit->text().toInt();
     sendPort = ui->txPortEdit->text().toInt();
     ipText = ui->ipEdit->text();

     StartConnect(ipText,recvPort);  //对方IP，监听端口
     ui->sendButton->setEnabled(true);
}

void udp::on_sendButton_clicked()
{
    QByteArray mac;
    mac.resize(6);
    mac[0]=0xB8;
    mac[1]=0xE8;
    mac[2]=0x56;
    mac[3]=0x3F;
    mac[4]=0x11;
    mac[5]=0x9E;

    SendScanConfig("192.168.80.115", "192.168.80.1", "255.255.255.0", 2,mac);
}

void udp::sendData(QByteArray buffer,int pos, int Count)
{

    sendUdpSocket->writeDatagram(buffer, buffer.size(), ipAddress, sendPort);

}

bool udp::StartConnect(QString strIP,int dwPort)  //对方IP，监听端口
 {
     if (strIP.isEmpty()||dwPort == 0)
         return false;

         recvPort = ui->rxPortEdit->text().toInt();
         ipAddress = QHostAddress(strIP);
         recvUdpSocket->bind(QHostAddress::Any,recvPort);
         connect(recvUdpSocket, SIGNAL(readyRead()),this, SLOT(RecvData()));
         return true;
 }

void udp::RecvData()
{
    while (recvUdpSocket->hasPendingDatagrams())
    {
             QByteArray datagram;
             datagram.resize(recvUdpSocket->pendingDatagramSize());

             QHostAddress sender;
             quint16 senderPort;

             recvUdpSocket->readDatagram(datagram.data(), datagram.size(),
                                     &sender, &senderPort);

             ui->receiveEdit->append(datagram);
         }
}

void udp::StopConnect()
{

}

void udp::SocketClose()
{

}

bool udp::SendScanConfig(QString strIP, QString strGate, QString strMask, int dwScanID,QByteArray mac)
{

    quint32 ip = QHostAddress(strIP).toIPv4Address();
    quint32 gate = QHostAddress(strGate).toIPv4Address();
    quint32 mask = QHostAddress(strMask).toIPv4Address();

    //ui->receiveEdit->append(QString::number(ip,16));

    QByteArray data(40,0x00);

    data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
    data[4] = 0x20;     //length
    data[8] = 0x02;    //cmd
    data[12] = (quint8)(dwScanID & 0xFF); data[13] = (quint8)((dwScanID >> 8) & 0xFF); data[14] = (quint8)((dwScanID >> 16) & 0xFF); data[15] = (quint8)((dwScanID >> 24) & 0xFF);
    data[16] = (quint8)(ip & 0xFF); data[17] = (quint8)((ip >> 8) & 0xFF); data[18] = (quint8)((ip >> 16) & 0xFF); data[19] = (quint8)((ip >> 24) & 0xFF);
    data[20] = (quint8)(gate & 0xFF); data[21] = (quint8)((gate >> 8) & 0xFF); data[22] = (quint8)((gate >> 16) & 0xFF); data[23] = (quint8)((gate >> 24) & 0xFF);
    data[24] = (quint8)(mask & 0xFF); data[25] = (quint8)((mask >> 8) & 0xFF); data[26] = (quint8)((mask >> 16) & 0xFF); data[27] = (quint8)((mask >> 24) & 0xFF);
    for (int i = 0; i < 6; i++)
        data[28 + i] = mac[i];

    QByteArray crc = crc32::GetCRC32(data,0,36);
    if (crc.isEmpty() || crc.size()!= 4)
        return false;
    for (int i = 0; i < 4; i++)
        data[36 + i] = crc[i];

    sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
    return true;

}

/*
bool udp::SendScanConfig(QString strIP, QString strGate, QString strMask, int dwScanID)
{

    quint32 ip = QHostAddress(strIP).toIPv4Address();
    quint32 gate = QHostAddress(strGate).toIPv4Address();
    quint32 mask = QHostAddress(strMask).toIPv4Address();

    //ui->receiveEdit->append(QString::number(ip,16));

    QByteArray data;
    data.resize(40);

    data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
    data[4] = 0x20;     //length
    data[8] = 0x02;    //cmd
    data[12] = (quint8)(dwScanID & 0xFF); data[13] = (quint8)((dwScanID >> 8) & 0xFF); data[14] = (quint8)((dwScanID >> 16) & 0xFF); data[15] = (quint8)((dwScanID >> 24) & 0xFF);
    data[16] = (quint8)(ip & 0xFF); data[17] = (quint8)((ip >> 8) & 0xFF); data[18] = (quint8)((ip >> 16) & 0xFF); data[19] = (quint8)((ip >> 24) & 0xFF);
    data[20] = (quint8)(gate & 0xFF); data[21] = (quint8)((gate >> 8) & 0xFF); data[22] = (quint8)((gate >> 16) & 0xFF); data[23] = (quint8)((gate >> 24) & 0xFF);
    data[24] = (quint8)(mask & 0xFF); data[25] = (quint8)((mask >> 8) & 0xFF); data[26] = (quint8)((mask >> 16) & 0xFF); data[27] = (quint8)((mask >> 24) & 0xFF);
    //for (int i = 0; i < 6; i++)
        //data[28 + i] = mac[i];
    //QByteArray crc = crc32::GetCRC32(data,0,36);
    //if (crc.isEmpty() || crc.size()!= 4)
    //    return false;
    //for (int i = 0; i < 4; i++)
    //    data[36 + i] = crc[i];

    sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
    return true;

}
*/
