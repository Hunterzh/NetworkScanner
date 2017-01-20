#ifndef MODELSWITCH_H
#define MODELSWITCH_H
#include <QList>
#include <QDateTime>
#include "sqldb.h"

class ModelSwitch
{
private:
    int m_ID;
    QString m_NAME;
    int m_Port;
    QString m_Model;
    QString m_Manufactory;

public:
    ModelSwitch();
    //交换机列表
    static QList<ModelSwitch> m_ListModelSwitch;
    //加载内存
    static void LoadModelSwitch();
    //名称
    QString NAME() const;
    void setNAME(const QString &NAME);
    //端口数
    int Port() const;
    void setPort(int Port);
    //型号
    QString Model() const;
    void setModel(const QString &Model);
    //厂家
    QString Manufactory() const;
    void setManufactory(const QString &Manufactory);
    //数据库ID
    int ID() const;
    void setID(int ID);
};

#endif // MODELSWITCH_H
