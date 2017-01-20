#ifndef MODELPEI_H
#define MODELPEI_H
#include <QObject>
#include <QVector>
#include <QString>
#include "sqldb.h"
#include "externvalue.h"

class ModelPeixianjia
{
private:
    int m_ID;
    int m_ScanID;
    int m_ScanPort;
    int m_PeixianjiaID;
    QString m_NAME;
    QString m_Type;
    QString m_Manufactory;
    QString m_Model;
    QString m_Admin;

public:
    ModelPeixianjia();
    //列表
    static QList<ModelPeixianjia> m_ListPeixianjia;
    //加载内存
    static void LoadModelPeixianjia();
    //数据库ID
    int ID() const;
    void setID(int ID);
    //扫描仪ID
    int ScanID() const;
    void setScanID(int ScanID);
    //扫描仪端口
    int ScanPort() const;
    void setScanPort(int ScanPort);
    //配线架ID
    int PeixianjiaID() const;
    void setPeixianjiaID(int PeixianjiaID);
    //类型
    QString Type() const;
    void setType(const QString &Type);
    //厂家
    QString Manufactory() const;
    void setManufactory(const QString &Manufactory);
    //型号
    QString Model() const;
    void setModel(const QString &Model);
    //管理员
    QString Admin() const;
    void setAdmin(const QString &Admin);
    //名称
    QString NAME() const;
    void setNAME(const QString &NAME);
};

#endif // MODELPEI_H
