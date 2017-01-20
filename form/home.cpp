#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
    createQss();  //创建qss
    //窗体大小
    QDesktopWidget * deskTop = QApplication::desktop();
    int number= deskTop->screenNumber ( this ); // 主屏号，参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(number);
    //this->setBaseSize(rect.width()*0.7,rect.height()*0.8-170);

    ui->addBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //ui->deviceWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

home::~home()
{
    delete ui;
}

void home::createQss()  //创建qss
{
    QFile qssFile(":/qss/home.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
    }
}


