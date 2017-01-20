#include "modelpei.h"


QString ModelPeixianjia::NAME() const
{
    return m_NAME;
}

void ModelPeixianjia::setNAME(const QString &NAME)
{
    m_NAME = NAME;
}
ModelPeixianjia::ModelPeixianjia()
{

}

QList<ModelPeixianjia> ModelPeixianjia::m_ListPeixianjia;

//加载到内存
void ModelPeixianjia::LoadModelPeixianjia()
{
    QString str = "SELECT * FROM `SwitchTools`.`Peixianjia` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelPeixianjia model;
    m_ListPeixianjia.clear();

    while(query.next())
        {
        model.setID(query.value(0).toInt());
        model.setScanID(query.value(1).toInt());
        model.setScanPort(query.value(2).toInt());
        model.setPeixianjiaID(query.value(3).toInt());
        model.setNAME(query.value(4).toString());
        model.setType(query.value(5).toString());
        model.setModel(query.value(6).toString());
        model.setManufactory(query.value(7).toString());
        model.setAdmin(query.value(8).toString());
        m_ListPeixianjia.append(model);
        }
}

QString ModelPeixianjia::Type() const
{
    return m_Type;
}

void ModelPeixianjia::setType(const QString &Type)
{
    m_Type = Type;
}

QString ModelPeixianjia::Manufactory() const
{
    return m_Manufactory;
}

void ModelPeixianjia::setManufactory(const QString &Manufactory)
{
    m_Manufactory = Manufactory;
}

QString ModelPeixianjia::Model() const
{
    return m_Model;
}

void ModelPeixianjia::setModel(const QString &Model)
{
    m_Model = Model;
}

QString ModelPeixianjia::Admin() const
{
    return m_Admin;
}

void ModelPeixianjia::setAdmin(const QString &Admin)
{
    m_Admin = Admin;
}

int ModelPeixianjia::ID() const
{
    return m_ID;
}

void ModelPeixianjia::setID(int ID)
{
    m_ID = ID;
}

int ModelPeixianjia::ScanID() const
{
    return m_ScanID;
}

void ModelPeixianjia::setScanID(int ScanID)
{
    m_ScanID = ScanID;
}

int ModelPeixianjia::ScanPort() const
{
    return m_ScanPort;
}

void ModelPeixianjia::setScanPort(int ScanPort)
{
    m_ScanPort = ScanPort;
}

int ModelPeixianjia::PeixianjiaID() const
{
    return m_PeixianjiaID;
}

void ModelPeixianjia::setPeixianjiaID(int PeixianjiaID)
{
    m_PeixianjiaID = PeixianjiaID;
}


