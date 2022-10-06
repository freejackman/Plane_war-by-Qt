#ifndef PLANE_H
#define PLANE_H

#include<QPixmap>
#include"bullet.h"
#include"config.h"

//玩家飞机的设计
class plane
{
    public:
        plane();
        ~plane();
        void shoot();     //玩家飞机子弹发射函数
    public:

        QPixmap planepix;  //玩家飞机图像

        bullet bull[BULLET_AMOUNT];   //玩家飞机子弹库
        int invert;     //飞机子弹时间间隔

        int plane_x;     //玩家飞机坐标
        int plane_y;

        QRect rect;     //玩家飞机碰撞矩阵

        int plane_speed;   //玩家飞机移动速度

        int sign;        //玩家飞机爆炸标志位
};

#endif // PLANE_H
