#include "alarm.h"
#include "ui_alarm.h"

alarm::alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarm)
{
    ui->setupUi(this);
    count=0;
    createQss();
    loadIcon();
    loadData();
    //加载内存
    ModelTreeNode::LoadTreeNode();

    //数据库
    db.createConnection("127.0.0.1","root",3306,"123456");

    //窗体大小
    QDesktopWidget * deskTop = QApplication::desktop();
    int number= deskTop->screenNumber ( this ); // 主屏号，参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(number);
    //this->setFixedSize(rect.width()*0.7,rect.height()*0.8-170);  //固定窗体大小
    //this->setBaseSize(rect.width()*0.7,rect.height()*0.8-170);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->alamTab->setColumnCount(3);    //设置列数
    ui->alamTab->setRowCount(100);        //设置行数
    QStringList  HStrList;
    HStrList<<QString::fromLocal8Bit("时间")<<QString::fromLocal8Bit("类型")<<QString::fromLocal8Bit("说明");
    ui->alamTab->setHorizontalHeaderLabels(HStrList);

    ui->alarmArea->resize(this->width()*0.8, this->height());
    ui->alarmArea->setMinimumSize (1290,850);
    ui->scrollAreaWidgetContents->setMinimumSize (this->width()*0.8-40,1600);
    ui->alarmArea->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
}

alarm::~alarm()
{
    delete ui;
}

void alarm::createQss()
{
    QFile qssFile(":/qss/alarm.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
    }
}

void alarm::paintEvent(QPaintEvent *event)
{
//    QPainter line(this);
//    QColor blue(78,185,208);
//    QPen pen(blue);
//    pen.setWidth(2);
//    line.setPen(pen);
//    line.drawLine(0,135,this->width(),135);
}

void alarm::loadIcon()
{
    /****************机柜******************/
    int uCount = 42;
    int left_x=ui->scrollAreaWidgetContents->x()+100; //左侧首坐标  42*24分辨率
    int left_y=ui->scrollAreaWidgetContents->y()+50+76;
    int right_x=ui->scrollAreaWidgetContents->x()+100+285-43; //右侧首坐标  43*24分辨率
    int right_y=ui->scrollAreaWidgetContents->y()+50+76;

    //柜头
    QLabel *chestTop = new QLabel(ui->scrollAreaWidgetContents);
    chestTop->setGeometry(QRect(left_x, left_y-76, 285, 76));
    chestTop->setPixmap(QPixmap(QString::fromUtf8(":/image/jg/top.png")));
    //柜尾
    QLabel *chestBottom = new QLabel(ui->scrollAreaWidgetContents);
    chestBottom->setGeometry(QRect(left_x, left_y+24*uCount, 285, 68));
    chestBottom->setPixmap(QPixmap(QString::fromUtf8(":/image/jg/bottom.png")));

    leftPicture.resize(uCount);
    rightPicture.resize(uCount);
    devicePicture.resize(uCount);
    chestLevel.resize(uCount);

    for(int i=0;i<uCount;i++)
    {
        //左
        leftPicture[i] = new QLabel(ui->scrollAreaWidgetContents);
        leftPicture[i]->setGeometry(QRect(left_x,left_y+24*i,42,24));
        QPixmap left=QPixmap(":/image/jg/left.gif");
        leftPicture[i]->setPixmap(left);

        //右
        rightPicture[i] = new QLabel(ui->scrollAreaWidgetContents);
        rightPicture[i]->setGeometry(QRect(right_x,right_y+24*i,43,24));
        QPixmap right=QPixmap(":/image/jg/right.gif");
        rightPicture[i]->setPixmap(right);

        //中
        devicePicture[i] = new QLabel(ui->scrollAreaWidgetContents);
        devicePicture[i]->setGeometry(QRect(left_x+42,left_y+24*i,200,24));
        devicePicture[i]->setObjectName(QString("%1").arg(i+1));//设置图标标号名称1~uCount
        //devicePicture[i]->setPixmap(QPixmap(":/image/jg/peixianjia.png"));
        //层
        chestLevel[i] = new QLabel(ui->scrollAreaWidgetContents);
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

    /****************配线架1******************/
    //字体颜色——白色
    QPalette white;
    white.setColor(QPalette::WindowText,Qt::white);

    int x = right_x+250;
    int y = right_y+60;
    int distance = 17;
    singlePeixianjia.resize(27);

    //两端图标
    singlePeixianjia[24] = new QLabel(ui->scrollAreaWidgetContents);           //左侧
    singlePeixianjia[24]->setGeometry(QRect(x,y,47,48));
    singlePeixianjia[24]->setPixmap(QPixmap(":/image/peixianjia/left.gif"));

    singlePeixianjia[25] = new QLabel(ui->scrollAreaWidgetContents);           //右侧
    singlePeixianjia[25]->setGeometry(QRect(x+455,y,52,48));
    singlePeixianjia[25]->setPixmap(QPixmap(":/image/peixianjia/right.gif"));

    //配线架标号
    singlePeixianjia[26] = new QLabel(ui->scrollAreaWidgetContents);
    singlePeixianjia[26]->setGeometry(QRect( x+47, y+50, 408, 50));
    singlePeixianjia[26]->setText(QString::fromLocal8Bit("电子配线架1"));
    singlePeixianjia[26]->setAlignment(Qt::AlignCenter); //居中
        //设置字号
    singlePeixianjia[26]->setFont(QFont( "Microsoft YaHei",10,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        //设置颜色
    singlePeixianjia[26]->setPalette(white);

    for(int i=0;i<24;i++)
    {
            //配线架图标
            singlePeixianjia[i] = new QLabel(ui->scrollAreaWidgetContents);
            singlePeixianjia[i]->setGeometry(QRect(x+47+distance*i,y,17,48));
            QPixmap pix=QPixmap(":/image/peixianjia/port24_black.gif");
            singlePeixianjia[i]->setPixmap(pix);
            singlePeixianjia[i]->setObjectName(QString("%1").arg(i+1));//设置图标标号名称1~24
    }

    /****************配线架2******************/
    doublePeixianjia.resize(27);

    //两端图标
    doublePeixianjia[24] = new QLabel(ui->scrollAreaWidgetContents);           //左侧
    doublePeixianjia[24]->setGeometry(QRect(x,y+150,47,48));
    doublePeixianjia[24]->setPixmap(QPixmap(":/image/peixianjia/left.gif"));

    doublePeixianjia[25] = new QLabel(ui->scrollAreaWidgetContents);           //右侧
    doublePeixianjia[25]->setGeometry(QRect(x+455,y+150,52,48));
    doublePeixianjia[25]->setPixmap(QPixmap(":/image/peixianjia/right.gif"));

    //配线架标号
    doublePeixianjia[26] = new QLabel(ui->scrollAreaWidgetContents);
    doublePeixianjia[26]->setGeometry(QRect( x+47, y+50+150, 408, 50));
    doublePeixianjia[26]->setText(QString::fromLocal8Bit("电子配线架2"));
    doublePeixianjia[26]->setAlignment(Qt::AlignCenter); //居中
        //设置字号
    doublePeixianjia[26]->setFont(QFont( "Microsoft YaHei",10,10));   //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        //设置颜色
    doublePeixianjia[26]->setPalette(white);

    for(int i=0;i<24;i++)
    {
            //配线架图标
            doublePeixianjia[i] = new QLabel(ui->scrollAreaWidgetContents);
            doublePeixianjia[i]->setGeometry(QRect(x+47+distance*i,y+150,17,48));
            QPixmap pix=QPixmap(":/image/peixianjia/port24_black.gif");
            doublePeixianjia[i]->setPixmap(pix);
            doublePeixianjia[i]->setObjectName(QString("%1").arg(i+1));//设置图标标号名称1~24
    }
}

void alarm::loadData()
{
    QVector<QString> position = db.selectAllData("SwitchTools","ChestLink","Position");
    QVector<QString> type = db.selectAllData("SwitchTools","ChestLink","Type");
    for(int i=0;i<position.count();i++)
    {
        int positionNumber = position[i].toInt();
        if(type[i] == QString::fromLocal8Bit("扫描仪"))
        devicePicture[positionNumber]->setPixmap(QPixmap(":/image/jg/scan.png"));
        if(type[i] == QString::fromLocal8Bit("交换机"))
        devicePicture[positionNumber]->setPixmap(QPixmap(":/image/jg/switch.gif"));
        if(type[i] == QString::fromLocal8Bit("电子配线架"))
        devicePicture[positionNumber]->setPixmap(QPixmap(":/image/jg/peixianjia.png"));
    }
}

void alarm::showAlarm(QVector<QString> value)
{
    QDateTime time = QDateTime::currentDateTime();
    QString strDate = time.toString("yyyy-MM-dd HH:mm");
    QVector<QString> PeiXianAlm;

    if(value==PeiXianAlm)
        return;
    else
        PeiXianAlm=value;

    QString almType;
    if(PeiXianAlm[5]=="0")
        almType="double off";
    if(PeiXianAlm[5]=="1")
        almType="single off";
    if(PeiXianAlm[5]=="2")
        almType="single invade";
    if(PeiXianAlm[5]=="3")
        almType="double invade";

    QString detail="scanID"+PeiXianAlm[0]+"::Sort:"+PeiXianAlm[1]+"Port:"+PeiXianAlm[2]+" | Sort:"+PeiXianAlm[3]+"Port:"+PeiXianAlm[4];

    ui->alamTab->setItem(count, 0, new QTableWidgetItem(strDate)); //时间
    ui->alamTab->setItem(count, 1, new QTableWidgetItem(almType)); //类型
    ui->alamTab->setItem(count, 2, new QTableWidgetItem(detail)); //说明

    count++;

}
