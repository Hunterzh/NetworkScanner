#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();
    void createQss();

private slots:
    void on_conformBtn_clicked();
    void on_cancelBtn_clicked();

    void on_registerBtn_clicked();

    void on_cancelRegisterBtn_clicked();

private:
    Ui::setting *ui;
};

#endif // SETTING_H
