#ifndef MODELSCAN_H
#define MODELSCAN_H
#include <QList>
#include <QDateTime>
#include "sqldb.h"

class ModelScan
{
private:
    int m_ID;
    QString m_NAME;
    int m_ParentID;
    QString m_IP;
    int m_Port;
    int m_ScanID;
    QString m_MAC;
    QString m_Mask;
    QString m_Gate;
    int m_SubID;
    int m_LinkPortCount;
    int m_ChestID;
    int m_ChestIndex;

public:
    ModelScan();
    static QList<ModelScan> m_ListModelScan;
    static void LoadModelScan();
    //数据库ID
    int ID() const;
    void setID(int ID);
    //名称
    QString NAME() const;
    void setNAME(const QString &NAME);
    //父ID
    int ParentID() const;
    void setParentID(int ParentID);
    //IP地址
    QString IP() const;
    void setIP(const QString &IP);
    //端口
    int Port() const;
    void setPort(int Port);
    //扫描仪ID
    int ScanID() const;
    void setScanID(int ScanID);
    //MAC地址
    QString MAC() const;
    void setMAC(const QString &MAC);
    //子网掩码
    QString Mask() const;
    void setMask(const QString &Mask);
    //网关
    QString Gate() const;
    void setGate(const QString &Gate);
    //子机编号
    int SubID() const;
    void setSubID(int SubID);
    //检测端口数量
    int LinkPortCount() const;
    void setLinkPortCount(int LinkPortCount);
    //连接机柜ID
    int ChestID() const;
    void setChestID(int ChestID);
    //连接机柜位置
    int ChestIndex() const;
    void setChestIndex(int ChestIndex);
};

#endif // MODELSCAN_H
