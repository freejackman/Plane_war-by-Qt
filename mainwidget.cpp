#include "mainwidget.h"
#include"config.h"
#include"widget.h"
#include<QPushButton>
#include<QPainter>

mainwidget::mainwidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(MAP_WIDE,MAP_HIGHT);   //固定窗口大小
    this->setWindowTitle("飞机大战(自制版)");   //设置窗口标题
    this->setWindowIcon(QIcon(SORTWARE_ICON));     //设置图标

    widget2= new Widget;     //初始化第二个窗口
    background.load(MAP_PATH);  //背景初始化
    title.load(TITLE);          //设置软件封面
    this->update();             //手动调用绘图事件监听函数

    startbutton = new QPushButton;          //开始游戏按钮的初始化
    startbutton->setParent(this);
    startbutton->move(STARTBUTTON_X,STARTBUTTON_Y);
    startbutton->resize(STARTBUTTON_WIDTH,STARTBUTTON_HIGHT);
    startbutton->setText("开始游戏");

    //绑定信号与槽
    //匿名函数
    connect(startbutton,&QPushButton::clicked,this,[=](){
        this->hide();      //将第一个窗口关闭
        widget2->show();    //将第二个窗口打开
        widget2->playgame();
    });
    connect(widget2->restartbutton,&QPushButton::clicked,this,&mainwidget::restart);
}

void mainwidget::restart()        //槽函数
{
    delete widget2;
    widget2=new Widget;      //重新构造对象
    //重新绑定信号与槽
    connect(widget2->restartbutton,&QPushButton::clicked,this,&mainwidget::restart);
    widget2->show();
    widget2->playgame();
}

void mainwidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,background);
    paint.drawPixmap(0,0,title);
}


mainwidget::~mainwidget()
{
    delete widget2;
    delete startbutton;
}
