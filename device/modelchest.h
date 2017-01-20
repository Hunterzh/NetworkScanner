#ifndef MODELCHEST_H
#define MODELCHEST_H
#include <QList>
#include <QDateTime>
#include "sqldb.h"

class ModelChest
{
    private:
        int m_ID;
        QString m_NAME;
        int m_ParentID;
        int m_Order;
        QString m_DeviceType;
        int m_Height;
        int m_Width;
        int m_Depth;
        QString m_Model;
        QString m_Manufactory;
        QString m_Department;
        QDateTime m_BuyDate;
        float m_Price;
        QString m_Adaministrator;
        QString m_Description;

    public:
        ModelChest();
        //机柜列表
        static QList<ModelChest> m_ListModelChest;
        //加载所有机柜信息到列表ListModelChest
        static void LoadModelChest();
        //static void RemoveChest(modeltreenode model);
        //数据库ID
        int ID() const;
        void setID(int ID);
        //名称
        QString NAME() const;
        void setNAME(const QString &NAME);
        //父ID
        int ParentID() const;
        void setParentID(int ParenID);
        //排序规则
        int Order() const;
        void setOrder(int Order);
        //设备类型
        QString DeviceType() const;
        void setDeviceType(const QString &DeviceType);
        //设备高度
        int Height() const;
        void setHeight(int Height);
        //设备宽度
        int Width() const;
        void setWidth(int Width);
        //设备深度
        int Depth() const;
        void setDepth(int Depth);
        //产品型号
        QString Model() const;
        void setModel(const QString &Model);
        //产品厂家
        QString Manufactory() const;
        void setManufactory(const QString &Manufactory);
        //使用部门
        QString Department() const;
        void setDepartment(const QString &Department);
        //购买时间
        QDateTime BuyDate() const;
        void setBuyDate(const QDateTime &BuyDate);
        //购买价格
        float Price() const;
        void setPrice(float Price);
        //管理员
        QString Adaministrator() const;
        void setAdaministrator(const QString &Adaministrator);
        //描述
        QString Description() const;
        void setDescription(const QString &Description);

};

#endif // MODELCHEST_H
