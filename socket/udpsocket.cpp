#include "udpsocket.h"

udpsocket::udpsocket()
{
    sendUdpSocket = new QUdpSocket();
    recvUdpSocket = new QUdpSocket();
    timer = new QTimer(this);
    timer->start(3000);  //3s周期启动

    PeiAlm.resize(6);


    connect(timer,SIGNAL(timeout()),this,SLOT(TimerElapsed()));
}

//定时器响应
void udpsocket::TimerElapsed()
{
    //SendHeart();
    SendTimeHeart();
}

//建立udp连接
bool udpsocket::StartConnect(QString strIP,int rxPort,int txPort)  //对方IP，监听端口
 {
     if (strIP.isEmpty()||rxPort == 0)
         return false;

         ipAddress = QHostAddress(strIP);
         sendPort = txPort;
         recvUdpSocket->bind(QHostAddress::Any,rxPort);
         connect(recvUdpSocket, SIGNAL(readyRead()),this, SLOT(RecvData()));
         //connect(recvUdpSocket, SIGNAL(readyRead()),this, SLOT(OnSocketRecvData()));
         return true;
}


//发送数据
void udpsocket::sendData(QByteArray buffer)
{
    sendUdpSocket->writeDatagram(buffer, buffer.size(), ipAddress, sendPort);
}

//接收数据
void udpsocket::RecvData()
{

    while (recvUdpSocket->hasPendingDatagrams())
    {
     QByteArray buffer;
     buffer.resize(recvUdpSocket->pendingDatagramSize());

     QHostAddress sender;
     quint16 senderPort;

     recvUdpSocket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

     OnSocketRecvData(buffer);
    }
}

//发送心跳
void udpsocket::SendHeart()
{
    QByteArray data(16,0x00);

    data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
    data[4] = 0x08;     //length
    data[8] = 0x04; data[9] = 0x00; data[10] = 0x01; data[11] = 0x01;

    QByteArray crc = crc32::GetCRC32(data, 0, 12);
    if (crc.isEmpty() || crc.size() != 4)
        return;
    for (int i = 0; i < 4; i++)
        data[12 + i] = crc[i];
    sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
}

//发送时间心跳
void udpsocket::SendTimeHeart()
{
    QByteArray data(32,0x00);
    QDateTime time = QDateTime::currentDateTime();
    data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
    data[4] = 0x018;     //length
    data[8] = 0x03;    //cmd
    QString strDate = time.toString("yyyy-MM-dd HH:mm");//string.Format("{0:yyyy-MM-dd HH:mm}", date->currentTime());
    QByteArray bytedate = strDate.toLatin1();
    for (int i = 0; i < 16; i++)
        data[12 + i] = bytedate[i];
    QByteArray crc = crc32::GetCRC32(data, 0, 28);
    if (crc.isEmpty() || crc.size() != 4)
        return;
    for (int i = 0; i < 4; i++)
        data[28 + i] = crc[i];
    sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
}


//修改扫描仪参数
bool udpsocket::SendScanConfig(QString strIP, QString strGate, QString strMask, int dwScanID,QByteArray mac)
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


int udpsocket::OnSocketRecvData(QByteArray buffer)
{
    int count = buffer.size();
    int index = 0;

    //QMessageBox::about(NULL,"count",QString::number(count,10));


       if (buffer.isEmpty())
           return 0;

       while (index < count)
       {
           if (count - index < 8)
               return index;
           if ((quint8)buffer[index + 0] != 0x4e && (quint8)buffer[index + 1] != 0x41 && (quint8)buffer[index + 2] != 0x43 && (quint8)buffer[index + 3] != 0x53)
           {
               index++;
               continue;
           }
           int size = (buffer[index + 4]) + (buffer[index + 5] << 8) + (buffer[index + 6] << 16) + (buffer[index + 7] << 24);
//           if (size > 4096)
//           {
//               //非法指令
//               index += size + 8;  //退出while
//               continue;
//           }
//           if (count - index < size + 8)  //count=size+8正常
//               return index;

           //crc校验
           QByteArray crc = crc32::GetCRC32(buffer, index, size + 4);
           if (crc[0] == buffer[index + size + 4] &&
               crc[1] == buffer[index + size + 5] &&
               crc[2] == buffer[index + size + 6] &&
               crc[3] == buffer[index + size + 7])
           {

           }
           else
           {
               QMessageBox::about(NULL,"error","crc error");
               //校验不正确
               index += size + 8;  //退出while
               //continue;
           }

           quint32 dwCmd = (quint32)((buffer[index + 8]) + (buffer[index + 9] << 8) + (buffer[index + 10] << 16) + (buffer[index + 11] << 24));
           //QMessageBox::about(NULL,"cmd",QString::number(dwCmd,16));
           switch (dwCmd)
           {
//           case 0x10000001: //查询在线
//               {

//               }
//               break;
//           case 0x10000003: //心跳回复
//               {

//               }
//               break;
//           case 0x11000001:    //上传配置的回复
//               {
//               }
//               break;
           case 0x11000002:    //链路断开警报
               {
               if (size != 20)
                   break;
               SendAlmAck();
               int scanID = buffer[index + 12] + (buffer[index + 13] << 8) + (buffer[index + 14] << 16) + (buffer[index + 15] << 24);
               quint8 AlmType = buffer[index + 20];

               PeiAlm[0]=QString::number(scanID,10);
               PeiAlm[1]=QString::number(buffer[16],10);  //sort1
               PeiAlm[2]=QString::number(buffer[17],10);  //port1
               PeiAlm[3]=QString::number(buffer[18],10);  //sort2
               PeiAlm[4]=QString::number(buffer[19],10);  //port2
               PeiAlm[5]=QString::number(AlmType,10);

               emit PeiXianAlm(PeiAlm);
               //QMessageBox::about(NULL,"flag","goin");
               }
               break;
           case 0x11000003:    //链路恢复
               {

               }
               break;
           case 0x11000004:    //配线架连接端口状态
               {
               if (size != 36)
                   break;
               SendPeixianStatusAck();
               int ScanID = buffer[index + 12] + (buffer[index + 13] << 8) + (buffer[index + 14] << 16) + (buffer[index + 15] << 24);

               portStatus.resize(24);
               for(int i=0;i<24;i++)
               {
                   portStatus.append((buffer[index + 16 + i]));
               }

               }
               break;

           }
           //buffer.clear();
           index += size + 8;  //退出while

       }
       return index;
}

//报警接收ACK
void udpsocket::SendAlmAck()
{
    QByteArray data(16,0x00);
    data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
    data[4] = 0x08;     //length
    data[8] = 0x02;
    data[11] = 0x01;    //cmd

    QByteArray crc = crc32::GetCRC32(data, 0, 12);
    if (crc.isEmpty() || crc.size() != 4)
        return;
    for (int i = 0; i < 4; i++)
        data[12 + i] = crc[i];
    sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
}

//配线架端口状态ACK
void udpsocket::SendPeixianStatusAck()
{
        QByteArray data(16,0x00);
        data[0] = 0x4e; data[1] = 0x41; data[2] = 0x43; data[3] = 0x53;
        data[4] = 0x08;     //length
        data[8] = 0x04;
        data[11] = 0x01;    //cmd

        QByteArray crc = crc32::GetCRC32(data, 0, 12);
        if (crc.isEmpty() || crc.size() != 4)
            return;
        for (int i = 0; i < 4; i++)
            data[12 + i] = crc[i];
        sendUdpSocket->writeDatagram(data, data.size(), ipAddress, sendPort);
}
