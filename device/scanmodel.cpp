#include "scanmodel.h"

scanModel::scanModel()
{

}

// 数据库ID
int scanModel::getDbId()
{
    return m_DbId;
}
void scanModel::setDbId(int id)
{
    m_DbId = id;
}

//扫描仪名称
QString scanModel::getName()
{
    return m_Name;
}
void scanModel::setName(QString name)
{
    m_Name = name;
}

//父ID
int scanModel::getParentId()
{
    return m_ParentId;
}
void scanModel::setParentId(int id)
{
    m_ParentId = id;
}

//IP
QString scanModel::getIp()
{
    return m_Ip;
}
void scanModel::setIp(QString ip)
{
    m_Ip = ip;
}

//端口
int scanModel::getPort()
{
    return m_Port;
}
void scanModel::setPort(int port)
{
    m_Port = port;
}

//扫描仪编号ID
int scanModel::getScanId()
{
    return m_ScanId;
}
void scanModel::setScanId(int id)
{
    m_ScanId = id;
}

//mac地址
QString scanModel::getMac()
{
    return m_Mac;
}
void scanModel::setMac(QString mac)
{
    m_Mac = mac;
}

//掩码
QString scanModel::getMask()
{
    return m_Mask;
}
void scanModel::setMask(QString mask)
{
    m_Mask = mask;
}

//网关
QString scanModel::getGate()
{
    return m_Gate;
}
void scanModel::setGate(QString gate)
{
    m_Gate = gate;
}

// 设备槽口连接状态 0未配置, 1未连接，2已经连接
QByteArray scanModel::getPortLinkStatus()
{
    return m_PortLinkStatus;
}

void scanModel::setPortLinkStatus(int port, int status)
{
    m_PortLinkStatus[port] = status;
}


//是否在线，0不在，1在线
int scanModel::getLiveTick()
{
    return m_LiveTick;
}
void scanModel::setLiveTick(int tick)
{
    m_LiveTick = tick;
}
