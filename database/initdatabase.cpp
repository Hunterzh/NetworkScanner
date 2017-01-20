#include "initdatabase.h"

initdatabase::initdatabase()
{
    initDb = new sqlDb;
    initDb->createConnection("127.0.0.1", "root", 3306, "123456");

    if(!initDb->searchDatabase("SwitchTools"))
    {
        initDb->creatDatabase("SwitchTools");
        //创建SWITCHTOOLS数据库表
        initDb->creatTabel(Create_PeixianjiaType());
        initDb->creatTabel(Create_DeviceClassSubType());
        initDb->creatTabel(Create_DeviceItem());
        initDb->creatTabel(Create_DeviceTree());
        initDb->creatTabel(Create_ICON());
        initDb->creatTabel(Create_Chest());
        initDb->creatTabel(Create_Map());
        initDb->creatTabel(Create_MapItem());
        initDb->creatTabel(Create_MapLink());
        initDb->creatTabel(Create_Switch());
        initDb->creatTabel(Create_Peixianjia());
        initDb->creatTabel(Create_PeixianjiaPort());
        initDb->creatTabel(Create_Port());
        initDb->creatTabel(Create_Scan());
        initDb->creatTabel(Create_ChestLink());

        for(int i=0;i<7;i++)
        {
            initDb->insertData(Create_PeixianjiaTypeDefault()[i]);
        }
    }

    if(!initDb->searchDatabase("SwitchTools_Info"))
    {
        initDb->creatDatabase("SwitchTools_Info");
        initDb->creatTabel(Create_OperateLog());
        initDb->creatTabel(Create_User());
        initDb->creatTabel(Create_DbBackup());
        initDb->insertData(Create_DefaultUser());
    }
//        QString str= QString("INSERT INTO `SwitchTools`.`DeviceClassMainType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("电子配线架系统"));
//        QMessageBox::about(NULL,"ERROR",str);

}

/*******************************************************************
                         SWITCHTOOLS数据库
*******************************************************************/
QString initdatabase::Create_PeixianjiaType()
        {
             QString str ="CREATE TABLE `SwitchTools`.`PeixianjiaType`(";

             str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
             str.append("`NAME` VARCHAR(100) NOT NULL,");

             str.append("KEY(`ID`)");
             str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
             return str;
        }

QVector<QString> initdatabase::Create_PeixianjiaTypeDefault()
        {
            QVector<QString> str(7);
            //str[0] = "INSERT INTO `SwitchTools`.`DeviceClassMainType`(`NAME`) VALUES('电子配线架系统');";
            str[0] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("五类配线架"));
            str[1] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("超五类配线架"));
            str[2] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("六类配线架"));
            str[3] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("超六类配线架"));
            str[4] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("多媒体配线架"));
            str[5] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("光纤配线架"));
            str[6] = QString("INSERT INTO `SwitchTools`.`PeixianjiaType`(`NAME`) VALUES('%1');").arg(QString::fromLocal8Bit("其他设备"));
            return str;
        }

QString initdatabase::Create_DeviceClassSubType()
        {
            QString str ="CREATE TABLE `SwitchTools`.`DeviceClassSubType`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`ParentID` INT(4) NOT NULL , ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`Height` INT(4) NOT NULL , ");
            str.append("`PortCount` INT(4) NOT NULL , ");
            //缺图标项

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_DeviceItem()
        {
            QString str ="CREATE TABLE `SwitchTools`.`DeviceItem`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`ParentID` INT(4) NOT NULL , ");
            str.append("`DeviceType` INT(4) NOT NULL , ");
            str.append("`Model` INT(4) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_DeviceTree()
        {
            QString str ="CREATE TABLE `SwitchTools`.`DeviceTree`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`ParentID` INT(4) NULL DEFAULT 0, ");
            str.append("`SubID` INT(4) NULL , ");
            str.append("`ICON` INT(4) NULL , ");
            str.append("`MAP` INT(4) NULL , ");
            str.append("`IsLast` INT(4) NULL DEFAULT 0 , ");
            str.append("`Type` VARCHAR(100) NOT NULL,");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_ICON()
        {
            QString str ="CREATE TABLE `SwitchTools`.`ICON`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            //str.append("`Image` BINARY(200) NOT NULL , ");
            str.append("`ImageName` VARCHAR(100) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_Chest()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Chest`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`ParentID` INT(4) NULL , ");
            str.append("`OrderNumber` INT(4) NULL , ");
            str.append("`DeviceType` VARCHAR(100) NULL , ");
            str.append("`Height` INT(4) NOT NULL , ");
            str.append("`Width` INT(4) NULL , ");
            str.append("`Depth` INT(4) NULL , ");
            str.append("`Model` VARCHAR(100) NULL , ");
            str.append("`Manufactor` VARCHAR(100) NULL , ");
            str.append("`Department` VARCHAR(100) NULL , ");
            str.append("`BuyDate` DATE NULL , ");
            str.append("`Price` FLOAT(8) NULL , ");
            str.append("`administrator` VARCHAR(100) NULL , ");
            str.append("`description` VARCHAR(100) NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_Map()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Map`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            //str.append("`Image` BINARY(200) NOT NULL , ");
            str.append("`ImageName` VARCHAR(100) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_MapItem()
        {
            QString str ="CREATE TABLE `SwitchTools`.`MapItem`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`MapID` INT(4) NOT NULL , ");
            str.append("`DeviceID` INT(4) NOT NULL , ");
            str.append("`x` INT(4) NOT NULL , ");
            str.append("`y` INT(4) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_MapLink()
        {
            return NULL;
        }

QString initdatabase::Create_Switch()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Switch`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`Port` INT(4) NULL , ");
            //str.append("`ParentID` INT(4) NULL , ");
            //str.append("`DeviceType` INT(4) NULL , ");
            str.append("`Model` VARCHAR(100) NULL , ");
            str.append("`Manufactory` VARCHAR(100) NULL , ");
            //str.append("`BuyDate` DATE NULL , ");
            //str.append("`ChestID` INT(4) NOT NULL , ");
            //str.append("`ChestIndex` INT(4) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_Peixianjia()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Peixianjia`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`ScanID` INT(4) NULL , ");
            str.append("`ScanPort` INT(4) NULL , ");
            str.append("`PeixianjiaID` INT(4) NULL , ");
            str.append("`NAME` VARCHAR(100) NOT NULL , ");
            str.append("`DeviceType` VARCHAR(100) NULL , ");
            str.append("`Model` VARCHAR(100) NULL , ");
            str.append("`Manufactory` VARCHAR(100) NULL , ");
            str.append("`Admin` VARCHAR(100) NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_PeixianjiaPort()
        {
            QString str ="CREATE TABLE `SwitchTools`.`PeixianjiaPort`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`SwitchID` INT(4) NOT NULL , ");
            str.append("`SwitchPort` INT(4) NOT NULL , ");
            str.append("`ListPeixianjiaLinkStruct` TEXT(200) NOT NULL , ");
            str.append("`DeviceID` INT(4) NULL , ");
            str.append("`DeviceType` INT(4) NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_Port()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Port`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`ParentID` INT(4) NOT NULL , ");
            str.append("`DeviceType` VARCHAR(100) NOT NULL , ");
            str.append("`IP` VARCHAR(50) NOT NULL , ");
            str.append("`Model` VARCHAR(100) NOT NULL , ");
            str.append("`Manufactor` VARCHAR(100) NOT NULL , ");
            str.append("`ModelType` VARCHAR(100) NOT NULL , ");
            str.append("`BuyDate` DATE NOT NULL , ");
            str.append("`Price` FLOAT(8) NOT NULL , ");
            str.append("`MAC` VARCHAR(100) NOT NULL , ");
            str.append("`administrator` VARCHAR(100) NOT NULL , ");
            str.append("`Department` VARCHAR(100) NOT NULL , ");
            str.append("`description` VARCHAR(100) NOT NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
        }

QString initdatabase::Create_Scan()
        {
            QString str ="CREATE TABLE `SwitchTools`.`Scan`(";

            str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
            str.append("`NAME` VARCHAR(100) NOT NULL,");
            str.append("`ParentID` INT(4) NULL , ");
            str.append("`IP` VARCHAR(50) NOT NULL , ");
            str.append("`Port` INT(4) NOT NULL , ");
            str.append("`ScanID` INT(4) NULL , ");

            str.append("`MAC` VARCHAR(100) NULL , ");
            str.append("`Mask` VARCHAR(100) NULL , ");
            str.append("`Gate` VARCHAR(100) NOT NULL , ");
            str.append("`SubID` INT(4) NULL , ");
            str.append("`LinkPortCount` INT(4) NULL , ");
            str.append("`ChestID` INT(4) NULL , ");
            str.append("`ChestIndex` INT(4) NULL , ");

            str.append("KEY(`ID`)");
            str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
            return str;
}

QString initdatabase::Create_ChestLink()
{
    QString str ="CREATE TABLE `SwitchTools`.`ChestLink`(";

    str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
    str.append("`ChestID` INT(4) NULL,");
    str.append("`LinkNAME` VARCHAR(100) NULL, ");
    str.append("`Position` INT(4) NULL, ");
    str.append("`Type` VARCHAR(100) NULL , ");

    str.append("KEY(`ID`)");
    str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
    return str;
}


/*******************************************************************
                         SWITCHTOOLS_INFO数据库
*******************************************************************/
QString initdatabase::Create_OperateLog()
    {
        QString str ="CREATE TABLE `SwitchTools_Info`.`OperateLog`(";

        str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
        str.append("`UserID` INT(4) NOT NULL , ");
        str.append("`Logtype` INT(4) NOT NULL , ");
        str.append("`LogInfo` VARCHAR(500) NOT NULL , ");
        str.append("`DateTime` DATETIME NOT NULL , ");

        str.append("KEY(`ID`)");
        str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
        return str;
    }
QString initdatabase::Create_User()
    {
        QString str ="CREATE TABLE `SwitchTools_Info`.`User`(";

        str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
        str.append("`UserName` VARCHAR(50) NOT NULL , ");
        str.append("`Password` VARCHAR(50) NOT NULL , ");
        str.append("`Describe` VARCHAR(50) NULL , ");
        str.append("`Department` VARCHAR(50) NULL , ");
        str.append("`Company` VARCHAR(50) NULL , ");
        str.append("`Email` VARCHAR(50) NULL , ");
        str.append("`Mobile` VARCHAR(50) NULL , ");
        str.append("`CreateDate` DATETIME NULL , ");
        str.append("`ExpireDate` DATETIME NULL , ");
        str.append("`UpdateDate` DATETIME NULL , ");
        str.append("`Status` INT(4) NULL , ");
        str.append("`UserGroup` INT(4) NULL , ");
        str.append("`Auth` INT(4) NULL , ");

        str.append("KEY(`ID`)");
        str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
        return str;
    }

QString initdatabase::Create_DefaultUser()
    {
        return "INSERT INTO `SwitchTools_Info`.`User`(`UserName`, `Password`, `Describe`, `ExpireDate`, `Auth`) VALUES('admin', 'admin', 'Adminstrator', '2200-1-1', '65535');";
    }

QString initdatabase::Create_DbBackup()
    {
        QString str ="CREATE TABLE `SwitchTools_Info`.`DbBackup`(";

        str.append("`ID` INT(4) NOT NULL AUTO_INCREMENT, ");
        str.append("`DateTime` DATETIME NOT NULL , ");
        str.append("`Operater` VARCHAR(100) NOT NULL , ");
        str.append("`Path` VARCHAR(256) NOT NULL , ");

        str.append("KEY(`ID`)");
        str.append(") CHARSET=utf8 COLLATE=utf8_general_ci;");
        return str;
    }
