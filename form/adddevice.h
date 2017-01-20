 #ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include <QWidget>
#include <QFile>
#include <QPainter>
#include <QDomDocument>
#include <QDesktopWidget>
#include "ui_adddevice.h"
#include "externvalue.h"
#include "udpsocket.h"
#include "sqldb.h"
#include "modelchest.h"
#include "modelscan.h"
#include "modelpei.h"
#include "modelswitch.h"

namespace Ui {
class addDevice;
}

class QStandardItemModel;//这个类为Qt中提供了存储定制数据的通用模型

class addDevice : public QWidget
{
    Q_OBJECT

public:
    explicit addDevice(QWidget *parent = 0);
    ~addDevice();
    void createQss();
    void paintEvent(QPaintEvent *event);
    sqlDb *database;

    enum DataTimeType{Time, Date, DateTime};//定义时间的枚举类型
    QString getDataTime(DataTimeType type);

    void showIndex(int number);

signals:
    void addChestEvent(ModelChest);
    void addIscanEvent(ModelScan);
    void addPeixianjiaEvent(ModelPeixianjia);
    void addSwitchEvent(ModelSwitch);

private slots:
    void on_addBtn_clicked();
    void on_closeBtn_clicked();
    void on_deleteBtn_clicked();

public:
    Ui::addDevice *ui;
    void addChest();
    void addIscan();
    void addPeixianjia();
    void addSwitch();
    udpsocket* udp;
    void scanconfig();



};

#endif // ADDDEVICE_H
