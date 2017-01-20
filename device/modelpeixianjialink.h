#ifndef MODELPEIXIANJIALINK_H
#define MODELPEIXIANJIALINK_H
#include <QObject>
#include <QVector>
#include <QString>
#include "sqldb.h"

class ModelPeixianjiaLink
{
    //配线架信息结构体
    struct peixianjiaLinkStruct
    {
        int dwIndex;         //起始编号
        int dwScanID;        //扫描仪编号     tb_Scan数据库ID
        int dwScanPort;      //扫描仪端口     0-23
        int dwPeixianID;     //配线架编号     tb_NetDevice数据库ID
        int dwPeixianPort;   //配线架端口     0-23
    };
    //上传工单结构体
    struct UploadLinkStruct
    {
        int dwScanID;
        quint8 dwScanPort1;
        quint8 dwPeixianPort1;
        quint8 dwScanPort2;
        quint8 dwPeixianPort2;
    };

private:
    int m_ID;
    int m_SwitchID;
    int m_SwitchPort;
    int m_DeviceID;
    int m_DeviceType;


public:
    peixianjiaLinkStruct m_Link;
    ModelPeixianjiaLink();
    //列表
    static QList<ModelPeixianjiaLink> m_ListModelPeixianjiaLink;
    //加载内存
    static void LoadModelPeixianjiaLink();
    //数据库ID
    int ID() const;
    void setID(int ID);
    //交换机ID
    int SwitchID() const;
    void setSwitchID(int SwitchID);
    //交换机端口
    int SwitchPort() const;
    void setSwitchPort(int SwitchPort);
    //设备ID
    int DeviceID() const;
    void setDeviceID(int DeviceID);
    //设备类型
    int DeviceType() const;
    void setDeviceType(int DeviceType);

};

#endif // MODELPEIXIANJIALINK_H
