#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QDesktopWidget>
#include <QTimer>
#include "ui_home.h"

namespace Ui {
class home;
}

class home : public QWidget , public Ui::home
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = 0);
    ~home();

public:
    Ui::home *ui;
    void createQss();


};

#endif // HOME_H
