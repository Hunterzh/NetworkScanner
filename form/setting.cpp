#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    createQss();
    //窗体大小
    QDesktopWidget * deskTop = QApplication::desktop();
    int number= deskTop->screenNumber ( this ); // 主屏号，参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(number);
    this->setBaseSize(rect.width()*0.7,rect.height()*0.8);

    ui->settingTabWidget->setGeometry(QRect(this->x(),this->y(),this->width(),this->height()));


}

setting::~setting()
{
    delete ui;
}

void setting::createQss()  //创建qss
{
    QFile qssFile(":/qss/setting.qss");

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
     {
         this->setStyleSheet(QLatin1String(qssFile.readAll()));
         qssFile.close();
     }
}

void setting::on_conformBtn_clicked()
{
    QString userText = ui->accountAlterEdit->text().trimmed(); //取账户名
    QString lastPasswordText = ui->lastPasswordEdit->text().trimmed(); //取原密码
    QString newPasswordText = ui->newPasswordEdit->text().trimmed(); //取新密码
    QString surePasswordText = ui->surePasswordEdit->text().trimmed(); //取确认密码

//    QString queryText = QString("SELECT `password` FROM `acount` WHERE user=\'%1\';").arg(userText);

//    QSqlQuery query(queryText);

//    query.next();
//    QString getPassword = query.value(0).toString();
//    //ui->lineEdit->setText(getPassword);

//    if(getPassword != lastPasswordText)
//    {
//        QMessageBox::about(NULL,"ERROR","LastPassword is error");
//        ui->lastPasswordEdit->setFocus();
//    }
//    else
//    {
//        if(newPasswordText != surePasswordText)
//        {
//            QMessageBox::about(NULL,"ERROR","Entered passwords differ");
//            ui->surePasswordEdit->setFocus();
//        }
//        else
//        {
//            query.exec(QString("UPDATE `acount` SET `password`=\'%1\' WHERE `user`=\'%2\';").arg(surePasswordText).arg(userText));//更新密码
//            QMessageBox::about(NULL,"成功","原密修改成功");
//        }
//    }

}

void setting::on_cancelBtn_clicked()
{
    ui->lastPasswordEdit->clear();
    ui->lastPasswordEdit->setFocus();//把输入焦点放在旧密码处，方便重新输入
    ui->newPasswordEdit->clear();
    ui->surePasswordEdit->clear();
}

void setting::on_registerBtn_clicked()
{
    QString userText = ui->registerAcountEdit->text().trimmed(); //取账户名
    QString passwordText = ui->registerPasswordEdit->text().trimmed(); //取密码

//    QSqlQuery query;
//    query.prepare("INSERT INTO `acount`(`user`,`password`) VALUES(:user,:password);");
//    query.bindValue(":user",userText);
//    query.bindValue(":password",passwordText);
//    bool flag = query.exec();
//    if(flag == true)
//    {
//        QMessageBox::about(NULL,"成功","注册成功");
//    }
//    else
//    {
//        QMessageBox::about(NULL,"错误","注册失败");
//    }
}

void setting::on_cancelRegisterBtn_clicked()
{
    ui->registerAcountEdit->clear();
    ui->registerPasswordEdit->clear();
    ui->registerAcountEdit->setFocus();//输入焦点
}

