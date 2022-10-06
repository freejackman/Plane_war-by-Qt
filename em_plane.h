#ifndef EM_PLANE_H
#define EM_PLANE_H

#include"config.h"
#include"bullet.h"

class em_plane
{
public:
    em_plane();
public:
    QPixmap em_planepix;  //敌机图像

    int em_plane_x;     //敌机坐标
    int em_plane_y;

    QRect rect;    //敌机碰撞矩阵坐标

    int em_plane_speed;   //敌机移动速度

    int inverts;            //敌机子弹发射的时间间隔

    bool isfree;          //判断敌机是否空闲

    int sign;             //爆炸标志位
};

#endif // EM_PLANE_H
