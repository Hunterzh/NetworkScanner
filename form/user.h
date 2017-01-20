#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include <QFile>
#include <QPainter>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QMoveEvent>
#include <QPalette>
#include <QDesktopWidget>
#include "home.h"
#include "device.h"
#include "setting.h"
#include "alarm.h"
#include "udpsocket.h"

namespace Ui {
class user;
}

class user : public QMainWindow
{
    Q_OBJECT

signals:
    void signalToHome(int);

public:
    explicit user(QWidget *parent = 0);
    ~user();
    home *homePage;
    device *devicePage;
    setting *setPage;
    alarm *alarmPage;
    udpsocket* udp;
    QRect DeskTopRect;
    bool windowStatus;

    void windowBtn();
    void uiControl();

private slots:
    void on_userCloseBtn_clicked();
    //void slotFromLogin(int);

    void on_homeBtn_clicked();

    void on_deviceBtn_clicked();

    void on_settingBtn_clicked();

    void on_alarmBtn_clicked();


    void on_userMizeBtn_clicked();

    void on_userMiniBtn_clicked();

private:
    Ui::user *ui;
    void createQss();
    void paintEvent(QPaintEvent *event);

protected:
    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *event); //鼠标移动事件
    void resizeEvent ( QResizeEvent * event );

};

#endif // USER_H
