#ifndef SQLDB_H
#define SQLDB_H

#include <QtSql>
#include <Windows.h>
#include <mysql.h>
#include <QMessageBox>
#include <QSqlDatabase>

class sqlDb
{
public:
    sqlDb();
    //创建连接
    bool createConnection(QString HostIp, QString userName, int port, QString password);
    //创建数据库
    bool creatDatabase(QString databaseName);
    //搜索是否存在指定数据库
    bool searchDatabase(QString databaseName);
    //创建表
    bool creatTabel(QString databaseName,QString tabel,QVector<QString> list);
    bool creatTabel(QString tabel);
    //搜索是否存在指定表
    bool searchTabel(QString db,QString tabel);
    //增
    bool addData(QString databaseName,QString tabel,QVector<QString> listValue);
    bool insertData(QString str);
    //删
    bool deleteData(QString databaseName,QString tabel,QString where,QString what);
    //改
    bool changeData(QString databaseName,QString tabel,QVector<QString> list,QString where,QString what);
    //查
    bool selectData(QString databaseName, QString tabel, QString where, QString what);
    //查找返回信息
    QVector<QString> selectListData(QString databaseName, QString tabel, QString coloumn, QString where, QString what); //返回数组
    QString selectOneData(QString databaseName, QString tabel, QString coloumn, QString where, QString what);       //返回一个数据的字符串
    QVector<QString> selectAllData(QString databaseName, QString tabel, QString coloumn); //返回一个列的所有数据数组
    //查找单一数据，并返回该信息全部内容
    QVector<QString> selectSingleData(QString databaseName, QString tabel,int coloumnNumber, QString where, QString what);
};

#endif // SQLDB_H
