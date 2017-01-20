#include "sqldb.h"

sqlDb::sqlDb()
{

}

bool sqlDb::createConnection(QString HostIp, QString userName, int port, QString password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HostIp);
    db.setUserName(userName);
    db.setPort(port);
    //db.setDatabaseName("sailer");
    db.setPassword(password);

    bool ok = db.open();
    if(!ok)
        return false;
    else
        return true;
}

bool sqlDb::creatDatabase(QString databaseName)
{
    QSqlQuery query;
    QString db = QString("CREATE DATABASE `%1`CHARACTER SET utf8 COLLATE utf8_general_ci;").arg(databaseName);
    query.prepare(db);
    if(query.exec())
        return true;
    else
        return false;
}

bool sqlDb::searchDatabase(QString databaseName)
{
    QString querySearch = QString("SHOW DATABASES;");
    QSqlQuery query(querySearch);
    while(query.next())
    {
        if(databaseName==query.value(0).toString())
            return true;
    }
    return false;
}

bool sqlDb::creatTabel(QString databaseName,QString tabel,QVector<QString> list)
{
    QString dbTabel = QString("CREATE TABLE `%1`.`%2`() CHARSET=utf8 COLLATE=utf8_general_ci;").arg(databaseName).arg(tabel);
    QString tabelName;
    for(int i=0;i<list.count();i++)
    {
        if(i==(list.count()-2))
         {
          tabelName.append(QString("`%1`%2").arg(list[i]).arg(list[i+1]));
         }
        else
          tabelName.append(QString("`%1`%2,").arg(list[i]).arg(list[i+1]));

        i++;
    }

    dbTabel.insert(dbTabel.indexOf("(")+1,tabelName);

    QSqlQuery query;
    query.prepare(dbTabel);
    if(query.exec())
        return true;
    else
        return false;
}

bool sqlDb::creatTabel(QString tabel)
{
    QSqlQuery query;
    query.prepare(tabel);
    if(query.exec())
        return true;
    else
        return false;
}

bool sqlDb::searchTabel(QString databaseName, QString tabel)
{
    if(searchDatabase(databaseName))  //USE sailer;SHOW TABLES LIKE 'chest';
    {
        QString use = QString("USE %1").arg(databaseName);
        QString search = QString("SHOW TABLES LIKE '%1';").arg(tabel);

        QSqlQuery queryUse(use);
        queryUse.next();
        QSqlQuery query(search);
        if(query.next())
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }

}

bool sqlDb::addData(QString databaseName,QString tabel,QVector<QString> listValue)
{
    QString addText = QString("INSERT INTO `%1`() VALUES();").arg(tabel);
    QString addName,addValue;
    QVector<QString> nameBuf;

    if(searchTabel(databaseName,tabel))
    {
        QString getColumn = QString("SHOW COLUMNS FROM %1.`%2`;").arg(databaseName).arg(tabel);
        QSqlQuery queryGet(getColumn);

        while(queryGet.next())
        {
            nameBuf<<queryGet.value(0).toString();
        }

        for(int i=0;i<nameBuf.count();i++)
        {
            if(i==(nameBuf.count()-1))
             {
                addName.append(QString("`%1`").arg(nameBuf[i]));
                addValue.append(QString("'%1'").arg(listValue[i]));
             }
            else
            {
                addName.append(QString("`%1`,").arg(nameBuf[i]));
                addValue.append(QString("'%1',").arg(listValue[i]));
            }
        }

        addText.insert(addText.indexOf("`(")+2,addName);
        addText.insert(addText.indexOf("S(")+2,addValue);

        QSqlQuery query;
        query.prepare(addText);
        if(query.exec())
            return true;
        else
            return false;

    }
    else
        return false;
}

bool sqlDb::insertData(QString str)
{
    QSqlQuery query;
    query.prepare(str);
    if(query.exec())
        return true;
    else
        return false;
}

bool sqlDb::deleteData(QString databaseName,QString tabel,QString where,QString what)
{
    QString deleteText = QString("DELETE FROM `%1`.`%2` WHERE `%3` = '%4';").arg(databaseName).arg(tabel).arg(where).arg(what);
    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query;
        query.prepare(deleteText);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool sqlDb::changeData(QString databaseName, QString tabel, QVector<QString> listValue, QString where, QString what)
{
    QString changeText = QString("UPDATE `%1`.`%2` SET  WHERE `%3` = '%4';").arg(databaseName).arg(tabel).arg(where).arg(what);
    QString setText;
    QVector<QString> nameBuf;

    if(searchTabel(databaseName,tabel))
    {
        QString getColumn = QString("SHOW COLUMNS FROM %1.`%2`;").arg(databaseName).arg(tabel);
        QSqlQuery queryGet(getColumn);

        while(queryGet.next())
        {
            nameBuf<<queryGet.value(0).toString();
        }

        for(int i=0;i<nameBuf.count();i++)
        {
            if(i==(nameBuf.count()-1))
             {
                setText.append(QString("`%1`='%2'").arg(nameBuf[i]).arg(listValue[i]));
             }
            else
            {
                setText.append(QString("`%1`='%2',").arg(nameBuf[i]).arg(listValue[i]));
            }
        }

        changeText.insert(changeText.indexOf("WHERE")-2,setText);

        QSqlQuery query;
        query.prepare(changeText);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool sqlDb::selectData(QString databaseName, QString tabel, QString where, QString what)
{
    QString selectText = QString("SELECT * FROM `%1`.`%2`  WHERE `%3` = '%4';").arg(databaseName).arg(tabel).arg(where).arg(what);

    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query(selectText);
        if(query.next())
            return true;
        else
            return false;
    }
    else
        return false;
}

QVector<QString> sqlDb::selectListData(QString databaseName, QString tabel, QString coloumn, QString where, QString what)
{
    QString selectText = QString("SELECT `%1` FROM `%2`.`%3`  WHERE `%4` = '%5';").arg(coloumn).arg(databaseName).arg(tabel).arg(where).arg(what);
    QVector<QString> data;

    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query(selectText);
        while(query.next())
        {
            data<<query.value(0).toString();
        }
        return data;
    }
    else
        return data;

}

QString sqlDb::selectOneData(QString databaseName, QString tabel, QString coloumn, QString where, QString what)
{
    QString selectText = QString("SELECT `%1` FROM `%2`.`%3`  WHERE `%4` = '%5';").arg(coloumn).arg(databaseName).arg(tabel).arg(where).arg(what);
    QString data;

    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query(selectText);
        query.next();
        data = query.value(0).toString();
        return data;
    }
    else
        return data;
}

QVector<QString> sqlDb::selectAllData(QString databaseName, QString tabel, QString coloumn)
{
    QString selectText = QString("SELECT `%1` FROM `%2`.`%3`;").arg(coloumn).arg(databaseName).arg(tabel);
    QVector<QString> data;

    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query(selectText);
        while(query.next())
        {
            data<<query.value(0).toString();
        }
        return data;
    }
    else
        return data;
}

QVector<QString> sqlDb::selectSingleData(QString databaseName, QString tabel ,int coloumnNumber,QString where, QString what)
{
    QString selectText = QString("SELECT * FROM `%1`.`%2`  WHERE `%3` = '%4';").arg(databaseName).arg(tabel).arg(where).arg(what);
    QVector<QString> data;

    if(searchTabel(databaseName,tabel))
    {
        QSqlQuery query(selectText);
        while(query.next())
        {
            for(int i=0;i<coloumnNumber-1;i++)
            data<<query.value(i).toString();
        }
        return data;
    }
    else
        return data;
}
















