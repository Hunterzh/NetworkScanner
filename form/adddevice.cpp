#include "adddevice.h"
#include "ui_adddevice.h"
#include <QtSql>
#include <QtXml>
#include <QtGui>

addDevice::addDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addDevice)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//设置窗体标题栏隐藏

    ui->closeBtn->setGeometry(this->width()-64,4,60,30);
    createQss();

    udp = new udpsocket();
    database = new sqlDb();

    //加载配线架类型
    QVector<QString> peixianjiaType = database->selectAllData("SwitchTools","PeixianjiaType","NAME");
    QStringList addType;
    for(int i=0;i<peixianjiaType.count();i++)
    {
        addType<<peixianjiaType[i];
    }
    ui->peiComboBox->addItems(addType);

}

addDevice::~addDevice()
{
    delete ui;
}

void addDevice::createQss()  //创建qss
{
    QFile qssFile(":/qss/addDevice.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
     }
}

void addDevice::paintEvent(QPaintEvent *)  //蓝色边框
{
    QPainter line(this);
    QColor blue(78,185,208);
    QPen pen(blue);
    pen.setWidth(4);
    line.setPen(pen);
    line.drawLine(0,0,0,this->height());
    line.drawLine(0,0,this->width(),0);
    line.drawLine(this->width(),this->height(),this->width(),0);
    line.drawLine(this->width(),this->height(),0,this->height());
}

void addDevice::showIndex(int number)
{
    this->show();
    if(number==0)  //机柜
        ui->tabWidget->setCurrentIndex(0);
    if(number==1)  //扫描仪
        ui->tabWidget->setCurrentIndex(1);
    if(number==2)  //交换机
        ui->tabWidget->setCurrentIndex(2);
    if(number==3)  //配线架
        ui->tabWidget->setCurrentIndex(3);
}

void addDevice::addChest()
{
    QString name = ui->chestNameEdit->text().trimmed(); //取名称
    QString manufactory = ui->chestFactoryEdit->text().trimmed(); //取厂家
    QString model = ui->chestVersionEdit->text().trimmed(); //取型号
    int height = ui->chestHeightEdit->text().trimmed().toInt(); //取高度

    ModelChest chest;
    chest.setNAME(name);
    chest.setManufactory(manufactory);
    chest.setModel(model);
    chest.setHeight(height);

    emit addChestEvent(chest);


}

void addDevice::addIscan()
{
    QString name = ui->iscanNameEdit->text().trimmed();
    QString ip = ui->iscanIpEdit->text().trimmed();
    QString gate = ui->iscanGatewayEdit->text().trimmed();
    int port = ui->iscanPortEdit->text().trimmed().toInt();

    ModelScan scan;
    scan.setNAME(name);
    scan.setIP(ip);
    scan.setGate(gate);
    scan.setPort(port);

    emit addIscanEvent(scan);
}

void addDevice::addPeixianjia()
{
    QString name = ui->peiNameEdit->text().trimmed();
    QString type = ui->peiComboBox->currentText().trimmed();
    QString manufacyory = ui->peiManufactory->text().trimmed();
    QString model = ui->peiModel->text().trimmed();

    ModelPeixianjia pei;
    pei.setNAME(name);
    pei.setType(type);
    pei.setManufactory(manufacyory);
    pei.setModel(model);

    emit addPeixianjiaEvent(pei);
}

void addDevice::addSwitch()
{
    QString name = ui->switchNameEdit->text().trimmed();
    int port = ui->switchPortEdit->text().trimmed().toInt();
    QString manufacyory = ui->switchManufactory->text().trimmed();
    QString model = ui->switchModel->text().trimmed();

    ModelSwitch swit;
    swit.setNAME(name);
    swit.setPort(port);
    swit.setManufactory(manufacyory);
    swit.setModel(model);

    emit addSwitchEvent(swit);
}

void addDevice::scanconfig()
{
   QByteArray mac(6,0xFF);

   udp->StartConnect("192.168.80.115",20012,20012);
   //udp->SendScanConfig("192.168.80.110", "192.168.80.1", "255.255.255.1", 1,mac);
   udp->SendHeart();
}

void addDevice::on_addBtn_clicked()
{
    if(ui->tabWidget->currentIndex()==0)  //机柜
        addChest();
    if(ui->tabWidget->currentIndex()==1)  //扫描仪
        addIscan();
    if(ui->tabWidget->currentIndex()==2)  //交换机
        addSwitch();
    if(ui->tabWidget->currentIndex()==3)  //配线架
        addPeixianjia();
}

void addDevice::on_closeBtn_clicked()
{
    this->close();
}



void addDevice::on_deleteBtn_clicked()
{
    if(ui->tabWidget->currentIndex()==0)  //机柜
    {
        ui->chestNameEdit->clear();
        ui->chestFactoryEdit->clear();
        ui->chestVersionEdit->clear();
        ui->chestHeightEdit->clear();
        ui->chestInfoLabel->clear();
        ui->chestNameEdit->setFocus();//输入焦点
    }
    if(ui->tabWidget->currentIndex()==1)  //扫描仪
    {
        ui->iscanNameEdit->clear();
        ui->iscanIpEdit->clear();
        ui->iscanGatewayEdit->clear();
        ui->iscanPortEdit->clear();
        ui->iscanInfoLabel->clear();
        ui->iscanNameEdit->setFocus();//输入焦点
    }
    if(ui->tabWidget->currentIndex()==2)  //交换机
    {
        ui->switchNameEdit->clear();
        ui->switchPortEdit->clear();
        ui->switchModel->clear();
        ui->switchManufactory->clear();
        ui->switchInfoLabel->clear();
        ui->switchNameEdit->setFocus();//输入焦点
    }
    if(ui->tabWidget->currentIndex()==3)  //配线架
    {
        ui->peiNameEdit->clear();
        ui->peiComboBox->clear();
        ui->peiManufactory->clear();
        ui->peiModel->clear();
        ui->peiInfoLabel->clear();
        ui->peiNameEdit->setFocus();//输入焦点
    }

}
