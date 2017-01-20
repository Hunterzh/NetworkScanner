#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPoint>
#include <QMoveEvent>
#include <QPixmap>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QDesktopWidget>
#include "user.h"
#include "tcpclient.h"
#include "udpsocket.h"
#include "initdatabase.h"
#include "loadmemorythread.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    user *userPage;
    void accept();
    initdatabase *database;

signals:
    void enterEvent();

private slots:
    void loginControl();
    void on_closeBtn_clicked();

private:
    Ui::login *ui;

protected:
    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *); //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *event); //鼠标移动事件
    void keyPressEvent(QKeyEvent* event); //按键事件
    void createQss();
};

#endif // LOGIN_H
