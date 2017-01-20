#include "user.h"
#include "home.h"
#include "ui_user.h"
#include "ui_home.h"

user::user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);     

    homePage = new home();
    devicePage = new device();
    setPage = new setting();
    alarmPage = new alarm();
    udp = new udpsocket();

    //链接扫描仪
    udp->StartConnect("192.168.80.108",20011,20012);

    ui->stackedWidget->insertWidget(0,homePage);
    ui->stackedWidget->insertWidget(1,alarmPage);
    ui->stackedWidget->insertWidget(2,devicePage);
    ui->stackedWidget->insertWidget(3,setPage);
    ui->stackedWidget->setCurrentIndex(0);

    createQss(); //界面美化
    setWindowFlags(Qt::FramelessWindowHint);//设置窗体标题栏隐藏

    QDesktopWidget * deskTop = QApplication::desktop();
    //int count = deskTop->screenCount();  //屏幕数
    int number= deskTop->screenNumber ( this ); // 主屏号，参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(number);
    DeskTopRect = rect;
    windowStatus = false;

    //this->setFixedSize(rect.width()*0.7,rect.height()*0.8);  //固定窗体大小
    //this->setBaseSize(rect.width()*0.7,rect.height()*0.8);

    ui->stackedWidget->setGeometry(QRect(0, 110, rect.width(), rect.height()-110));

    connect(homePage->ui->addBtn,SIGNAL(clicked()),this,SLOT(on_deviceBtn_clicked()));
    connect(homePage->ui->alarmBtn,SIGNAL(clicked()),this,SLOT(on_alarmBtn_clicked()));
    connect(homePage->ui->settingBtn,SIGNAL(clicked()),this,SLOT(on_settingBtn_clicked()));

    connect(udp,SIGNAL(PeiXianAlm(QVector<QString>)),alarmPage,SLOT(showAlarm(QVector<QString>)));
}

user::~user()
{
    delete ui;
}

void user::on_homeBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void user::on_alarmBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void user::on_deviceBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void user::on_settingBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void user::on_userCloseBtn_clicked()  //窗体关闭事件
{
    this->close();
}

void user::on_userMizeBtn_clicked()  //最大化、最小化
{

    if(windowStatus)
    {
        this->setWindowState(Qt::WindowNoState);
        ui->userMizeBtn->setIcon(QIcon(QString::fromUtf8(":/image/maxmize.png")));
        windowStatus = false;
    }
    else
    {
        this->setWindowState(Qt::WindowFullScreen);
        ui->userMizeBtn->setIcon(QIcon(QString::fromUtf8(":/image/minimize.png")));
        windowStatus = true;
    }
}

void user::on_userMiniBtn_clicked()  //最小化到托盘
{
    this->setWindowState(Qt::WindowMinimized);
}

void user::createQss()  //创建qss
{
    QFile qssFile(":/qss/user.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
     }
}

void user::windowBtn()  //窗体关闭按钮自适应
{
    ui->userCloseBtn->setGeometry(this->width()-60,0,60,40);
    ui->userMizeBtn->setGeometry(this->width()-120,0,60,40);
    ui->userMiniBtn->setGeometry(this->width()-180,0,60,40);
}

void user::paintEvent(QPaintEvent *)  //蓝色分界线
{
    QPainter line(this);
    QColor blue(78,185,208);
    QPen pen(blue);
    pen.setWidth(2);
    line.setPen(pen);
    line.drawLine(0,110,this->width(),110);

    windowBtn();  //关闭按钮
}

/*定义鼠标事件*/
void user::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        {
        mouse_press = true; //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();;
        }
}

void user::mouseMoveEvent(QMouseEvent *event)
{

if(mouse_press)//若鼠标左键被按下
{
    QPoint move_pos = event->globalPos();//鼠标相对于屏幕的位置
    this->move(move_pos - move_point);//移动主窗体位置
}
}

void user::resizeEvent(QResizeEvent *event)
{
    ui->stackedWidget->resize(event->size().width(),event->size().height()-140);
}

void user::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false; //设置鼠标为未被按下
}





