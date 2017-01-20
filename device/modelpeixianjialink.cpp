#include "modelpeixianjialink.h"

ModelPeixianjiaLink::ModelPeixianjiaLink()
{

}

QList<ModelPeixianjiaLink> ModelPeixianjiaLink::m_ListModelPeixianjiaLink;

void ModelPeixianjiaLink::LoadModelPeixianjiaLink()
{
    QString str = "SELECT * FROM `SwitchTools`.`PeixianjiaLink` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelPeixianjiaLink model;
    m_ListModelPeixianjiaLink.clear();

    while(query.next())
        {
        model.setID(query.value(0).toInt());
        model.setSwitchID(query.value(1).toInt());
        model.setSwitchPort(query.value(2).toInt());
        //model结构体
        model.setDeviceID(query.value(4).toInt());
        model.setDeviceType(query.value(5).toInt());

        m_ListModelPeixianjiaLink.append(model);
        }
}

int ModelPeixianjiaLink::ID() const
{
    return m_ID;
}

void ModelPeixianjiaLink::setID(int ID)
{
    m_ID = ID;
}

int ModelPeixianjiaLink::SwitchID() const
{
    return m_SwitchID;
}

void ModelPeixianjiaLink::setSwitchID(int SwitchID)
{
    m_SwitchID = SwitchID;
}

int ModelPeixianjiaLink::SwitchPort() const
{
    return m_SwitchPort;
}

void ModelPeixianjiaLink::setSwitchPort(int SwitchPort)
{
    m_SwitchPort = SwitchPort;
}

int ModelPeixianjiaLink::DeviceID() const
{
    return m_DeviceID;
}

void ModelPeixianjiaLink::setDeviceID(int DeviceID)
{
    m_DeviceID = DeviceID;
}

int ModelPeixianjiaLink::DeviceType() const
{
    return m_DeviceType;
}

void ModelPeixianjiaLink::setDeviceType(int DeviceType)
{
    m_DeviceType = DeviceType;
}


