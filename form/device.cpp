#include "device.h"
#include "ui_device.h"


device::device(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::device)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(500);  //3s周期启动
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerElapsed()));

    //窗体大小
    QDesktopWidget * deskTop = QApplication::desktop();
    int number= deskTop->screenNumber (this); // 主屏号，参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(number);
    //this->setFixedSize(rect.width()*0.7,rect.height()*0.8-170);  //固定窗体大小
    this->setBaseSize(rect.width()*0.7,rect.height()*0.8-170);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->deviceTree->setGeometry(QRect(this->width()*0, this->height()*0, this->width()*0.2, this->height()*1));
    ui->deviceTabWidget->setGeometry(QRect(this->width()*0.2, this->height()*0, this->width()*0.8, this->height()*1));

    ui->setLinkArea->setMinimumSize (1300,970);
    ui->scrollAreaWidgetContents->setMinimumSize (1500,2700);
    ui->setLinkArea->setStyleSheet(QString::fromUtf8("background-color:transparent;"));

    ui->chestArea->setMinimumSize (1300,970);
    ui->scrollAreaWidgetContents_2->setMinimumSize (1500,1500);
    ui->chestArea->setStyleSheet(QString::fromUtf8("background-color:transparent;"));

    ui->portArea->setMinimumSize (1300,970);
    ui->scrollAreaWidgetContents_3->setMinimumSize (1500,1500);
    ui->portArea->setStyleSheet(QString::fromUtf8("background-color:transparent;"));

    db.createConnection("127.0.0.1","root",3306,"123456");
    getDevice = new addDevice();

    model = new QStandardItemModel(ui->deviceTree);

    //model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Device Tree"));

    ui->deviceTree->setModel(model);
    ModelTreeNode::LoadTreeNode();   //加载内存

    menu_Init();
    createQss();
    creatTree();
    CakouIconInit();
    loadChest();
    loadPeixianjiaIcon();

    ui->deviceTree->expandAll(); //展开所有节点

    setAcceptDrops(true);//支持拖放
    //ui->scrollAreaWidgetContents->installEventFilter(this);//时间过滤器调用指针
    ui->setLinkArea->installEventFilter(this);//事件过滤器调用指针
    ui->deviceTree->installEventFilter(this);

    //添加设备菜单
    connect(chest,SIGNAL(triggered()),getDevice,SLOT(show()));
    connect(iscan,SIGNAL(triggered()),getDevice,SLOT(show()));
    connect(switchboard,SIGNAL(triggered()),getDevice,SLOT(show()));
    connect(allotshelf,SIGNAL(triggered()),getDevice,SLOT(show()));

    connect(getDevice,SIGNAL(addChestEvent(ModelChest)),this,SLOT(addChestTree(ModelChest)));
    connect(getDevice,SIGNAL(addIscanEvent(ModelScan)),this,SLOT(addIscanTree(ModelScan)));
    connect(getDevice,SIGNAL(addPeixianjiaEvent(ModelPeixianjia)),this,SLOT(addPeixianjiaTree(ModelPeixianjia)));
    connect(getDevice,SIGNAL(addSwitchEvent(ModelSwitch)),this,SLOT(addSwitchTree(ModelSwitch)));

    //QTreeView鼠标左右键信号
    connect(ui->deviceTree,SIGNAL(leftClick()),this,SLOT(treeMouseLeftEvent()));
    connect(this,SIGNAL(treeRightPressed(QModelIndex)),this,SLOT(treeMouseRightEvent(QModelIndex)));  //右击
    //槽口图标信号槽
    connect(this,SIGNAL(loadCakouIconSignal(ModelScan)),this,SLOT(loadCakouIcon(ModelScan)));
}

device::~device()
{
    delete ui;
    delete getDevice;
    delete model;
}

void device::createQss()  //创建qss
{
    QFile qssFile(":/qss/device.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
     }
}

void device::menu_Init()
{
    m_projectMenu = new QMenu(this);
    m_itemMenu = new QMenu(this);
    m_noneMenu = new QMenu(this);

    QAction* ac = nullptr;

    //点击空白菜单
    chest = new QAction(QString::fromUtf8("addchest"),this);
    m_noneMenu->addAction(chest);

    ac = new QAction(QString::fromUtf8("delete"),this);
    m_noneMenu->addAction(ac);


    //文件夹
    iscan = new QAction(QString::fromUtf8("addIscan"),this);
    m_projectMenu->addAction(iscan);

    m_projectMenu->addSeparator();

    switchboard = new QAction(QString::fromUtf8("addSwitch"),this);
    m_projectMenu->addAction(switchboard);

    m_projectMenu->addSeparator();

    allotshelf = new QAction(QString::fromUtf8("addAllotShelf"),this);
    m_projectMenu->addAction(allotshelf);


    //文件
    ac = new QAction(QString::fromUtf8("AA"),this);
    m_itemMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("BB"),this);
    m_itemMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("CC"),this);
    m_itemMenu->addAction(ac);

    QMenu* itemChildMenu = new QMenu(m_itemMenu);
    itemChildMenu->setTitle(QString::fromUtf8("AddDevice"));
    ac = new QAction(QString::fromUtf8("ee"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("ff"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("gg"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("hh"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromUtf8("ll"),this);
    itemChildMenu->addAction(ac);
    m_itemMenu->addAction(itemChildMenu->menuAction());
}


void device::on_deviceTree_customContextMenuRequested(const QPoint &pos)
{

    QModelIndex index = ui->deviceTree->indexAt(pos);
    emit treeRightPressed(index);  //右击信号

    externvalue::parentID = db.selectOneData("SwitchTools","DeviceTree","ID","NAME",index.data().toString()).toInt();  //获取当前机柜ID

    //ui->infoLabel->setText(QStringLiteral("当前选中：%1\nrow:%2,column:%3\n").arg(index.data().toString()).arg(index.row()).arg(index.column()));
    //ui->infoLabel_2->setText(QStringLiteral("父级：%1\n").arg(index.parent().data().toString()));
}


void device::creatTree()
{
    //QModelIndex currentIndex = ui->deviceTree->currentIndex();

    tree.resize(ModelTreeNode::m_ListModelTreeNode.count());
    for(int i=0;i<ModelTreeNode::m_ListModelTreeNode.count();i++)
    {
        if(ModelTreeNode::m_ListModelTreeNode[i].ParentID()==0)
        {
            tree[i] = new QStandardItem(QIcon(":/image/treeicon/jigui.png"),ModelTreeNode::m_ListModelTreeNode[i].NAME());
            tree[i]->setData(MARK_CHEST,ROLE_MARK);
            model->appendRow(tree[i]);
        }
        else
        {
            for(int j=0;j<ModelTreeNode::m_ListModelTreeNode.count();j++)
            {
                if(ModelTreeNode::m_ListModelTreeNode[i].ParentID() == ModelTreeNode::m_ListModelTreeNode[j].ID())
                {
                    if(ModelTreeNode::m_ListModelTreeNode[i].Type()=="scan")
                    tree[i] = new QStandardItem(QIcon(":/image/treeicon/scan.png"),ModelTreeNode::m_ListModelTreeNode[i].NAME());
                    if(ModelTreeNode::m_ListModelTreeNode[i].Type()=="peixianjia")
                    tree[i] = new QStandardItem(QIcon(":/image/treeicon/peixianjia.png"),ModelTreeNode::m_ListModelTreeNode[i].NAME());
                    if(ModelTreeNode::m_ListModelTreeNode[i].Type()=="switch")
                    tree[i] = new QStandardItem(QIcon(":/image/treeicon/switch.png"),ModelTreeNode::m_ListModelTreeNode[i].NAME());
                    tree[i]->setData(MARK_OTHER,ROLE_MARK);
                    tree[j]->appendRow(tree[i]);
                }
            }
        }

    }
    //ui->deviceTree->expandAll(); //展开所有节点
}


void device::loadChest()
{
    int uCount = 35;
    int left_x=ui->deviceTabWidget->width()/2-144; //左侧首坐标  42*24分辨率
    int left_y=ui->deviceTabWidget->y()+50+76;
    int right_x=ui->deviceTabWidget->width()/2-144+285-43; //右侧首坐标  43*24分辨率
    int right_y=ui->deviceTabWidget->y()+50+76;

    //柜头
    QLabel *chestTop = new QLabel(ui->scrollAreaWidgetContents_2);
    chestTop->setGeometry(QRect(left_x, left_y-76, 285, 76));
    chestTop->setPixmap(QPixmap(QString::fromUtf8(":/image/jg/top.png")));
    //柜尾
    QLabel *chestBottom = new QLabel(ui->scrollAreaWidgetContents_2);
    chestBottom->setGeometry(QRect(left_x, left_y+24*uCount, 285, 68));
    chestBottom->setPixmap(QPixmap(QString::fromUtf8(":/image/jg/bottom.png")));

    leftPicture.resize(uCount);
    rightPicture.resize(uCount);
    devicePicture.resize(uCount);
    chestLevel.resize(uCount);

    for(int i=0;i<uCount;i++)
    {
        //左
        leftPicture[i] = new QLabel(ui->scrollAreaWidgetContents_2);
        leftPicture[i]->setGeometry(QRect(left_x,left_y+24*i,42,24));
        QPixmap left=QPixmap(":/image/jg/left.gif");
        leftPicture[i]->setPixmap(left);

        //右
        rightPicture[i] = new QLabel(ui->scrollAreaWidgetContents_2);
        rightPicture[i]->setGeometry(QRect(right_x,right_y+24*i,43,24));
        QPixmap right=QPixmap(":/image/jg/right.gif");
        rightPicture[i]->setPixmap(right);

        //中
        devicePicture[i] = new QLabel(ui->scrollAreaWidgetContents_2);
        devicePicture[i]->setGeometry(QRect(left_x+42,left_y+24*i,200,24));
        devicePicture[i]->setObjectName(QString("%1").arg(i+1));//设置图标标号名称1~uCount

        //层
        chestLevel[i] = new QLabel(ui->scrollAreaWidgetContents_2);
        chestLevel[i]->setGeometry(QRect(left_x+10,left_y+1+24*i,24,24));
        chestLevel[i]->setText(QString("%1").arg(i+1));
        //设置字号
        QFont ft( "Microsoft YaHei",6,75);    //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        chestLevel[i]->setFont(ft);
        //设置颜色
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::black);
        chestLevel[i]->setPalette(pa);
    }
    updateChestLinkFromDb();
}

void device::setChestLink(QString NAME, QString Position)
{
    int posi = Position.toInt();
    //是否存在该设备
    bool status_Peixianjia = db.selectData("SwitchTools","Peixianjia","NAME",NAME);
    bool status_Scan = db.selectData("SwitchTools","Scan","NAME",NAME);
    bool status_Switch = db.selectData("SwitchTools","Switch","NAME",NAME);

    //该设备是否已存在机柜中
    bool status_Chest = db.selectData("SwitchTools","ChestLink","LinkNAME",NAME);

    if(status_Peixianjia&&!status_Chest)
    {
        db.insertData(QString("INSERT INTO `SwitchTools`.`ChestLink`(`LinkNAME`,`Position`,`Type`) VALUES('%1','%2','%3');").arg(NAME).arg(posi).arg(QString::fromLocal8Bit("电子配线架")));
        updateChestLinkFromDb();
    }

    if(status_Scan&&!status_Chest)
    {
        db.insertData(QString("INSERT INTO `SwitchTools`.`ChestLink`(`LinkNAME`,`Position`,`Type`) VALUES('%1','%2','%3');").arg(NAME).arg(posi).arg(QString::fromLocal8Bit("扫描仪")));
        updateChestLinkFromDb();
    }

    if(status_Switch&&!status_Chest)
    {
        db.insertData(QString("INSERT INTO `SwitchTools`.`ChestLink`(`LinkNAME`,`Position`,`Type`) VALUES('%1','%2','%3');").arg(NAME).arg(posi).arg(QString::fromLocal8Bit("交换机")));
        updateChestLinkFromDb();
    }

    if(status_Chest)
       QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("机柜已存在该设备"));

}

void device::updateChestLinkFromDb()
{
    //更新图标
    QVector<QString> positionList = db.selectAllData("SwitchTools","ChestLink","Position");  //位置列表
    for(int i=0; i<positionList.count(); i++)
    {
        int posi = positionList[i].toInt();
        QString Type = db.selectOneData("SwitchTools","ChestLink","Type","Position",positionList[i]);
        if(Type==QString::fromLocal8Bit("电子配线架"))
        devicePicture[posi]->setPixmap(QPixmap(":/image/jg/peixianjia.png"));
        if(Type==QString::fromLocal8Bit("交换机"))
        devicePicture[posi]->setPixmap(QPixmap(":/image/jg/switch.gif"));
        if(Type==QString::fromLocal8Bit("扫描仪"))
        devicePicture[posi]->setPixmap(QPixmap(":/image/jg/scan.png"));
    }
}

void device::setScanPortLink(QString treeDeviceText, QString tabLabelObjectName)
{
    int port = tabLabelObjectName.toInt();
    bool status_peixianjia = db.selectData("SwitchTools","Peixianjia","NAME",treeDeviceText);
    bool status_scan = db.selectData("SwitchTools","Scan","NAME",treeDeviceText);
    //若拖的是扫描仪
    if(status_scan)
    {
        if(port==25||port==26)
        {
            scanLabel->setPixmap(QPixmap(":/image/scanBig.png"));
            scanNameLabel->setText(treeDeviceText);
            for(int i=0;i<ModelScan::m_ListModelScan.count();i++)
            {
                if(ModelScan::m_ListModelScan[i].NAME()==treeDeviceText)
                  {
                   loadCakouIcon(ModelScan::m_ListModelScan[i]);
                  }
            }
        }
    }
    //若拖的是配线架
    else if(status_peixianjia)
    {
        int scanID;

        if(port>0&&port<25)
        {
            for(int i=0;i<ModelScan::m_ListModelScan.count();i++)
            {
                if(ModelScan::m_ListModelScan[i].NAME()==scanNameLabel->text())
                {
                    scanID = ModelScan::m_ListModelScan[i].ID();
                    db.insertData(QString("UPDATE `SwitchTools`.`Peixianjia` SET `ScanPort`='%1'  WHERE `NAME` = '%2';").arg(port).arg(treeDeviceText));
                    db.insertData(QString("UPDATE `SwitchTools`.`Peixianjia` SET `ScanID`='%1'  WHERE `NAME` = '%2';").arg(scanID).arg(treeDeviceText));
                    updateCakouIconFromDb(ModelScan::m_ListModelScan[i]);
                }
            }
        }
         else
            QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("请拖放至配线架端口图标"));
    }
    else
        QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("请拖拽配线架或扫描仪"));

}

void device::mouseMoveEvent(QMouseEvent *event)
{
    //QMessageBox::about(NULL,"error","mouseMoveEvent");
    // 只允许用左键拖动
    if (!(event->buttons() & Qt::LeftButton))
        return;

    // 移动一定距离后，才算是开始拖动
    if ((event->pos() - m_dragPosition).manhattanLength()
        < QApplication::startDragDistance())
        return;

    // 找到拖动的项
    if(m_dragName=="") return;
      QString text = m_dragName;

    // 创建数据
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText( text );
    drag->setMimeData(mimeData);

    // 设置拖动时的图像显示
    QPixmap drag_img(120, 18);
    QPainter painter(&drag_img);
    painter.setPen(Qt::white);
    //painter.fillRect(QRectF(0,0, 120,18),Qt::Dense7Pattern);
    painter.drawText(QRectF(0,0, 120,18),text,QTextOption(Qt::AlignVCenter));
    drag->setPixmap(drag_img);


    // 启动拖放start a drag
    Qt::DropAction result = drag->exec(Qt::CopyAction | Qt::MoveAction);

    // 检查操作有没有成功/有没有被取消
    if(Qt::IgnoreAction != result)
    {

    }
    else
    {
        // 按住ctrl键: Qt::CopyAction
        // 没按： Qt::MoveAction
    }
}

void device::mousePressEvent(QMouseEvent *event)
{
    //QMessageBox::about(NULL,"Tip","hello");
    m_dragPosition = event->pos(); //记下起点
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;
    m_dragName = child->objectName();


    // 记得调用父类的函数（保持原有的按键行为)
    //QTreeView::mousePressEvent(event);
}


void device::on_deviceTree_pressed(const QModelIndex &index)
{
    m_dragName = index.data().toString();

    emit treeLeftPressed();
}

void device::treeMouseLeftEvent()
{
    //QMessageBox::about(NULL,"Tip","hello");

    // 创建数据
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText( m_dragName );
    drag->setMimeData(mimeData);
    // 设置拖动时的图像显示
    QPixmap drag_img(120, 18);
    QPainter painter(&drag_img);
    QPen pen(QColor(255,255,255));
    painter.setPen(pen);
    painter.drawText(QRectF(0,0, 120,18),m_dragName,QTextOption(Qt::AlignVCenter));
    drag->setPixmap(drag_img);

    Qt::DropAction result = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void device::treeMouseRightEvent(QModelIndex index)
{
    QVariant var = index.data(ROLE_MARK);
    if(var.isValid())
    {
        if(MARK_CHEST == var.toInt())
            m_projectMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
        else if(MARK_OTHER == var.toInt())
            m_itemMenu->exec(QCursor::pos());
    }
    else
        m_noneMenu->exec(QCursor::pos());
}

void device::both(QModelIndex index)
{

}

void device::TimerElapsed()
{
    ModelTreeNode::LoadTreeNode();   //加载内存
    for(int i=0;i<ModelScan::m_ListModelScan.count();i++)
    {
        if(ModelScan::m_ListModelScan[i].NAME()==scanNameLabel->text())
          {
           loadCakouIcon(ModelScan::m_ListModelScan[i]);
          }
    }
}

void device::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        event->acceptProposedAction(); //允许接收释放
    }
}

//拖放释放
void device::dropEvent(QDropEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));

    if(child->isVisible())
    {
        if (event->mimeData()->hasFormat("text/plain"))
        {
            QString text  = event->mimeData()->text();
            event->acceptProposedAction();
            if(ui->deviceTabWidget->currentIndex()==1)
                setScanPortLink(text, child->objectName());//设置扫描仪端口连接
            if(ui->deviceTabWidget->currentIndex()==0)
                setChestLink(text, child->objectName());//设置机柜连接
            if(ui->deviceTabWidget->currentIndex()==2)
                setPeixianjiaLink(text, child->objectName());//设置配线架链路
        }
        else
            event->ignore();
    }
    else
    {
        child->close();
    }

}

void device::loadWorkSheetconfig()
{


}

void device::drawTable()
{
    int x = ui->scrollAreaWidgetContents->x();
    int y = ui->scrollAreaWidgetContents->y()+120;
    int width = 1500;
    int height = ui->scrollAreaWidgetContents->height();

    QPainter line;
    line.begin(ui->setLinkArea);
    QColor blue(255,255,255);
    QPen pen(blue);
    pen.setWidth(1);
    line.setPen(pen);
    line.drawLine(x+20,y+20,x+20,y+2420); //竖first
    line.drawLine(x+120,y+20,x+120,y+2420); //竖1
    line.drawLine(x+240,y+20,x+240,y+2420); //竖2
    line.drawLine(x+240+(width-260)/2,y+20,x+240+(width-260)/2,y+2420); //竖3
    line.drawLine(width-40,y+20,width-40,y+2420); //竖last
    line.drawLine(x+20,y+20,width-40,y+20); //横first
    line.drawLine(x+20,y+2420,width-40,y+2420); //横last
    for(int i=0;i<23;i++)
    {
        line.drawLine(x+120,y+120+100*i,width-40,y+120+100*i); //横1~24
    }
    line.end();
}

void device::setPeixianjiaLink(QString PeixianjiaPort, QString PeixianjiaIconNumber)
{
    int port = PeixianjiaPort.toInt();
    int PositionNumber = PeixianjiaIconNumber.toInt();
    int greenPort_x = tableIconLabel[PositionNumber]->x()+47+(port-1)*17;
    int greenPort_y = tableIconLabel[PositionNumber]->y();

    /***************交换机*****************/
    if(PeixianjiaIconNumber == "switch")
    {
        QString switchName = PeixianjiaPort;

        for(int i=0;i<ModelSwitch::m_ListModelSwitch.count();i++)
        {
            if(ModelSwitch::m_ListModelSwitch[i].NAME() == switchName)
            {
                tableIconLabel[24]->setGeometry(QRect(ui->scrollAreaWidgetContents->x()+20+26,ui->scrollAreaWidgetContents->y()+120+250,48,400));
                tableIconLabel[24]->setPixmap(QPixmap(":/image/peixianjia/switch1.gif"));
                //交换机名字
                tableTextLabel[24]->setGeometry(QRect(ui->scrollAreaWidgetContents->x()+20,ui->scrollAreaWidgetContents->y()+120+650,100,50));
                tableTextLabel[24]->setFont(QFont( "Verdana",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
                tableTextLabel[24]->setAlignment(Qt::AlignCenter); //居中
                tableTextLabel[24]->setText(switchName);

                for(int i=0;i<24;i++)
                {
                    //端口图标
                    tableIconLabel[i]->setPixmap(QPixmap(":/image/peixianjia/lanport.png"));
                    //端口号
                    tableTextLabel[i]->setText(QString::fromLocal8Bit("端口%1").arg(i+1));
                }
            }
        }
    }

    /***************显示表上配线架*****************/
    if(PeixianjiaIconNumber == "peixianjia")
    {
        QString peixianjiaName = PeixianjiaPort;

        for(int i=0;i<ModelPeixianjia::m_ListPeixianjia.count();i++)
        {
            if(ModelPeixianjia::m_ListPeixianjia[i].NAME() == peixianjiaName)
            {
                //配线架名称
                peixianjiaLabel[26]->setGeometry(QRect(ui->scrollAreaWidgetContents->x()+10,50,1400,135));
                peixianjiaLabel[26]->setText(peixianjiaName);
                peixianjiaLabel[26]->setFont(QFont( "Verdana",10,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）

                //表上两端图标
                peixianjiaLabel[24]->setPixmap(QPixmap(":/image/peixianjia/left.gif"));
                peixianjiaLabel[25]->setPixmap(QPixmap(":/image/peixianjia/right.gif"));
                //显示表上配线架
                for(int i=0;i<24;i++)
                {
                        //配线架图标
                        peixianjiaLabel[i]->setPixmap(QPixmap(":/image/peixianjia/port24_black.gif"));
                        //表上端口标号
                        peixianjiaTextLabel[i]->setText(QString("%1").arg(i+1));
                }
            }
        }
    }
    /***************显示表下配线架*****************/
    else
    {
        if(PositionNumber==0||port>24)
           return;

        //配线架
        tableIconLabel[PositionNumber]->setPixmap(QPixmap(":/image/peixianjia/24kou.png"));
        //绿色端口
        tableIconLabel[PositionNumber+48]->setGeometry(QRect(greenPort_x,greenPort_y,17,48));
        tableIconLabel[PositionNumber+48]->setPixmap(QPixmap(":/image/peixianjia/port24_green.gif"));
        //备注文字
        tableTextLabel[PositionNumber]->setText(QString::fromLocal8Bit("配线架1，端口%1").arg(port));

        /***********存入数据库***********/
        //配线架连接结构体（目前只有单配）
        ModelPeixianjiaLink* peixianjiaLink = new ModelPeixianjiaLink;
        QString peixianjiaLinkString;
        for(int i=0;i<ModelPeixianjia::m_ListPeixianjia.count();i++)
        {
            if(ModelPeixianjia::m_ListPeixianjia[i].NAME() == PeixianjiaIconNumber)
            {
                peixianjiaLink->m_Link.dwIndex = 0;
                peixianjiaLink->m_Link.dwScanID = ModelPeixianjia::m_ListPeixianjia[i].ScanID();
                peixianjiaLink->m_Link.dwScanPort = ModelPeixianjia::m_ListPeixianjia[i].ScanPort();
                peixianjiaLink->m_Link.dwPeixianID = ModelPeixianjia::m_ListPeixianjia[i].ID();
                peixianjiaLink->m_Link.dwPeixianPort = PeixianjiaPort.toInt();
                peixianjiaLinkString = QString("%1,%2,%3,%4,%5")\
                        .arg(peixianjiaLink->m_Link.dwIndex)\
                        .arg(peixianjiaLink->m_Link.dwScanID)\
                        .arg(peixianjiaLink->m_Link.dwScanPort)\
                        .arg(peixianjiaLink->m_Link.dwPeixianID)\
                        .arg(peixianjiaLink->m_Link.dwPeixianPort);
            }
        }
        //交换机ID
        int switchID;
        for(int i=0;i<ModelSwitch::m_ListModelSwitch.count();i++)
        {
            if(ModelSwitch::m_ListModelSwitch[i].NAME() == tableTextLabel[24]->text())
                switchID = ModelSwitch::m_ListModelSwitch[i].ID();
        }
        //交换机端口
        int switchPort;
        if(port%2==0)  //偶数
            switchPort = port/2;
        else
            switchPort = (port+1)/2;
        //一起存入数据库
        bool status = db.insertData(QString("INSERT INTO `SwitchTools`.`PeixianjiaPort`(`SwitchID`,`SwitchPort`,`ListPeixianjiaLinkStruct`) VALUES('%1','%2','%3');").arg(switchID).arg(switchPort).arg(peixianjiaLinkString));
        if(status)
            QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("成功"));
        else
            QMessageBox::about(NULL,"Tip",QString::fromLocal8Bit("失败"));
    }


}



bool device::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->setLinkArea)
    {
        if(e->type() == QEvent::Paint)
        {
            drawTable();
            return true;
        }
    }

    if(obj == ui->deviceTree)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMessageBox::about(NULL,"Tip","MouseButtonPress");

            QMouseEvent * event = (QMouseEvent *)e;
            //QMouseEvent *event=static_cast<QMouseEvent *>e;
            if(event->button()&&Qt::LeftButton)
               QMessageBox::about(NULL,"Tip","LeftClick");
            if(event->button()&&Qt::RightButton)
               QMessageBox::about(NULL,"Tip","RightClick");
            return true;
        }
    }

    return QWidget::eventFilter(obj,e);
}

void device::CakouIconInit()
{
    int x = ui->deviceTabWidget->x()-250;
    int y = ui->deviceTabWidget->y()+200;
    int x_distance = 200;
    int y_distance = 200;
    int portNumber = 1;

    //扫描仪框
    ui->scanFrameLabel->setGeometry(QRect(x+0,y-170,1020,150));
    ui->scanFrameLabel->setObjectName("25");
    //扫描仪
    scanLabel = new QLabel(ui->scrollAreaWidgetContents_3);
    //scanLabel->setText(QString::fromLocal8Bit("请拖拽扫描仪至此"));
    scanLabel->setGeometry(QRect(x+245,y-140,530,80));
    //scanLabel->setPixmap(QPixmap(":/image/jg/scan.png"));
    scanLabel->setObjectName("26");

    //扫描仪信息
    scanNameLabel = new QLabel(ui->scrollAreaWidgetContents_3);
    //scanNameLabel->setText(QString::fromLocal8Bit("扫描仪名称"));
    scanNameLabel->setGeometry(QRect(x+245,y-60,530,30));
    scanNameLabel->setAlignment(Qt::AlignCenter);
    QFont ft( "Microsoft YaHei",10,10);    //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    scanNameLabel->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    scanNameLabel->setPalette(pa);

    //端口部分
    cakou.resize(24);
    cakouInfo.resize(24);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            //槽口图标
            cakou[portNumber-1] = new QLabel(ui->scrollAreaWidgetContents_3);
            cakou[portNumber-1]->setGeometry(QRect(x+x_distance*j,y+y_distance*i,22,80));
            //cakou[portNumber-1]->setPixmap(QPixmap(":/image/caokou_gray.jpg"));
            cakou[portNumber-1]->setObjectName(QString("%1").arg(portNumber));//设置图标标号名称1~24

            //槽口文字
            cakouInfo[portNumber-1] = new QLabel(ui->scrollAreaWidgetContents_3);
            cakouInfo[portNumber-1]->setGeometry(QRect(x+x_distance*j-11,y+y_distance*i+95,160,60));
            //cakouInfo[portNumber-1]->setText(QString::fromLocal8Bit("槽口%1\r\n").arg(portNumber));

            //设置字号
            QFont ft("Microsoft YaHei",10,10);    //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
            cakouInfo[portNumber-1]->setFont(ft);
            //设置颜色
            QPalette pa;
            pa.setColor(QPalette::WindowText,Qt::white);
            cakouInfo[portNumber-1]->setPalette(pa);
            ++portNumber;
        }
    }
}

void device::loadCakouIcon(ModelScan scan)
{
    for(int i=0;i<24;i++)
    {
        cakou[i]->setPixmap(QPixmap(":/image/caokou_gray.jpg"));
        cakouInfo[i]->setText(QString::fromLocal8Bit("槽口%1\r\n").arg(i+1));
    }

    for(int i=0;i<ModelPeixianjia::m_ListPeixianjia.count();i++)
    {
        if(ModelPeixianjia::m_ListPeixianjia[i].ScanID()==scan.ID())
        {
            int Number = ModelPeixianjia::m_ListPeixianjia[i].ScanPort()-1;
            cakou[Number]->setPixmap(QPixmap(":/image/caokou_green.jpg"));
            cakouInfo[Number]->setText(QString::fromLocal8Bit("槽口%1\r\n%2").arg(Number+1).arg(ModelPeixianjia::m_ListPeixianjia[i].NAME()));
        }
    }
}

void device::updateCakouIconFromDb(ModelScan scan)
{

    //ModelTreeNode::LoadTreeNode();   //加载内存

    for(int i=0;i<24;i++)
    {
        cakou[i]->setPixmap(QPixmap(":/image/caokou_gray.jpg"));
        cakouInfo[i]->setText(QString::fromLocal8Bit("槽口%1\r\n").arg(i+1));
    }

    for(int i=0;i<ModelPeixianjia::m_ListPeixianjia.count();i++)
    {
        if(ModelPeixianjia::m_ListPeixianjia[i].ScanID()==scan.ID())
        {
            int Number = ModelPeixianjia::m_ListPeixianjia[i].ScanPort()-1;
            cakou[Number]->setPixmap(QPixmap(":/image/caokou_green.jpg"));
            cakouInfo[Number]->setText(QString::fromLocal8Bit("槽口%1\r\n%2").arg(Number+1).arg(ModelPeixianjia::m_ListPeixianjia[i].NAME()));
        }
    }
}

void device::loadPeixianjiaIcon()
{
    //字体颜色——白色
    QPalette white;
    white.setColor(QPalette::WindowText,Qt::white);

    /****************表上******************/
    int x = ui->scrollAreaWidgetContents->x()+ui->scrollAreaWidgetContents->width()/2-400;
    int y = 50;
    int distance = 27;
    peixianjiaLabel.resize(27);

    peixianjiaTextLabel.resize(24);//表上端口标号

    //表上两端图标
    peixianjiaLabel[24] = new QLabel(ui->setLink);           //左侧
    peixianjiaLabel[24]->setGeometry(QRect(x,y,47,48));
    //peixianjiaLabel[24]->setPixmap(QPixmap(":/image/peixianjia/left.gif"));

    peixianjiaLabel[25] = new QLabel(ui->setLink);           //右侧
    peixianjiaLabel[25]->setGeometry(QRect(x+695,y,52,48));
    //peixianjiaLabel[25]->setPixmap(QPixmap(":/image/peixianjia/right.gif"));

    //表上拖拽提示或配线架名称
    peixianjiaLabel[26] = new QLabel(ui->setLink);           //
    peixianjiaLabel[26]->setGeometry(QRect(ui->scrollAreaWidgetContents->x()+10,10,1400,135));
    peixianjiaLabel[26]->setText(QString::fromLocal8Bit("二、再拖拽配线架至此位置"));
    peixianjiaLabel[26]->setAlignment(Qt::AlignCenter);
    //peixianjiaLabel[26]->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(255,255,255);"));
    peixianjiaLabel[26]->setObjectName(QString("peixianjia"));
    //设置字号
    peixianjiaLabel[26]->setFont(QFont( "Verdana",12,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //设置颜色
    peixianjiaLabel[26]->setPalette(white);


    for(int i=0;i<24;i++)
    {
            //配线架图标
            peixianjiaLabel[i] = new QLabel(ui->setLink);
            peixianjiaLabel[i]->setGeometry(QRect(x+47+distance*i,y,27,48));
            peixianjiaLabel[i]->setAlignment(Qt::AlignCenter);
            //peixianjiaLabel[i]->setPixmap(QPixmap(":/image/peixianjia/port24_black.gif"));
            peixianjiaLabel[i]->setObjectName(QString("  %1").arg(i+1));//设置图标标号名称1~24

            //表上端口标号
            peixianjiaTextLabel[i]= new QLabel(ui->setLink);
            peixianjiaTextLabel[i]->setGeometry(QRect(x+47+distance*i,y-25,27,20));
            //peixianjiaTextLabel[i]->setText(QString("%1").arg(i+1));
            peixianjiaTextLabel[i]->setAlignment(Qt::AlignCenter);
            //设置字号
            peixianjiaTextLabel[i]->setFont(QFont( "Microsoft YaHei",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
            //设置颜色
            peixianjiaTextLabel[i]->setPalette(white);
    }

    /****************表中******************/
    int scroll_x = ui->scrollAreaWidgetContents->x();
    int scroll_y = ui->scrollAreaWidgetContents->y()+120;
    tableIconLabel.resize(73+48);
    tableTextLabel.resize(73);

    //交换机端口
    for(int i=0;i<24;i++)
    {
        //端口图标
        tableIconLabel[i] = new QLabel(ui->scrollAreaWidgetContents);
        tableIconLabel[i]->setGeometry(QRect(scroll_x+160,scroll_y+20+24+i*100,43,32));
        //tableIconLabel[i]->setPixmap(QPixmap(":/image/peixianjia/lanport.png"));

        //端口号
        tableTextLabel[i] = new QLabel(ui->scrollAreaWidgetContents);
        tableTextLabel[i]->setGeometry(QRect(scroll_x+160,scroll_y+20+24+i*100+40,60,15));
        //tableTextLabel[i]->setText(QString::fromLocal8Bit("端口%1").arg(i+1));
        //设置字号
        tableTextLabel[i]->setFont(QFont( "Microsoft YaHei",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        //设置颜色
        tableTextLabel[i]->setPalette(white);
    }

    //交换机图标
    tableIconLabel[24] = new QLabel(ui->scrollAreaWidgetContents);
    tableIconLabel[24]->setGeometry(QRect(scroll_x+20,scroll_y+20,100,1000));
    tableIconLabel[24]->setObjectName(QString("switch"));
    //tableIconLabel[24]->setGeometry(QRect(scroll_x+20+26,scroll_y+250,48,400));
    //tableIconLabel[24]->setPixmap(QPixmap(":/image/peixianjia/switch1.gif"));

    //交换机文字
    tableTextLabel[24] = new QLabel(ui->scrollAreaWidgetContents);
    tableTextLabel[24]->setGeometry(QRect(scroll_x+20+35,scroll_y+200,30,700));
    //tableTextLabel[24]->setGeometry(QRect(scroll_x+20,scroll_y+650,100,50));
    tableTextLabel[24]->setFont(QFont( "Verdana",12,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //tableTextLabel[24]->setFont(QFont( "Verdana",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    tableTextLabel[24]->setPalette(white);
    tableTextLabel[24]->setWordWrap(true);
    tableTextLabel[24]->setAlignment(Qt::AlignTop); //居中
    //tableTextLabel[24]->setAlignment(Qt::AlignCenter); //居中
    tableTextLabel[24]->setText(QString::fromLocal8Bit("一、请先拖拽交换机至此"));

    //工单图标
    for(int i=25;i<73;i++)
    {
        //第一列图标
        tableIconLabel[i] = new QLabel(ui->scrollAreaWidgetContents);
        tableIconLabel[i+48] = new QLabel(ui->scrollAreaWidgetContents);
        tableIconLabel[i]->setGeometry(QRect(scroll_x+295,scroll_y+20+20+(i-25)*50,507,48));
        tableIconLabel[i]->setObjectName(QString("%1").arg(i));
        //tableIconLabel[i]->setPixmap(QPixmap(":/image/peixianjia/24kou.png"));

        //第一列文字
        tableTextLabel[i] = new QLabel(ui->scrollAreaWidgetContents);
        tableTextLabel[i]->setGeometry(QRect(scroll_x+295,scroll_y+20+75+(i-25)*50,507,20));
        //tableTextLabel[i]->setText(QString::fromLocal8Bit("端口%1").arg(i-24));
        tableTextLabel[i]->setFont(QFont( "Microsoft YaHei",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        tableTextLabel[i]->setPalette(white);

        //第二列图标
        tableIconLabel[i+1] = new QLabel(ui->scrollAreaWidgetContents);
        tableIconLabel[i+49] = new QLabel(ui->scrollAreaWidgetContents);
        tableIconLabel[i+1]->setGeometry(QRect(scroll_x+915,scroll_y+20+20+(i-25)*50,507,48));
        tableIconLabel[i+1]->setObjectName(QString("%1").arg(i+1));
        //tableIconLabel[i+1]->setPixmap(QPixmap(":/image/peixianjia/24kou.png"));

        //第二列文字
        tableTextLabel[i+1] = new QLabel(ui->scrollAreaWidgetContents);
        tableTextLabel[i+1]->setGeometry(QRect(scroll_x+915,scroll_y+20+75+(i-25)*50,507,20));
        //tableTextLabel[i+1]->setText(QString::fromLocal8Bit("端口%1").arg(i-23));
        tableTextLabel[i+1]->setFont(QFont( "Microsoft YaHei",8,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        tableTextLabel[i+1]->setPalette(white);
        i++;
    }
}



void device::addChestTree(ModelChest chest)
{
    if(db.selectData("SwitchTools","Chest","NAME",chest.NAME()))
    {
        getDevice->ui->chestInfoLabel->setText(QString::fromLocal8Bit("已存在该设备名，请更改后添加"));
    }
    else
    {
      bool statusOne = db.insertData(QString("INSERT INTO `SwitchTools`.`Chest`(`NAME`,`Manufactor`,`Model`,`Height`) VALUES('%1','%2','%3','%4');").arg(chest.NAME()).arg(chest.Manufactory()).arg(chest.Model()).arg(chest.Height()));
      bool statusTwo = db.insertData(QString("INSERT INTO `SwitchTools`.`DeviceTree`(`NAME`,`ParentID`,`Type`) VALUES('%1','%2','%3');").arg(chest.NAME()).arg(externvalue::parentID).arg("jigui"));
      if(statusOne&&statusTwo)
      {
          getDevice->ui->chestInfoLabel->setText(QString::fromLocal8Bit("添加成功"));
          getDevice->close();
      }
      else
          getDevice->ui->chestInfoLabel->setText(QString::fromLocal8Bit("添加失败"));
    }

    //在目录中添加图标
    QStandardItem* jigui = new QStandardItem(QIcon(":/image/treeicon/jigui.png"),chest.NAME());
    jigui->setData(MARK_CHEST,ROLE_MARK);
    model->appendRow(jigui);
}

void device::addIscanTree(ModelScan scan)
{
    if(db.selectData("SwitchTools","Scan","NAME",scan.NAME()))
    {
        getDevice->ui->iscanInfoLabel->setText(QString::fromLocal8Bit("已存在该设备名，请更改后添加"));
    }
    else
    {
      bool statusOne = db.insertData(QString("INSERT INTO `SwitchTools`.`Scan`(`NAME`,`IP`,`Gate`,`Port`) VALUES('%1','%2','%3','%4');").arg(scan.NAME()).arg(scan.IP()).arg(scan.Gate()).arg(scan.Port()));
      bool statusTwo = db.insertData(QString("INSERT INTO `SwitchTools`.`DeviceTree`(`NAME`,`ParentID`,`Type`) VALUES('%1','%2','%3');").arg(scan.NAME()).arg(externvalue::parentID).arg("scan"));
      if(statusOne&&statusTwo)
      {
          getDevice->ui->iscanInfoLabel->setText(QString::fromLocal8Bit("添加成功"));
          getDevice->close();
      }
      else
          getDevice->ui->iscanInfoLabel->setText(QString::fromLocal8Bit("添加失败"));
      //在目录中添加图标
      QModelIndex currentIndex = ui->deviceTree->currentIndex();
      QStandardItem* currentItem = model->itemFromIndex(currentIndex);

      if(currentItem)
      {
          QStandardItem* saomiao = new QStandardItem(QIcon(":/image/treeicon/scan.png"),scan.NAME());
          saomiao->setData(MARK_OTHER,ROLE_MARK);
          currentItem->appendRow(saomiao);
      }
    }   
}

void device::addPeixianjiaTree(ModelPeixianjia pei)
{
    if(db.selectData("SwitchTools","Peixianjia","NAME",pei.NAME()))
    {
        getDevice->ui->peiInfoLabel->setText(QString::fromLocal8Bit("已存在该设备名，请更改后添加"));
    }
    else
    {
      bool statusOne = db.insertData(QString("INSERT INTO `SwitchTools`.`Peixianjia`(`NAME`,`DeviceType`,`Model`,`Manufactory`) VALUES('%1','%2','%3','%4');").arg(pei.NAME()).arg(pei.Type()).arg(pei.Model()).arg(pei.Manufactory()));
      bool statusTwo = db.insertData(QString("INSERT INTO `SwitchTools`.`DeviceTree`(`NAME`,`ParentID`,`Type`) VALUES('%1','%2','%3');").arg(pei.NAME()).arg(externvalue::parentID).arg("peixianjia"));
      if(statusOne&&statusTwo)
      {
          getDevice->ui->peiInfoLabel->setText(QString::fromLocal8Bit("添加成功"));
          getDevice->close();
      }
      else
          getDevice->ui->peiInfoLabel->setText(QString::fromLocal8Bit("添加失败"));
      //在目录中添加图标
      QModelIndex currentIndex = ui->deviceTree->currentIndex();
      QStandardItem* currentItem = model->itemFromIndex(currentIndex);

      if(currentItem)
      {
          QStandardItem* peixianjia = new QStandardItem(QIcon(":/image/treeicon/peixianjia.png"),pei.NAME());
          peixianjia->setData(MARK_OTHER,ROLE_MARK);
          currentItem->appendRow(peixianjia);
      }
    }
}

void device::addSwitchTree(ModelSwitch swit)
{
    if(db.selectData("SwitchTools","Switch","NAME",swit.NAME()))
    {
        getDevice->ui->switchInfoLabel->setText(QString::fromLocal8Bit("已存在该设备名，请更改后添加"));
    }
    else
    {
      bool statusOne = db.insertData(QString("INSERT INTO `SwitchTools`.`Switch`(`NAME`,`Port`,`Model`,`Manufactory`) VALUES('%1','%2','%3','%4');").arg(swit.NAME()).arg(swit.Port()).arg(swit.Model()).arg(swit.Manufactory()));
      bool statusTwo = db.insertData(QString("INSERT INTO `SwitchTools`.`DeviceTree`(`NAME`,`ParentID`,`Type`) VALUES('%1','%2','%3');").arg(swit.NAME()).arg(externvalue::parentID).arg("switch"));
      if(statusOne&&statusTwo)
      {
          getDevice->ui->switchInfoLabel->setText(QString::fromLocal8Bit("添加成功"));
          getDevice->close();
      }
      else
          getDevice->ui->switchInfoLabel->setText(QString::fromLocal8Bit("添加失败"));
      //在目录中添加图标
      QModelIndex currentIndex = ui->deviceTree->currentIndex();
      QStandardItem* currentItem = model->itemFromIndex(currentIndex);

      if(currentItem)
      {
          QStandardItem* jiaohuanji = new QStandardItem(QIcon(":/image/treeicon/switch.png"),swit.NAME());
          jiaohuanji->setData(MARK_OTHER,ROLE_MARK);
          currentItem->appendRow(jiaohuanji);
      }
    }
}



void device::on_selectBtn_clicked()
{
//    MemoryThread.start();
//    MemoryThread.terminate();
//    MemoryThread.wait();

    //ModelTreeNode::LoadTreeNode();   //加载内存

}
