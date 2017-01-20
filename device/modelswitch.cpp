#include "modelswitch.h"

ModelSwitch::ModelSwitch()
{

}
QList<ModelSwitch> ModelSwitch::m_ListModelSwitch;
void ModelSwitch::LoadModelSwitch()
{
    QString str = "SELECT * FROM `SwitchTools`.`Switch` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelSwitch model;
    m_ListModelSwitch.clear();

    while(query.next())
        {
        model.setID(query.value(0).toInt());
        model.setNAME(query.value(1).toString());
        model.setPort(query.value(2).toInt());
        model.setModel(query.value(3).toString());
        model.setManufactory(query.value(4).toString());
        m_ListModelSwitch.append(model);
        }
}

int ModelSwitch::ID() const
{
    return m_ID;
}

void ModelSwitch::setID(int ID)
{
    m_ID = ID;
}

QString ModelSwitch::NAME() const
{
    return m_NAME;
}

void ModelSwitch::setNAME(const QString &NAME)
{
    m_NAME = NAME;
}

int ModelSwitch::Port() const
{
    return m_Port;
}

void ModelSwitch::setPort(int Port)
{
    m_Port = Port;
}

QString ModelSwitch::Model() const
{
    return m_Model;
}

void ModelSwitch::setModel(const QString &Model)
{
    m_Model = Model;
}

QString ModelSwitch::Manufactory() const
{
    return m_Manufactory;
}

void ModelSwitch::setManufactory(const QString &Manufactory)
{
    m_Manufactory = Manufactory;
}


