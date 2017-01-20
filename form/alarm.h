#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QDateTime>
#include <QDesktopWidget>
#include <QFile>
#include <QLabel>
#include "sqldb.h"
#include "modelchest.h"
#include "modelscan.h"
#include "modelpei.h"
#include "modeltreenode.h"
#include "modelswitch.h"

namespace Ui {
class alarm;
}

class alarm : public QWidget
{
    Q_OBJECT

public:
    explicit alarm(QWidget *parent = 0);
    ~alarm();
    int count;
    void createQss();
    //数据库
    sqlDb db;

    //绘制链路
    void paintEvent(QPaintEvent *event);


    //机柜
    QVector<QLabel*> leftPicture;
    QVector<QLabel*> rightPicture;
    QVector<QLabel*> devicePicture;
    QVector<QLabel*> chestLevel;
    void loadIcon();
    void loadData();
    //报警配线架
    QVector<QLabel*> singlePeixianjia;
    QVector<QLabel*> doublePeixianjia;

public slots:
    void showAlarm(QVector<QString> value);


private:
    Ui::alarm *ui;
};

#endif // ALARM_H
