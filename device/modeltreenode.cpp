#include "modeltreenode.h"


QString ModelTreeNode::Type() const
{
    return m_Type;
}

void ModelTreeNode::setType(const QString &Type)
{
    m_Type = Type;
}
ModelTreeNode::ModelTreeNode()
{

}

QList<ModelTreeNode> ModelTreeNode::m_ListModelTreeNode;

void ModelTreeNode::LoadModelTree()
{
    QString str = "SELECT * FROM `SwitchTools`.`DeviceTree` ORDER BY `ID`;";
    QSqlQuery query(str);

    ModelTreeNode model;
    m_ListModelTreeNode.clear();

    while(query.next())
        {
        ModelTreeNode model;
        model.setID(query.value(0).toInt());
        model.setNAME(query.value(1).toString());
        model.setParentID(query.value(2).toInt());
        model.setSubID(query.value(3).toInt());
        model.setType(query.value(7).toString());
        m_ListModelTreeNode.append(model);
        }
}

void ModelTreeNode::LoadTreeNode()
{
    ModelChest::LoadModelChest();
    ModelScan::LoadModelScan();
    ModelPeixianjia::LoadModelPeixianjia();
    ModelPeixianjiaLink::LoadModelPeixianjiaLink();
    ModelTreeNode::LoadModelTree();
    ModelSwitch::LoadModelSwitch();
}

int ModelTreeNode::ID() const
{
    return m_ID;
}

void ModelTreeNode::setID(int ID)
{
    m_ID = ID;
}

QString ModelTreeNode::NAME() const
{
    return m_NAME;
}

void ModelTreeNode::setNAME(const QString &NAME)
{
    m_NAME = NAME;
}

int ModelTreeNode::ParentID() const
{
    return m_ParentID;
}

void ModelTreeNode::setParentID(int ParentID)
{
    m_ParentID = ParentID;
}

int ModelTreeNode::SubID() const
{
    return m_SubID;
}

void ModelTreeNode::setSubID(int SubID)
{
    m_SubID = SubID;
}
