#ifndef INITDATABASE_H
#define INITDATABASE_H
#include "sqldb.h"
#include <QMessageBox>
#include <QObject>
class initdatabase : public QObject
{
        Q_OBJECT
public:
    initdatabase();

private:
    sqlDb *initDb;

    static QString Create_PeixianjiaType();
    static QVector<QString> Create_PeixianjiaTypeDefault();
    static QString Create_DeviceClassSubType();
    static QString Create_DeviceItem();
    static QString Create_DeviceTree();
    static QString Create_ICON();
    static QString Create_Chest();
    static QString Create_Map();
    static QString Create_MapItem();
    static QString Create_MapLink();
    static QString Create_Switch();
    static QString Create_Peixianjia();
    static QString Create_PeixianjiaPort();
    static QString Create_Port();
    static QString Create_Scan();
    static QString Create_ChestLink();

    static QString Create_OperateLog();
    static QString Create_User();
    static QString Create_DefaultUser();
    static QString Create_DbBackup();


};

#endif // INITDATABASE_H
