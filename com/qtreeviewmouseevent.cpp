#include "qtreeviewmouseevent.h"

QTreeViewMouseEvent::QTreeViewMouseEvent(QWidget *parent) :
    QTreeView(parent)
{
    mouse_press = false;
}

QTreeViewMouseEvent::~QTreeViewMouseEvent()
{

}

void QTreeViewMouseEvent::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mouse_press = true;

    }
    if(event->button()==Qt::RightButton)
    {
        emit rightClick();
    }
    // 记得调用父类的函数（保持原有的按键行为)
    QTreeView::mousePressEvent(event);
}

void QTreeViewMouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)//若鼠标左键被按下
    {
        emit leftClick();
    }
}

