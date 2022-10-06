#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include"widget.h"
#include"config.h"
#include <QWidget>
#include<QPushButton>
#include<QPixmap>
#include<QPainter>

class mainwidget : public QWidget
{
    Q_OBJECT

    public:
        mainwidget(QWidget *parent = nullptr);
        ~mainwidget();
        void paintEvent(QPaintEvent *);     //绘图事件
        void restart();
    public:
        Widget *widget2;
        QPushButton *startbutton;       //开始游戏按钮
        QPixmap background;             //背景
        QPixmap title;                  //游戏标题
        int three;                      //第三个窗口标志位
};

#endif // MAINWIDGET_H
