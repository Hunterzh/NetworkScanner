#include "tcpclient.h"


tcpclient::tcpclient()
{
    status = false;
    serverIP = new QHostAddress();  //创建一个主机IP地址

}

//创建连接
void tcpclient::creatConnection(QString ip,int port)
{
        serverIP->setAddress(ip);

        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receivedData()));   //readyRead()是数据传入信号,当数据来临时会发出这个信号，bytesAvailable()是函数,该函数返回当前已经获取的数据的大小
        tcpSocket->connectToHost(*serverIP,port); //客户端连接服务器
        status = true;  //链接成功
}

//关闭连接
void tcpclient::closeConnection()
{
    tcpSocket->disconnectFromHost();  //与服务器断开
    status = false;  //设置状态位为断开状态
}

//发送数据
void tcpclient::sendData(QByteArray data)  //客户端发送信息
{
    tcpSocket->write(data,data.length());  //发送信息
}

//接收数据
QByteArray tcpclient::receivedData()
{
    QByteArray datagram; //字节数组
    while(tcpSocket->bytesAvailable()>0)  //当接收数据大于0时开始接收
    {
        datagram.resize(tcpSocket->bytesAvailable()); //设置字节数组的大小
        tcpSocket->read(datagram.data(),datagram.size()); //读取来自服务器的数据
    }
    return datagram;
}

