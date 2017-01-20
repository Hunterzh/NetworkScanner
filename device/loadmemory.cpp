#include "loadmemory.h"

LoadMemory::LoadMemory()
{

}

void LoadMemory::LoadModelChest()
{
    QString str = "SELECT * FROM `SwitchTools`.`Chest` ORDER BY `ID`;";
    QSqlQuery query(str);

    while(query.next())
        {
        ModelChest model;
        model.setID(query.value(0).toInt());
        model.setNAME(query.value(1).toString());
        model.setParenID(query.value(2).toInt());
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

