#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

//    LoadMemoryThread* MemoryThread = new LoadMemoryThread;
//    MemoryThread->start();

    createQss();

    mouse_press=false;  //初始化鼠标为未被按下

    userPage = new user();  //创建主窗口

    ui->loginBtn->setStyleSheet("background-color: rgb(232, 78, 64);");  //添加样式表，loginBtn背景色设置
    ui->closeBtn->setStyleSheet("background-color: rgb(35,39,49);");  //关闭按钮背景色
    //this->setFixedSize( this->width (),this->height ());  //固定窗体大小

    this->setAutoFillBackground(true);  //设置背景色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(35,39,49));
    this->setPalette(palette);


    setWindowFlags(Qt::FramelessWindowHint);//设置窗体标题栏隐藏
    //setWindowFlags(Qt::WindowStaysOnTopHint);//设置窗体设置位于顶层
    setMouseTracking(true);//可获取鼠标跟踪效果


    connect(ui->loginBtn,SIGNAL(clicked()),this,SLOT(loginControl()));
    connect(this,SIGNAL(enterEvent()),this,SLOT(loginControl()));

    //db.createConnection();
    database = new initdatabase();
    //ui->infoLabel->setText(database->Create_DeviceClassMainTypeDefault()[0]);

//    tcp = new tcpclient();



}

login::~login()
{
    delete ui;
}

void login::loginControl()
{
    this->accept();



//    QByteArray data;
//    data.append("hello");
//    data.append("world");

//    tcp->creatConnection("127.0.0.1",8010);
//    tcp->sendData(data);
    /*
    QString userText = ui->userEdit->text().trimmed(); //取账户名
    QString passwordText = ui->passwordEdit->text().trimmed(); //取原密码

    QString queryText = QString("SELECT `password` FROM `acount` WHERE user=\'%1\';").arg(userText);

    QSqlQuery query(queryText);

    query.next();
    QString getPassword = query.value(0).toString();

    if(getPassword != passwordText)
    {
        ui->infoLabel->setText(tr("wrong password "));
        ui->passwordEdit->setFocus();
    }
    else
    {
    this->accept();
    }
    */
}


void login::accept()
{
    this->hide();
    userPage->show();
}


void login::createQss()  //创建qss
{
    QFile qssFile(":/qss/login.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
     }
}

/*定义鼠标事件*/
void login::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        {
        mouse_press = true; //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = event->pos();;
        }
}

void login::mouseMoveEvent(QMouseEvent *event)
{

if(mouse_press)//若鼠标左键被按下
{
    QPoint move_pos = event->globalPos();//鼠标相对于屏幕的位置
    this->move(move_pos - move_point);//移动主窗体位置
    }
}

void login::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false; //设置鼠标为未被按下
}

void login::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
       emit enterEvent();
    }
}


void login::on_closeBtn_clicked()  //关闭登陆窗口
{
    this->close();
}


