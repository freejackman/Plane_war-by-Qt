#ifndef WIDGET_H
#define WIDGET_H

#include"map.h"
#include"config.h"
#include"plane.h"
#include"em_plane.h"
#include <QWidget>
#include<QPushButton>
#include<QTimer>
#include<QPainter>
#include<QMediaPlayer>     //音乐播放器
#include<QMediaPlaylist>    //音乐列表

class Widget : public QWidget
{
    Q_OBJECT

    public:
        QTimer timer;                       //定时器
        map maper;                              //地图
        plane planer;                            //玩家飞机
        em_plane em_planer[PLANE2_AMOUNT];      //敌机库
        bullet em_bull[PLANE2_BULLET];          //敌机子弹库
        int em_invert;                   //敌机出场的时间间隔
        QMediaPlayer *background;        //背景音乐
        QMediaPlaylist *background_list;  //背景音乐列表
        QMediaPlayer *boom_music;         //爆炸音效
        QPushButton *endbutton;           //结束按钮
        QPushButton *restartbutton;           //重新开始按钮
    public:
        Widget(QWidget *parent = 0);
        ~Widget();
        void playgame();   //开始游戏
        void update_map_y();  //更新地图y坐标
        void paintEvent(QPaintEvent*);    //绘图事件监听
        void keyPressEvent(QKeyEvent *ev);   //按键事件监听
        void mouseMoveEvent(QMouseEvent *ev);    //鼠标移动事件监听
        void update_bullet();          //玩家子弹位置更新
        void em_shoot();                //敌机子弹发射函数
        void em_appear();               //敌机出场函数
        void update_em_bullet();        //更新敌机子弹坐标
        void update_em_plane();         //更新敌机坐标
        void collision_detection();     //碰撞检测

};

#endif // WIDGET_H
