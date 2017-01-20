#ifndef DEVICE_H
#define DEVICE_H

#define ROLE_MARK Qt::UserRole + 1

#define MARK_CHEST 1 //机柜标记
#define MARK_OTHER 2 //其他标记

#include <QWidget>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QIcon>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QDesktopWidget>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QtGui>
#include <QScrollArea>
#include <QTimer>
#include "adddevice.h"
#include "ui_device.h"
#include "externvalue.h"
#include "sqldb.h"
#include "modelchest.h"
#include "modelscan.h"
#include "modelpei.h"
#include "modeltreenode.h"
#include "modelswitch.h"


namespace Ui {
class device;
}


class device : public QWidget//
{
    Q_OBJECT

public:
    explicit device(QWidget *parent = 0);
    ~device();
    QStandardItemModel* model;
    QTimer* timer;

    //QSS
    void createQss();
    //菜单
    void menu_Init();
    QMenu* m_projectMenu;
    QMenu* m_itemMenu;
    QMenu* m_noneMenu;
    QAction* chest;
    QAction* iscan;
    QAction* switchboard;
    QAction* allotshelf;
    //树
    QVector<QStandardItem*> tree;
    void creatTree();

    //添加窗口
    addDevice* getDevice;
    //数据库
    sqlDb db;
    //机柜
    QVector<QLabel*> leftPicture;
    QVector<QLabel*> rightPicture;
    QVector<QLabel*> devicePicture;
    QVector<QLabel*> chestLevel;
    void loadChest();
    void setChestLink(QString NAME, QString Position);
    void updateChestLinkFromDb();

    //端口配置
    QVector<QLabel*> cakou;
    QVector<QLabel*> cakouInfo;
    QLabel* scanLabel;
    QLabel* scanNameLabel;
    void CakouIconInit();
    void setScanPortLink(QString peixianjia, QString scanPort);
    void updateCakouIconFromDb(ModelScan scan);
    void loadCakouIcon(ModelScan scan);

    //链路构建
    QVector<QLabel*> peixianjiaLabel; //表上配线架
    QVector<QLabel*> peixianjiaTextLabel; //表上配线架
    QVector<QLabel*> tableIconLabel; //表中图标（交换机、端口、配线架）
    QVector<QLabel*> tableTextLabel; //表中文字备注
    void loadPeixianjiaIcon();
    void drawTable();
    void setPeixianjiaLink(QString PeixianjiaPort, QString PeixianjiaIconNumber);
    void loadWorkSheetconfig();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

//端口配置拖拽事件
private:
    Ui::device *ui;
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    //virtual void QTreeView::mousePressEvent(QMouseEvent * event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QPoint m_dragPosition; // 拖放起点
    QString m_dragName; // 被拖放的名称

private slots:
    //设备添加槽函数
    void addChestTree(ModelChest);
    void addIscanTree(ModelScan);
    void addPeixianjiaTree(ModelPeixianjia);
    void addSwitchTree(ModelSwitch);
    //菜单槽函数
    void on_deviceTree_customContextMenuRequested(const QPoint &pos);
    //树点击拖拽槽函数
    void on_deviceTree_pressed(const QModelIndex &index);
    //树单机事件，左击
    void treeMouseLeftEvent();
    //树单机事件，右击
    void treeMouseRightEvent(QModelIndex index);
    //信号比较
    void both(QModelIndex index);
    //定时器事件
    void TimerElapsed();

    void on_selectBtn_clicked();

signals:
    void treeLeftPressed();  //左击信号
    void treeRightPressed(QModelIndex index);  //右击信号
};

#endif // DEVICE_H
