#include "modelscan.h"

ModelScan::ModelScan()
{

}

QList<ModelScan> ModelScan::m_ListModelScan;

void ModelScan::LoadModelScan()
{
    QString str = "SELECT * FROM `SwitchTools`.`Scan` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelScan model;
    m_ListModelScan.clear();

    while(query.next())
        {
        model.setID(query.value(0).toInt());
        model.setNAME(query.value(1).toString());
        model.setParentID(query.value(2).toInt());
        model.setIP(query.value(3).toString());
        model.setPort(query.value(4).toInt());
        model.setScanID(query.value(5).toInt());
        model.setMAC(query.value(6).toString());
        model.setMask(query.value(7).toString());
        model.setGate(query.value(8).toString());
        model.setSubID(query.value(9).toInt());
        model.setLinkPortCount(query.value(10).toInt());
        model.setChestID(query.value(11).toInt());
        model.setChestIndex(query.value(12).toInt());
        m_ListModelScan.append(model);
        }
}

int ModelScan::ID() const
{
    return m_ID;
}

void ModelScan::setID(int ID)
{
    m_ID = ID;
}

QString ModelScan::NAME() const
{
    return m_NAME;
}

void ModelScan::setNAME(const QString &NAME)
{
    m_NAME = NAME;
}

int ModelScan::ParentID() const
{
    return m_ParentID;
}

void ModelScan::setParentID(int ParentID)
{
    m_ParentID = ParentID;
}

QString ModelScan::IP() const
{
    return m_IP;
}

void ModelScan::setIP(const QString &IP)
{
    m_IP = IP;
}

int ModelScan::Port() const
{
    return m_Port;
}

void ModelScan::setPort(int Port)
{
    m_Port = Port;
}

int ModelScan::ScanID() const
{
    return m_ScanID;
}

void ModelScan::setScanID(int ScanID)
{
    m_ScanID = ScanID;
}

QString ModelScan::MAC() const
{
    return m_MAC;
}

void ModelScan::setMAC(const QString &MAC)
{
    m_MAC = MAC;
}

QString ModelScan::Mask() const
{
    return m_Mask;
}

void ModelScan::setMask(const QString &Mask)
{
    m_Mask = Mask;
}

QString ModelScan::Gate() const
{
    return m_Gate;
}

void ModelScan::setGate(const QString &Gate)
{
    m_Gate = Gate;
}

int ModelScan::SubID() const
{
    return m_SubID;
}

void ModelScan::setSubID(int SubID)
{
    m_SubID = SubID;
}

int ModelScan::LinkPortCount() const
{
    return m_LinkPortCount;
}

void ModelScan::setLinkPortCount(int LinkPortCount)
{
    m_LinkPortCount = LinkPortCount;
}

int ModelScan::ChestID() const
{
    return m_ChestID;
}

void ModelScan::setChestID(int ChestID)
{
    m_ChestID = ChestID;
}

int ModelScan::ChestIndex() const
{
    return m_ChestIndex;
}

void ModelScan::setChestIndex(int ChestIndex)
{
    m_ChestIndex = ChestIndex;
}


