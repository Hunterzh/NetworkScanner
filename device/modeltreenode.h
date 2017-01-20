#ifndef MODELTREENODE_H
#define MODELTREENODE_H
#include <QList>
#include <QDateTime>
#include "sqldb.h"
#include "modelchest.h"
#include "modelpei.h"
#include "modelscan.h"
#include "modelswitch.h"
#include "modelpeixianjialink.h"

class ModelTreeNode
{
private:
    int m_ID;
    QString m_NAME;
    int m_ParentID;
    int m_SubID;
    QString m_Type;

public:
    ModelTreeNode();
    static QList<ModelTreeNode> m_ListModelTreeNode;
    static void LoadModelTree();
    static void LoadTreeNode();
    //数据库ID
    int ID() const;
    void setID(int ID);
    //名称
    QString NAME() const;
    void setNAME(const QString &NAME);
    //父ID
    int ParentID() const;
    void setParentID(int ParentID);
    //子ID
    int SubID() const;
    void setSubID(int SubID);
    //设备类型
    QString Type() const;
    void setType(const QString &Type);
};

#endif // MODELTREENODE_H
