#include "loadmemorythread.h"

LoadMemoryThread::LoadMemoryThread()
{
    stopped = false;
}

void LoadMemoryThread::run()
{
    while(!stopped)
    {
    //ModelTreeNode::LoadTreeNode();   //加载内存
    QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("机柜已存在该设备"));
    }
}

void LoadMemoryThread::stop()
{
    stopped = true;
}

