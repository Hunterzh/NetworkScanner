#include "modelchest.h"

ModelChest::ModelChest()
{

}

QList<ModelChest> ModelChest::m_ListModelChest;

//加载所有机柜信息到列表ListModelChest
void ModelChest::LoadModelChest()
{
    QString str = "SELECT * FROM `SwitchTools`.`Chest` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelChest model;
    m_ListModelChest.clear();

    while(query.next())
        {
        model.setID(query.value(0).toInt());
        model.setNAME(query.value(1).toString());
        model.setParentID(query.value(2).toInt());
        model.setOrder(query.value(3).toInt());
        model.setDeviceType(query.value(4).toString());
        model.setHeight(query.value(5).toInt());
        model.setWidth(query.value(6).toInt());
        model.setDepth(query.value(7).toInt());
        model.setModel(query.value(8).toString());
        model.setManufactory(query.value(9).toString());
        model.setDepartment(query.value(10).toString());
        model.setBuyDate(query.value(11).toDateTime());
        model.setPrice(query.value(12).toInt());
        model.setAdaministrator(query.value(13).toString());
        model.setDescription(query.value(14).toString());
        m_ListModelChest.append(model);
        }
}

int ModelChest::ID() const
{
    return m_ID;
}

void ModelChest::setID(int ID)
{
    m_ID = ID;
}


QString ModelChest::NAME() const
{
    return m_NAME;
}

void ModelChest::setNAME(const QString &NAME)
{
    m_NAME = NAME;
}


int ModelChest::ParentID() const
{
    return m_ParentID;
}

void ModelChest::setParentID(int ParentID)
{
    m_ParentID = ParentID;
}

int ModelChest::Order() const
{
    return m_Order;
}

void ModelChest::setOrder(int Order)
{
    m_Order = Order;
}


QString ModelChest::DeviceType() const
{
    return m_DeviceType;
}

void ModelChest::setDeviceType(const QString &DeviceType)
{
    m_DeviceType = DeviceType;
}

int ModelChest::Height() const
{
    return m_Height;
}

void ModelChest::setHeight(int Height)
{
    m_Height = Height;
}

int ModelChest::Width() const
{
    return m_Width;
}

void ModelChest::setWidth(int Width)
{
    m_Width = Width;
}

int ModelChest::Depth() const
{
    return m_Depth;
}

void ModelChest::setDepth(int Depth)
{
    m_Depth = Depth;
}

QString ModelChest::Model() const
{
    return m_Model;
}

void ModelChest::setModel(const QString &Model)
{
    m_Model = Model;
}

QString ModelChest::Manufactory() const
{
    return m_Manufactory;
}

void ModelChest::setManufactory(const QString &Manufactory)
{
    m_Manufactory = Manufactory;
}

QString ModelChest::Department() const
{
    return m_Department;
}

void ModelChest::setDepartment(const QString &Department)
{
    m_Department = Department;
}

QDateTime ModelChest::BuyDate() const
{
    return m_BuyDate;
}

void ModelChest::setBuyDate(const QDateTime &BuyDate)
{
    m_BuyDate = BuyDate;
}

float ModelChest::Price() const
{
    return m_Price;
}

void ModelChest::setPrice(float Price)
{
    m_Price = Price;
}

QString ModelChest::Adaministrator() const
{
    return m_Adaministrator;
}

void ModelChest::setAdaministrator(const QString &Adaministrator)
{
    m_Adaministrator = Adaministrator;
}

QString ModelChest::Description() const
{
    return m_Description;
}

void ModelChest::setDescription(const QString &Description)
{
    m_Description = Description;
}



