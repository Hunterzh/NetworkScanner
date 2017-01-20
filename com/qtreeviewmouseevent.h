#ifndef QTREEVIEWMOUSEEVENT_H
#define QTREEVIEWMOUSEEVENT_H
#include <QTreeView>
#include <QMouseEvent>
#include <QMessageBox>
#include <QObject>

class QTreeViewMouseEvent : public QTreeView
{
        Q_OBJECT

public:
    explicit QTreeViewMouseEvent(QWidget *parent = 0);
    ~QTreeViewMouseEvent();

signals:
    void leftClick(void);
    void rightClick(void);

public:
    bool mouse_press; //鼠标按下
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );

};

#endif // QTREEVIEWMOUSEEVENT_H
